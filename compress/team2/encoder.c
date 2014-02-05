#include <string.h>
#include <assert.h>
#include "internal.h"
#include "encoder.h"

static void DEBUG_PRINT_BITS(uint8_t byte) {
    for (int i = 7; i >= 0; i--) {
        printf("%c", ((byte >> i) & 0x1) + '0');
    }
}


static void DEBUG_PRINT_BYTES(uint8_t bytes[], int len) {
    for (int i = 0; i < len; i++) {
        DEBUG_PRINT_BITS(bytes[i]);
        printf(" ");
    }
}


static void SET_BIT(int index, int value, uint8_t *byte) {
    assert(index < 8); assert(value == 0 || value == 1);
    /*         Clear the bit         Set it to 'value' */
    *byte = (*byte & ~(1 << index)) | value << index;
}

static int build_bits(struct huff_enc_entry * entry, char * str_bits) {
    memset(entry->bits, 0, sizeof(entry->bits));
    for (int i = 0; i < entry->bitlen; i++) {
        SET_BIT(7 - (i % 8), str_bits[i] - '0', &entry->bits[i / 8]);
    }
    /*
    printf("Got table: %s\n", str_bits);
    int bitlen = entry->bitlen;
    int trans_bytes = (bitlen / 8) + (bitlen % 8 != 0);
    printf("Trans: "); DEBUG_PRINT_BYTES(entry->bits, trans_bytes);
    printf("\n");
    */
    return 0;
}

int huff_make_encoder(struct huff_encoder * encoder, char *ttable[256]) {
    encoder->buffer = 0;
    encoder->buffer_used = 0;
    for (int i = 0; i < 256; i++) {
        encoder->table[i].bitlen = strlen(ttable[i]);
        //printf("Building for: %d\n", i);
        build_bits(&encoder->table[i], ttable[i]);
    }
    return 0;
}

int huff_encode(uint8_t byte, uint8_t output[32], struct huff_encoder *encoder) {
    uint8_t buffer[33];
    memset(buffer, 0, sizeof(buffer));
    int packed = 0;
    int bitlen = encoder->table[byte].bitlen;

    /* get the number of bytes this byte translates too, rounded up. */
    int trans_bytes = (bitlen / 8) + (bitlen % 8 != 0);

    buffer[0] = encoder->buffer;
    memcpy(buffer + 1, encoder->table[byte].bits, trans_bytes);

    /*
    printf("S Buffer: "); DEBUG_PRINT_BYTES(buffer, trans_bytes + 1);
    printf("\n");
    printf("Trans: "); DEBUG_PRINT_BYTES(encoder->table[byte].bits, trans_bytes);
    printf("\n");
    */

    for (int i = 1; i < trans_bytes + 1; i++) {
        buffer[i - 1] |= buffer[i] >> encoder->buffer_used;
        buffer[i] = buffer[i] << (8 - encoder->buffer_used);
        //printf("looping.\n");
    }

    bitlen += encoder->buffer_used;
    packed = bitlen / 8;
    encoder->buffer_used = bitlen % 8;
    encoder->buffer = buffer[packed];

    memcpy(output, buffer, packed);

    /*
    printf("Encoding: %d '%c'\n"
           "Packed Len: %d\n"
           "Leftover Bits: %d\n"
           "Saved Buffer: ", byte, byte, packed, encoder->buffer_used);
    DEBUG_PRINT_BITS(encoder->buffer);
    printf("\nSend Buffer: "); DEBUG_PRINT_BYTES(output, packed);
    printf("\n");
    */

    return packed;
}
