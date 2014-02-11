/*
 * Generates huffman tree from character frequencies.
 */

#include "huff_tree.h"

/* Character nodes. */
static node *nodes[256];

/* Huffman table. */
static char *table[256];

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
    sort_nodes(); /* Sort nodes before building tree. */
    build_tree_frq();
    create_table();
}

void init_nodes()
{
    for (int i = 0; i < 256; i++)
    {
        init_node(&nodes[i], i);
        all_nodes[all_node_curr++] = nodes[i];
    }
}

void byte_freq(uint64_t freq[256])
{
    for (int i = 0; i < 256; i++)
        nodes[i]->freq = freq[i];
}

/* Comparison routine for qsort. */
int compare_nodes(const void* node1, const void* node2)
{
    node **n1 = (node**)node1;
    node **n2 = (node**)node2;
    
    /* Null nodes get sorted to end of array. */
    if (*n1 == NULL)
        return 1;
    if (*n2 == NULL)
        return -1;
    
    if ((*n1)->freq == (*n2)->freq)
        return (*n1)->lowest < (*n2)->lowest ? -1 : (*n1)->lowest == (*n2)->lowest ? 0 : 1;
    
    /* Sort least to greatest. */
    return (*n1)->freq < (*n2)->freq ? -1 : (*n1)->freq == (*n2)->freq ? 0 : 1;
}

void sort_nodes()
{
    qsort(nodes, 256, sizeof(node*), compare_nodes);
}


void check_build(node *node0, node *node1)
{
    assert(node0 != NULL && node1 != NULL); /* Only true if even number of original elements. */
    assert(node0->freq <= node1->freq);
    if (is_leaf(node0) && is_leaf(node1))
        assert(node0->c != node1->c);
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
        node* new_node = NULL;        
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
        sort_nodes();
    }    
    assert(nodes[0] != NULL);
}

void clear_visited()
{
    for (int i = 0; i < 511; i++)
        if (all_nodes[i] != NULL)
            all_nodes[i]->visited = false;
}

/* Depth first search tree traversal from given root node.*/
void dfs(node *root)
{
    assert(root);
    root->visited = true;
    if (root->left != NULL)
    {
        if (root->left->visited == false)
        {
            strcat(strcat(root->left->code, root->code), "0");
            assert(root->freq >= root->left->freq);
            dfs(root->left);
        }
    }
    if (root->right != NULL)
    {
        if (root->right->visited == false)
        {
            strcat(strcat(root->right->code, root->code), "1");
            assert(root->freq >= root->right->freq);
            dfs(root->right);
        }
    }
    if(is_leaf(root))
        table[root->c] = root->code;
    else
        assert(root->c == 0);
}

void create_table()
{
    clear_visited();
    dfs(*nodes);
}
