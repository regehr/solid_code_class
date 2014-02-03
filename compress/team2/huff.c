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

static bool BYTE_INDEX(short path) {
    return -(path + 1);
}

/* Represents a node which points to other nodes. */
struct HuffmanNode {
    /* The zero path. If positive, represents an index into nodes. If
       negative, |zero + 1| represents the byte value at pointed to leaf. */
    short zero;
    /* The one path. If positive, represents an index into branches. If
       negative, |zero + 1| represents the byte value at pointed to leaf. */
    short one;
};

struct HuffmanTree {
    /* The nodes of the tree. nodes[0] is the root. */
    struct HuffmanNode nodes[255];
};

struct PrioritizedNode {
    uint64_t priority;
    /* If positive, represents an index into branches. If negative, |zero + 1|
       represents the byte value at pointed to leaf. */
    short node;
    uint8_t minbyte;
};

int compareprioritizednodes(const void *a, const void *b) {
    struct PrioritizedNode *nodea = (struct PrioritizedNode *) a;
    struct PrioritizedNode *nodeb = (struct PrioritizedNode *) b;

    int result = nodea->priority - nodeb->priority;
    return result == 0 ? nodea->minbyte - nodeb->minbyte : result;
}

/* A Huffman table specifies an encoding for all 256 bytes as a null terminated
   string: char * HuffmanTable[256] */

void filltable(char *code, int node, struct HuffmanTree *tree,
               char *out_table[256]) {
    short zero = tree->nodes[node].zero;

    char zerostring[strlen(code) + 2];
    strcpy(zerostring, code);
    strcat(zerostring, "0");
    if (IS_BYTE(zero)) {
        out_table[BYTE_INDEX(zero)] = xmalloc((strlen(zerostring) + 1));
        strcpy(out_table[BYTE_INDEX(zero)], zerostring);
    } else {
        filltable(zerostring, zero, tree, out_table);
    }

    short one = tree->nodes[node].one;

    char onestring[strlen(code) + 2];
    strcpy(onestring, code);
    strcat(onestring, "1");
    if (IS_BYTE(zero)) {
        out_table[BYTE_INDEX(zero)] = xmalloc((strlen(onestring) + 1));
        strcpy(out_table[BYTE_INDEX(zero)], onestring);
    } else {
        filltable(onestring, one, tree, out_table);
    }
}

int leafcheck(int nodeindex, int haschar[256], const struct HuffmanTree *tree) {
    assert(nodeindex > -256);
    assert(nodeindex < 255);

    short zero = tree->nodes[nodeindex].zero;
    short one = tree->nodes[nodeindex].one;

    if (IS_BYTE(zero)) {
        assert(haschar[BYTE_INDEX(0)] == 0);
        haschar[BYTE_INDEX(zero)] = 1;
    }

    if (IS_BYTE(one)) {
        assert(haschar[BYTE_INDEX(one)] == 0);
        haschar[BYTE_INDEX(one)] = 1;
    }

    return
        (IS_BYTE(zero) ? 1 : leafcheck(tree->nodes[nodeindex].zero, haschar, tree)) +
        (IS_BYTE(one)  ? 1 : leafcheck(tree->nodes[nodeindex].one, haschar, tree));
}

int nodecheck(int nodeindex, const struct HuffmanTree *tree) {
    return 1 +
        (IS_BYTE(tree->nodes[nodeindex].zero) ?
            1 : nodecheck(tree->nodes[nodeindex].zero, tree)) +
        (IS_BYTE(tree->nodes[nodeindex].one) ?
            1 : nodecheck(tree->nodes[nodeindex].one, tree));
}

int checktree(const struct HuffmanTree *tree) {
    int haschar[256];
    memset(haschar, 0, 256 * sizeof(int));
    /* Make sure we have 256 leaves. */
    int leaves = leafcheck(0, haschar, tree);
    assert(leaves == 256);
    /* Make sure we saw all 256 leaves. */
    for (int i = 0; i < 256; i++) {
        assert(haschar[i] == 1);
    }
    /* Make sure we have 511 nodes (including implicit leaves). */
    assert(nodecheck(0, tree) == 511);

    return 1;
}

int checktable(char *table[256]) {
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
    struct PrioritizedNode nodelist[256];

    for (int i = 0; i < 256; i++) {
        nodelist[i] = (struct PrioritizedNode) { .priority = freq[i],
                                                 .node = BYTE_INDEX(i),
                                                 .minbyte = i };
    }

    /* Fill the HuffmanTree backwards so the last element added, which will be
       the root of the tree, will also be the first item in the nodes array */
    struct HuffmanTree tree;
    for (int i = 0; i < 255; i++) {
        qsort(nodelist + i, 256 - i, sizeof(struct PrioritizedNode),
              compareprioritizednodes);
        int huffindex = 254 - i;
        tree.nodes[huffindex] = (struct HuffmanNode) {
            .zero = nodelist[i].node,
            .one = nodelist[i + 1].node };
        nodelist[i + 1] = (struct PrioritizedNode) {
            .priority = nodelist[i].priority +
                        nodelist[i + 1].priority,
            .node = huffindex,
            .minbyte = nodelist[i].minbyte < nodelist[i + 1].minbyte ?
                       nodelist[i].minbyte : nodelist[i + 1].minbyte };
    }

    assert(checktree(&tree) == 1);

    filltable("", 0, &tree, out_table);

    assert(checktable(out_table) == 1);

    return 1;
}

/* Decompression
----------------------------------------------------------------------------- */


/* Frees a decoder struct. Returns 1 on success, 0 otherwise. */
int huff_free_decoder(struct decoder *);

/* Returns a pointer to a new decoder struct generated from a
   translation table, which is an array of 256 char *s which are the ASCII
   representations of that byte index's translation. */
struct decoder *huff_make_decoder(char *table[]);

/* Takes the next bit to decode. Returns an unsigned char converted to an int if
   a character is decoded, returns -1 otherwise. If an error occurs, -2 or lower
   is returned */
int huff_decode(int bit, struct decoder*);
