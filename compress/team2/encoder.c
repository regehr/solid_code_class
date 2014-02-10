#include <string.h>
#include <stdint.h>
#include <assert.h>
#include "common.h"
#include "encoder.h"

static void SET_BIT(int index, int value, uint8_t *byte) {
    assert(index < 8); assert(value == 0 || value == 1);
    /*         Clear the bit         Set it to 'value' */
    *byte = (*byte & ~(1 << index)) | value << index;
}

static void build_bits(struct huff_enc_entry * entry, char * str_bits) {
    memset(entry->bits, 0, sizeof(entry->bits));
    for (int i = 0; i < entry->bitlen; i++) {
        SET_BIT(7 - (i % 8), str_bits[i] - '0', &entry->bits[i / 8]);
    }
}

void huff_make_encoder(struct huff_encoder * encoder, char *ttable[256]) {
    encoder->buffer = 0;
    encoder->buffer_used = 0;
    for (int i = 0; i < 256; i++) {
        encoder->table[i].bitlen = strlen(ttable[i]);
        build_bits(&encoder->table[i], ttable[i]);
    }
}

int huff_encode(uint8_t byte, uint8_t output[32], struct huff_encoder *encoder) {
    uint8_t buffer[33];
    memset(buffer, 0, sizeof(buffer));
    int packed = 0;
    int bitlen = encoder->table[byte].bitlen;

    /* get the number of bytes this byte translates too, rounded up. */
    int trans_bytes = (bitlen / 8) + (bitlen % 8 ? 1 : 0);

    buffer[0] = encoder->buffer;
    memcpy(buffer + 1, encoder->table[byte].bits, trans_bytes);

    for (int i = 1; i < trans_bytes + 1; i++) {
        buffer[i - 1] |= buffer[i] >> encoder->buffer_used;
        buffer[i] = buffer[i] << (8 - encoder->buffer_used);
    }

    bitlen += encoder->buffer_used;
    packed = bitlen / 8;
    encoder->buffer_used = bitlen % 8;
    encoder->buffer = buffer[packed];

    memcpy(output, buffer, packed);
    return packed;
}
