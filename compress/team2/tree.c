#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stdint.h>

#include "common.h"
#include "tree.h"

static bool IS_BYTE(short path) {
    return path >= -256 && path <= -1;
}

static bool IS_BRANCH(short path) {
    return path >= 0 && path <= 255;
}

static bool IS_SUBBRANCH(short path) {
    return IS_BRANCH(path) && path != 0;
}

static bool IS_PATH(short index) {
    return IS_BRANCH(index) || IS_BYTE(index);
}

static short BYTE_INDEX(short path) {
    return -(path + 1);
}

static uint8_t MIN_UINT8(uint8_t a, uint8_t b) {
    return a < b ? a : b;
}

static bool IS_CODE(const char *string) {
    short i;
    for (i = 0; string[i] != 0; i++) {
        char c = string[i];
        if ((c != '0' && c != '1') || i > 255)
            return false;
    }
    return i > 0;
}

struct prioritized_node {
    uint64_t priority;
    /* If positive, represents an index into branches. If negative, |zero + 1|
       represents the byte value at pointed to leaf. */
    short node;
    uint8_t smallest_byte;
};

static int compare_prioritized_nodes(const void *a, const void *b) {
    struct prioritized_node *node_a = (struct prioritized_node *) a;
    struct prioritized_node *node_b = (struct prioritized_node *) b;


    if (node_a->priority > node_b->priority)
        return 1;
    else if (node_a->priority < node_b->priority)
        return -1;
    else
        /* Subtraction of non-negative numbers cannot overflow */
        return (int)node_a->smallest_byte - (int)node_b->smallest_byte;
}

/* A Huffman table specifies an encoding for all 256 bytes as a null terminated
   string: char * HuffmanTable[256] */

static void fill_table(const char *code, short node, const struct tree *tree,
        char *out_table[256]) {
    assert(IS_CODE(code) || *code == 0);
    assert(IS_PATH(node));

    if (IS_BYTE(node)) {
        out_table[BYTE_INDEX(node)] = xmalloc((strlen(code) + 1));
        strcpy(out_table[BYTE_INDEX(node)], code);
        return;
    }

    for (short i = 0; i < 2; i++) {
        size_t code_length = strlen(code);
        char new_code[code_length + 2];
        strcpy(new_code, code);
        /* Append '0' or '1' to the string */
        new_code[code_length] = (char)i + '0';
        new_code[code_length + 1] = 0;

        short path = tree->nodes[node].paths[i];

        assert(IS_CODE(new_code));
        assert(IS_SUBBRANCH(path) || IS_BYTE(path));
        fill_table(new_code, path, tree, out_table);
    }
}

/* Returns the number of leaves in this subtree. Fills has_char with true for
   every leaf byte index. */
static int check_leaves(short node, bool has_char[256], const struct tree *tree) {
    assert(IS_PATH(node));

    if (IS_BYTE(node)) {
        assert(has_char[BYTE_INDEX(node)] == false);
        has_char[BYTE_INDEX(node)] = true;
        return 1;
    }

    int result = 0;

    for (short i = 0; i < 2; i++) {
        short path = tree->nodes[node].paths[i];

        assert(IS_SUBBRANCH(path) || IS_BYTE(path));
        result += check_leaves(path, has_char, tree);
    }

    return result;
}

static bool check_tree(const struct tree *tree) {
    bool has_char[256];
    memset(has_char, 0, 256 * sizeof(bool));
    /* Make sure we have 256 unique leaves. */
    int leaves = check_leaves(0, has_char, tree);
    assert(leaves == 256);
    /* Make sure we saw all 256 leaves. */
    for (short i = 0; i < 256; i++)
        assert(has_char[i] == 1);

    return true;
}

static bool check_table(const char *const table[256]) {
    for (short i = 0; i < 256; i++)
        assert(IS_CODE(table[i]));

    return true;
}

/* Compression
----------------------------------------------------------------------------- */

/* Returns a new translation table generated from an array of 256
   unsigned long longs representing the number of times the byte index has
   appeared in a file. Allocates (strlen(i) + 1) * 8 memory for each string. */
void huff_make_table(const uint64_t freq[256], char *out_table[256]) {
    struct prioritized_node node_list[256];
    for (short i = 0; i < 256; i++) {
        node_list[i] = (struct prioritized_node) {
            .priority = freq[i],
            .node = BYTE_INDEX(i),
            .smallest_byte = (uint8_t)i };
    }

    /* Fill the tree backwards so the last element added, which will be
       the root of the tree, will also be the first item in the nodes array */
    struct tree tree;
    for (short i = 0; i < 255; i++) {
        qsort(node_list + (unsigned short)i, 256 - (unsigned short)i,
                sizeof(struct prioritized_node), compare_prioritized_nodes);
        short huff_index = 254 - i;
        tree.nodes[huff_index] = (struct node) {
            .paths = {
                node_list[i].node,
                node_list[i + 1].node } };
        node_list[i + 1] = (struct prioritized_node) {
            /* We assume max file size is UINT64_MAX so the addition of all
               frequencies must be less than UINT64_MAX. Therefore, overflow is
               impossible. */
            .priority = node_list[i].priority + node_list[i + 1].priority,
            .node = huff_index,
            .smallest_byte = MIN_UINT8(node_list[i].smallest_byte,
                    node_list[i + 1].smallest_byte) };
    }

    assert(check_tree(&tree) == true);

    fill_table("", 0, &tree, out_table);

    assert(check_table((const char *const *)out_table) == true);
}

/* Decompression
----------------------------------------------------------------------------- */

/* Returns a pointer to a new decoder struct generated from a
   translation table, which is an array of 256 char *s which are the ASCII
   representations of that byte index's translation. Returns zero on
   success, non-zero on failure. Should not fail. */
void huff_make_decoder(struct huff_decoder *decoder,
                       const char * const table[256]) {
    assert(check_table(table) == true);

    /* initialize current_node to 0 which is the root and where decoding
       should always start. */
    memset(decoder, 0, sizeof(struct huff_decoder));

    /* Represents the next "unallocated" node. */
    short next_empty = 1;

    for (short i = 0; i < 256; i++) {
        short current_node = 0;

        for (short j = 0; ; j++) {
            assert(j <= 254);

            short direction = table[i][j] - '0';
            short *path = &decoder->tree.nodes[current_node].paths[direction];
            /* Check table[i][j + 1] because our last path is to an implicit
               node. */
            if (table[i][j + 1] == 0) {
                assert(*path == 0);
                *path = BYTE_INDEX(i);
                break;
            }
            if (*path == 0) {
                assert(IS_SUBBRANCH(next_empty));
                *path = next_empty;
                next_empty++;
            }
            current_node = *path;
        }

    }

    assert(check_tree(&decoder->tree));
}

/* Takes the next bit to decode. Returns an unsigned char converted to an int if
   a character is decoded, returns -1 otherwise. If an error occurs, -2 or lower
   is returned */
int huff_decode(int bit, struct huff_decoder *decoder) {
    assert(bit == 0 || bit == 1);
    assert(check_tree(&decoder->tree));

    decoder->current_node =
        decoder->tree.nodes[decoder->current_node].paths[bit];

    if (IS_BYTE(decoder->current_node)) {
        int result = BYTE_INDEX(decoder->current_node);
        decoder->current_node = 0;
        return result;
    }
    return -1;
}
