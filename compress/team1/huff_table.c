/*
 *
 */

#include "huff_table.h"

//#define DBG_FRQ
#define DBG_SORT
//#define DBG_BLD_TREE
//#define DBG_TABLE
#define GEN_DOT

unsigned s;


struct node
{
    unsigned serial;
    char code[256];
    struct node *left; /* The left child of this node. Null if leaf node. */
    struct node *right; /* The right child of this node. Null if leaf node. */
    uint64_t freq; /* The frequency of this node. Combined value if non-leaf node. */
    bool visited; /* Used for searching algorithms. */
    char c; /* The character this node represents. Null if non-leaf node. */
};

node *all_nodes[511];
int all_node_curr = 0;

void gen_huff_table(uint64_t freq[256], char *table[256])
{
    node *nodes[256];
    init_nodes(nodes);
    byte_freq(nodes, freq); /* Determine the frequency of occurrence of each byte in the input file. */
    sort_nodes(nodes); /* Sort nodes before building tree. */
    build_tree(nodes);
    create_compression_table(nodes, table);
    
#ifdef GEN_DOT
    tree_dot(*nodes);
#endif
    
    for (int i = 0; i < 511; i++)
        free(all_nodes[i]);
}

/* Initialize node. */
void init_node(node **n, char c)
{
    *n = (node*)malloc(sizeof(node));
    for (int i = 0; i < 256; i++)
        (*n)->code[i] = 0;
    (*n)->left = NULL;
    (*n)->right = NULL;
    (*n)->freq = 0;
    (*n)->visited = false;
    (*n)->c = c;
    (*n)->serial = s++;
}

/* Initialize all nodes. */
void init_nodes(node *nodes[256])
{
    for (int i = 0; i < 256; i++)
    {
        init_node(&nodes[i], i);
        all_nodes[all_node_curr++] = nodes[i];
    }
}

/* Copys file stream data to int array.
 * Creates a count af each possible character.
 */
void byte_freq(node **nodes, uint64_t freq[256])
{
    for (int i = 0; i < 256; i++)
    {
        nodes[i]->freq = freq[i];
    }
#ifdef DBG_FRQ
    int i;
    for(i = 0; i < 256; i++)
    {
        printf("%d:\t%llu\n", nodes[i]->c, nodes[i]->freq);
    }
#endif
}

/* Sets all nodes to unvisited. */
void clear_visited()
{
    for (int i = 0; i < 511; i++)
    {
        if (all_nodes[i] != NULL)
            all_nodes[i]->visited = false;
    }
}

/* Depth first search tree traversal from given root node.
 * Sets second parameter to the node with lowest valued
 * character in subtree. */
void dfs(node *root, char *lowest)
{
    root->visited = true;
    if (root->left != NULL)
    {
        if (root->left->visited == false)
        {
            
            dfs(root->left, lowest);
        }
    }
    if (root->right != NULL)
    {
        if (root->right->visited == false)
        {
            
            dfs(root->right, lowest);
        }
    }
    if(root->left == NULL && root->right == NULL)
    if (root->c < *lowest)
        *lowest = root->c;
}

/* Helper function for recursive depth first search.
 * Assumes root node of subtree has the lowest byte
 * valued character.
 */
char find_lowest(node *root)
{
    clear_visited();
    char lowest = root->c;
    dfs(root, &lowest);
    return lowest;
}

/* Comparison routine for qsort. Ugly because of so many ifs
 * but it wouldn't work with fewer comparisons. */
int compare_nodes(const void* node1, const void* node2)
{
    node **n1 = (node**)node1;
    node **n2 = (node**)node2;
    
    /* Null nodes get sorted to end of array. */
    if (*n1 == NULL)
        return 1;
    
    if (*n2 == NULL)
        return -1;
    
    /* If the two node frequencies are equal, the element
     * whose subtree, which may number zero nodes, contains
     * the lowest valued byte is sorted earlier. */
    if ((*n1)->freq == (*n2)->freq)
    {
        char a = find_lowest(*n1);
        char b = find_lowest(*n2);
        if (a > b)
            return -1;
        if (a == b)
            return 0;
        return 1;
    }
    if( (*n1)->freq < (*n2)->freq)
        return -1; /* Sort least to greatest. */
    return 1;
}

/* Sort length nodes in specified array.
 */
void sort_nodes(node **nodes)
{
    qsort(nodes, 256, sizeof(node*), compare_nodes);
    
#ifdef DBG_SORT
    int i;
    for(i = 0; i < 256; i++)
    {
        if (nodes[i] != NULL)
            printf("%c:\t%lld\n", nodes[i]->c, nodes[i]->freq);
    }
#endif
}

void build_tree(node **nodes)
{
    /* N-1 steps to create tree. */
    for (int i = 0; i < 255; i++)
    {
        /* Remove first two elements. */
        node* node1 = nodes[0];
        node* node2 = nodes[1];
        nodes[0] = NULL;
        nodes[1] = NULL;
        
        /* Combine into new node whose frequency is the sum of frequency of removed nodes. */
        node* new_node;
        init_node(&new_node, 0); /* Character value shouldn't matter here because char comparisons are only done on leaf nodes. */
        new_node->freq = (*node1).freq + (*node2).freq;
        
        /* New node should contain the removed nodes as subtrees. */
        new_node->left = node1;
        new_node->right = node2;
        
        /* Insert new element into list.*/
        nodes[0] = new_node;
        all_nodes[all_node_curr++] = new_node;
        
        /* Sort. */
        sort_nodes(nodes);
    }
    
#ifdef DBG_BLD_TREE
    printf("%d:\t%lld\n", nodes[0]->c, nodes[0]->freq);
    for (int i = 1; i < 256; i++)
        assert(nodes[i] == NULL);
#endif
}

/* Depth first search tree traversal from given root node. */
void code_dfs(node *root, char *table[256])
{
    root->visited = true;
    if (root->left != NULL)
    {
        if (root->left->visited == false)
        {
            strcat(strcat(root->left->code, root->code), "0");
            code_dfs(root->left, table);
        }
    }
    if (root->right != NULL)
    {
        if (root->right->visited == false)
        {
            strcat(strcat(root->right->code, root->code), "1");
            code_dfs(root->right, table);
        }
    }

    if(root->right == NULL && root->left == NULL);
    {
        /* This might be a good place to get information from leaf nodes. */
        table[root->c] = root->code;
        #ifdef DBG_TABLE
        printf("%c:\t%llu\t%s\n", root->c, root->freq, root->code);
        #endif
    }

}

/* Builds a compression table from huffman tree. */
void create_compression_table(node **nodes, char *table[256])
{
    clear_visited();
    code_dfs(*nodes, table);
}

/* Depth first search tree traversal from given root node.
 * Sets second parameter to the node with lowest valued
 * character in subtree. */
void tree_dot_dfs(node *root, FILE *dot)
{
    root->visited = true;
    if (root->left != NULL)
    {
        if (root->left->visited == false)
        {
            fprintf(dot, "%d -> %d;\n", root->serial, root->left->serial);
            tree_dot_dfs(root->left, dot);
        }
    }
    if (root->right != NULL)
    {
        if (root->right->visited == false)
        {
            fprintf(dot, "%d -> %d;\n", root->serial, root->right->serial);
            tree_dot_dfs(root->right, dot);
        }
    }
}

void tree_dot(node *root)
{
    clear_visited();
    FILE *dot = fopen("tree.dot", "w");
    fputs("digraph G {\n", dot);
    for (int i = 0; i < 511; i++)
    {
        if (i < 91 && i > 47)
            fprintf(dot, "%u [label=\"%c: %llu\"];\n", all_nodes[i]->serial, all_nodes[i]->c, all_nodes[i]->freq);
        else
            fprintf(dot, "%u [label=\"%u: %llu\"];\n", all_nodes[i]->serial, all_nodes[i]->c, all_nodes[i]->freq);
    }

    tree_dot_dfs(root, dot);
        fputs("}", dot);
    fclose(dot);
}


