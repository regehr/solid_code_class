#include "rle.h"

#include <assert.h>
#include "util.h"

/** (encoded run)<->(bit and count) functions */
static const int RUN_MAX = 127;

static uint8_t run_encode(int type, int len) {
  assert(type == 0 || type == 1);
  assert(len >= 0 && len <= RUN_MAX);

  uint8_t type_enc = type << 7;
  uint8_t len_enc = len;

  return (type_enc | len_enc);
}

static int run_decode_type(uint8_t run) {
  return (run >> 7) & 0x1;
}

static int run_decode_len(uint8_t run) {
  return (int)(run & 0x7F);
}

/** Read context functions and structures */
typedef struct {
  const uint8_t *data;
  const size_t len;
  size_t byte_idx;
  int bit_idx;
} rcontext;

static rcontext rcontext_init(uint8_t *data, size_t len) {
  rcontext con = {.data = data, .len = len, .byte_idx = 0, .bit_idx = 0};
  return con;
}

/** Returns 0 or 1, or -1 for end of data */
static int rcontext_read_bit(rcontext *con) {
  assert(con->len >= con->byte_idx);
  assert(con->bit_idx >= 0 && con->bit_idx <= 7);

  if (con->len == con->byte_idx) {
    return -1;
  } else {
    uint8_t to_extract = con->data[con->byte_idx];
    int bit = (to_extract >> (7 - con->bit_idx)) & 0x1;

    con->bit_idx++;
    if (con->bit_idx == 8) {
      con->bit_idx = 0;
      con->byte_idx++;
    }

    return bit;
  }
}

/** Write context functions and structures */
typedef struct {
  uint8_t *buffer;
  size_t len;
  size_t byte_idx;
} byte_wcontext;

static byte_wcontext byte_wcontext_init(size_t start_len) {
  uint8_t *data = xmalloc(start_len);
  byte_wcontext con = {.buffer = data, .len = start_len, .byte_idx = 0};
  return con;
}

static void byte_wcontext_write(byte_wcontext *con, uint8_t byte) {
  assert(con->len >= con->byte_idx);

  if (con->len == con->byte_idx) {
    con->buffer = xrealloc(con->buffer, con->len*2);
    con->len *= 2;
  }

  con->buffer[con->byte_idx++] = byte;
}

typedef struct {
  uint8_t *buffer;
  size_t len;
  size_t byte_idx;
  size_t bit_idx;
} bit_wcontext;

static bit_wcontext bit_wcontext_init(size_t start_len) {
  uint8_t *data = xmalloc(start_len);
  bit_wcontext con = {.buffer = data, .len = start_len, .byte_idx = 0, .bit_idx = 0};
  return con;
}

static void bit_wcontext_write(bit_wcontext *con, int bit) {
  // TODO: assertions here, probably
  if (con->len == con->byte_idx) {
    con->buffer = xrealloc(con->buffer, con->len*2);
    con->len *= 2;
  }

  if (con->bit_idx == 0)
    con->buffer[con->byte_idx] = 0;

  uint8_t old = con->buffer[con->byte_idx];
  uint8_t to_or = ((uint8_t)bit) << (7 - con->bit_idx);
  uint8_t new = old | to_or;
  con->buffer[con->byte_idx] = new;

  con->bit_idx++;
  if (con->bit_idx == 8) {
    con->bit_idx = 0;
    con->byte_idx++;
  }
}


/** Encoding context functions and structures */
typedef struct {
  int run_type;
  int run_len;
} econtext;

static econtext econtext_init() {
  econtext con = {.run_type = 0, .run_len = 0};
  return con;
}

static int econtext_add_bit(econtext *con, int bit, uint8_t *out_byte) {
  if (con->run_type == bit) {
    con->run_len++;

    if (con->run_len == RUN_MAX) {
      *out_byte = run_encode(con->run_type, con->run_len);
      con->run_len = 0;
      return 1;
    } else {
      return 0;
    }
  }

  // con->run_type != bit at this point.
  int to_ret = 0;

  if (con->run_len > 0) {
    *out_byte = run_encode(con->run_type, con->run_len);
    to_ret = 1;
  }

  con->run_type = bit;
  con->run_len = 1;

  return to_ret;
}

static int econtext_end_bits(econtext *con, uint8_t *out_byte) {
  if (con->run_len > 0) {
    *out_byte = run_encode(con->run_type, con->run_len);
    return 1;
  } else {
    return 0;
  }
}

/** Encoding functions */
uint8_t *rle_encode(uint8_t *original_data, size_t in_len, size_t *out_len) {
  rcontext rcon = rcontext_init(original_data, in_len);
  econtext econ = econtext_init();
  byte_wcontext wcon = byte_wcontext_init(1024);
  
  int bit = rcontext_read_bit(&rcon);
  uint8_t encoded;
  while (bit >= 0) {
    if (econtext_add_bit(&econ, bit, &encoded))
      byte_wcontext_write(&wcon, encoded);
    bit = rcontext_read_bit(&rcon);
  }

  if (econtext_end_bits(&econ, &encoded))
    byte_wcontext_write(&wcon, encoded);
  
  *out_len = wcon.byte_idx;
  return wcon.buffer;
}

/** Decoding functions */
uint8_t* rle_decode(uint8_t *encoded_data, size_t in_len, size_t *out_len) {
  bit_wcontext wcon = bit_wcontext_init(1024);

  for (size_t i = 0; i < in_len; i++) {
    uint8_t run = encoded_data[i];
    int type = run_decode_type(run);
    int len = run_decode_len(run);

    for (int j = 0; j < len; j++) {
      bit_wcontext_write(&wcon, type);
    }
  }

  if (wcon.bit_idx != 0) {
    free(wcon.buffer);
    return NULL;
  } else {
    *out_len = wcon.byte_idx;
    return wcon.buffer;
  }
}
