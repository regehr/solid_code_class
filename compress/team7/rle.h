/**
 * Author: Spencer Phippen
 *
 * Contains functions for in-memory RLE encoding and decoding.
 */

#ifndef HUFF_RLE_H
#define HUFF_RLE_H

#include <stdint.h>
#include <stdlib.h>

/** RLE-encodes the given data.
 * @param original_data A pointer to a buffer where the data to be encoded is.
 * @param in_len The length of the original_data buffer.
 * @param out_len Contains the size of the returned buffer on return.
 * @return A buffer containing the RLE-encoded data.
 *         Pass to free when you're done with it.
 */
uint8_t *rle_encode(uint8_t *original_data, size_t in_len, size_t *out_len);

/** RLE-decodes the given data.
 * @param original_data A pointer to a buffer where the data to be decoded is.
 * @param in_len The length of the original_data buffer.
 * @param out_len Contains the size of the returned buffer on return.
 *                Contents are undefined if function returns NULL.
 * @return A buffer containing the decoded data, or NULL if the RLE data is malformed.
 *         Pass to free when you're done with it.
 */
uint8_t *rle_decode(uint8_t *encoded_data, size_t in_len, size_t *out_len);

#endif // HUFF_RLE_H
