#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "internal.h"
#include "huff.h"

static bool IS_BYTE(short path) {
    return path < 0;
}

static bool IS_BRANCH(short path) {
    return ! IS_BYTE(path);
}

static short BYTE_INDEX(short path) {
    return -(path + 1);
}

static char MIN_CHAR(char a, char b) {
    return a < b ? a : b;
}

/* Represents a node which points to other nodes. */
struct node {
    /* The tree paths. If a path is non-negative, represents an index into
       nodes. Else, |zero + 1| represents the byte value at pointed to leaf. */
    short paths[2];
};

struct tree {
    /* The nodes of the tree. nodes[0] is the root. */
    struct node nodes[255];
};

struct prioritized_node {
    uint64_t priority;
    /* If positive, represents an index into branches. If negative, |zero + 1|
       represents the byte value at pointed to leaf. */
    short node;
    uint8_t smallest_byte;
};

int compare_prioritized_nodes(const void *a, const void *b) {
    struct prioritized_node *node_a = (struct prioritized_node *) a;
    struct prioritized_node *node_b = (struct prioritized_node *) b;

    int result = node_a->priority - node_b->priority;
    return result == 0 ? node_a->smallest_byte - node_b->smallest_byte : result;
}

/* A Huffman table specifies an encoding for all 256 bytes as a null terminated
   string: char * HuffmanTable[256] */

void fill_table(char *code, int node, struct tree *tree,
               char *out_table[256]) {
    for (int i = 0; i < 2; i++) {
        int code_length = strlen(code);
        char new_code[code_length + 2];
        strcpy(new_code, code);
        new_code[code_length] = i + '0';
        new_code[code_length + 1] = 0;

        short path = tree->nodes[node].paths[i];
        if (IS_BYTE(path)) {
            out_table[BYTE_INDEX(path)] = xmalloc((strlen(new_code) + 1));
            strcpy(out_table[BYTE_INDEX(path)], new_code);
        } else {
            fill_table(new_code, path, tree, out_table);
        }
    }
}

int leaf_check(int node, int has_char[256], const struct tree *tree) {
    assert(node > -256);
    assert(node < 255);

    int result = 0;
    for (int i = 0; i < 2; i++) {
        short path = tree->nodes[node].paths[i];
        if (IS_BYTE(path)) {
            assert(has_char[BYTE_INDEX(path)] == 0);
            has_char[BYTE_INDEX(path)] = 1;
        }
        result += IS_BYTE(path) ?
            1 : leaf_check(tree->nodes[node].paths[i], has_char, tree);
    }

    return result;
}

int node_check(int node, const struct tree *tree) {
    int result = 1;

    for (int i = 0; i < 2; i++) {
        result += IS_BYTE(tree->nodes[node].paths[i]) ?
            1 : node_check(tree->nodes[node].paths[i], tree);
    }

    return result;
}

int check_tree(const struct tree *tree) {
    int has_char[256];
    memset(has_char, 0, 256 * sizeof(int));
    /* Make sure we have 256 unique leaves. */
    int leaves = leaf_check(0, has_char, tree);
    assert(leaves == 256);
    /* Make sure we saw all 256 leaves. */
    for (int i = 0; i < 256; i++) {
        assert(has_char[i] == 1);
    }
    /* Make sure we have 511 nodes (including implicit leaves). */
    assert(node_check(0, tree) == 511);

    return 1;
}

int check_table(char *table[256]) {
    for (int i = 0; i < 256; i++) {
        assert(strlen(table[i]) > 0);

        char c;
        for (int j = 0; (c = *(table[i] + j)) != 0; j++) {
            assert(c == '0' || c == '1');
        }
    }

    return 1;
}

/* Compression
----------------------------------------------------------------------------- */

/* Returns a new translation table generated from an array of 256
   unsigned long longs representing the number of times the byte index has
   appeared in a file. Allocates (strlen(i) + 1) * 8 memory for each string. */
int huff_make_table(uint64_t freq[256], char *out_table[256]) {
    struct prioritized_node node_list[256];

    for (int i = 0; i < 256; i++) {
        node_list[i] = (struct prioritized_node) { .priority = freq[i],
                                                   .node = BYTE_INDEX(i),
                                                   .smallest_byte = i };
    }

    /* Fill the tree backwards so the last element added, which will be
       the root of the tree, will also be the first item in the nodes array */
    struct tree tree;
    for (int i = 0; i < 255; i++) {
        qsort(node_list + i, 256 - i, sizeof(struct prioritized_node),
              compare_prioritized_nodes);
        int huff_index = 254 - i;
        tree.nodes[huff_index] =
            (struct node) { .paths = { node_list[i].node,
                                       node_list[i + 1].node } };
        node_list[i + 1] =
            (struct prioritized_node) {
                .priority = node_list[i].priority + node_list[i + 1].priority,
                .node = huff_index,
                .smallest_byte = MIN_CHAR(node_list[i].smallest_byte,
                                          node_list[i + 1].smallest_byte) };
    }

    assert(check_tree(&tree) == 1);

    fill_table("", 0, &tree, out_table);

    assert(check_table(out_table) == 1);

    return 1;
}

/* Decompression
----------------------------------------------------------------------------- */

struct decoder {
    struct tree tree;
    short current_node;
};

/* Frees a decoder struct. Returns 1 on success, 0 otherwise. */
int huff_free_decoder(struct decoder *decoder) {
    free(decoder);
    return 1;
}

/* Returns a pointer to a new decoder struct generated from a
   translation table, which is an array of 256 char *s which are the ASCII
   representations of that byte index's translation. Returns the null pointer
   if any errors occur. */
struct decoder *huff_make_decoder(char *table[256]) {
    assert(check_table(table) == 1);

    /* calloc will not only make our tree completely empty, but will
       also initialize current_node to 0 which is the root and where decoding
       should always start. */
    struct decoder *decoder = calloc(1, sizeof(struct decoder));
    if (decoder == NULL) {
        return NULL;
    }
    /* Represents the next "unallocated" node. */
    int next_empty = 1;

    for (int i = 0; i < 256; i++) {
        int current_node = 0;

        int j;
        /* Check table[i][j + 1] because our last path is an implicit node. */
        for (j = 0; table[i][j + 1] != 0; j++) {
            int direction = table[i][j] - '0';
            if (decoder->tree.nodes[current_node].paths[direction] == 0) {
                assert(next_empty < 255);
                decoder->tree.nodes[current_node].paths[direction] = next_empty;
                next_empty++;
            }
            current_node = decoder->tree.nodes[current_node].paths[direction];
        }

        int direction = table[i][j] - '0';
        assert(decoder->tree.nodes[current_node].paths[direction] == 0);
        decoder->tree.nodes[current_node].paths[direction] == BYTE_INDEX(i);
    }

    assert(check_tree(&decoder->tree));

    return decoder;
}

/* Takes the next bit to decode. Returns an unsigned char converted to an int if
   a character is decoded, returns -1 otherwise. If an error occurs, -2 or lower
   is returned */
int huff_decode(int bit, struct decoder *decoder) {
    assert(bit == 0 || bit == 1);

    decoder->current_node =
        decoder->tree.nodes[decoder->current_node].paths[bit];

    int result = -1;
    if (IS_BYTE(decoder->current_node)) {
        result = BYTE_INDEX(decoder->current_node);
        decoder->current_node = 0;
    }
    return result;
}
