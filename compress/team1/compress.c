/*
 * Generates huffman tree from character frequencies.
 */

#include "huff_tree.h"

/* Takes a char and returns the matching code *. */
char * get_code(char c)
{
    return table[(uint8_t)c];
}

/* Builds a huffman tree from character frequencies. */
void gen_tree_frq(uint64_t freq[256])
{
    init_nodes();
    byte_freq(freq); /* Determine the frequency of occurrence of each byte in the input file. */
    sort_nodes(256); /* Sort nodes before building tree. */
    build_tree_frq();
#ifdef CHECK_REP
    check_tree();
#endif
    create_table();
    tree_dot();
}

void byte_freq(uint64_t freq[256])
{
    for (int i = 0; i < 256; i++)
        nodes[i]->freq = freq[i];
#ifdef DBG_FRQ
    int i;
    for(i = 0; i < 256; i++)
        printf("%d:\t%llu\n", nodes[i]->c, nodes[i]->freq);
#endif
}

void build_tree_frq()
{
    /* N-1 steps to create tree. */
    for (int i = 0; i < 255; i++)
    {
        /* Remove first two elements. */
        node* node0 = nodes[0];
        node* node1 = nodes[1];
        check_build(node0, node1);
        nodes[0] = NULL;
        nodes[1] = NULL;
        
        /* Combine into new node whose frequency is the sum of frequency of removed nodes. */
        node* new_node;
        
        init_node(&new_node, 0); /* Character value shouldn't matter here because char comparisons are only done on subtree lowest chars. */
        new_node->freq = node0->freq + node1->freq;
        new_node->lowest = node0->lowest < node1->lowest ? node0->lowest : node0->lowest == node1->lowest ? node1->lowest : node1->lowest;
        
        /* New node should contain the removed nodes as subtrees. */
        new_node->left = node0;
        new_node->right = node1;
        
        /* Insert new element into list.*/
        nodes[0] = new_node;
        all_nodes[all_node_curr++] = new_node;
        
        /* Sort. */
        sort_nodes(256);
    }
    
    assert(nodes[0] != NULL);
    for (int i = 1; i < 256; i++)
        assert(nodes[i] == NULL);
    
#ifdef DBG_BLD_TREE
    printf("%d:\t%lld\n", nodes[0]->c, nodes[0]->freq);
#endif
}
