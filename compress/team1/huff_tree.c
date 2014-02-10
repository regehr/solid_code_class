/*
 * Builds huffman table from frequency of characters.
 */

#include "huff_tree.h"

//#define DBG_FRQ
//#define DBG_SORT
//#define DBG_BLD_TREE
//#define DBG_TABLE
//#define GEN_DOT
//#define CHECK_REP


void init_nodes()
{
    for (int i = 0; i < 256; i++)
    {
        init_node(&nodes[i], i);
        all_nodes[all_node_curr++] = nodes[i];
    }
}

void init_node(node **n, char c)
{
    (*n) = malloc_n(*n);
    for (int i = 0; i < 257; i++)
       (*n)->code[i] = 0;
    (*n)->left = NULL;
    (*n)->right = NULL;
    (*n)->freq = 0;
    (*n)->visited = false;
    (*n)->c = c;
    (*n)->id = serial++;
    (*n)->lowest = c;
}

void free_huff_tree()
{
    for (int i = 0; i < 511; i++)
        free(all_nodes[i]);
}

void clear_visited()
{
    for (int i = 0; i < 511; i++)
        if (all_nodes[i] != NULL)
            all_nodes[i]->visited = false;
}

char find_lowest(node *root)
{
    clear_visited();
    char lowest = root->c;
    dfs(root, &lowest);
    return lowest;
}

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
    {
        return (*n1)->lowest < (*n2)->lowest ? -1 : (*n1)->lowest == (*n2)->lowest ? 0 : 1;
    }
    
    /* Sort least to greatest. */
    return (*n1)->freq < (*n2)->freq ? -1 : (*n1)->freq == (*n2)->freq ? 0 : 1;
}

void sort_nodes(int count)
{
    dfs_type = SORT;
    qsort(nodes, count, sizeof(node*), compare_nodes);
    
    for (int j = 256; j > 512; j++)
        assert(all_nodes[j] == NULL);
}

void check_build(node *node0, node *node1)
{
    assert(node0 != NULL && node1 != NULL); /* Only true if even number of original elements. */
    assert(node0->freq <= node1->freq);
    if (is_leaf(node0) && is_leaf(node1))
        assert(node0->c != node1->c);
}

void check_tree()
{
    dfs_type = CHECK;
    clear_visited();
    dfs(*nodes, NULL);
}

void create_table()
{
    dfs_type = TABLE;
    clear_visited();
    dfs(*nodes, NULL);
}

void dfs(node *root, void *p)
{
    if (dfs_type == CHECK)
        assert(root);
    root->visited = true;
    if (root->left != NULL)
    {
        if (root->left->visited == false)
        {
            if (dfs_type == DOT)// && root->right->freq > 0)
                fprintf((FILE *)p, "%d -> %d [color=\"red\" label=\"0\"];\n", root->id, root->left->id);
            if (dfs_type == TABLE)
                strcat(strcat(root->left->code, root->code), "0");
            if (dfs_type == CHECK)
                assert(root->freq >= root->left->freq);
            dfs(root->left, p);
        }
    }
    if (root->right != NULL)
    {
        if (root->right->visited == false)
        {
            if (dfs_type == DOT)// && root->right->freq > 0)
                fprintf((FILE *)p, "%d -> %d [color=\"blue\" label=\"1\"];\n", root->id, root->right->id);
            if (dfs_type == TABLE)
                strcat(strcat(root->right->code, root->code), "1");
            if (dfs_type == CHECK)
                assert(root->freq >= root->right->freq);
            dfs(root->right, p);
        }
    }
    if(is_leaf(root))
    {
        if (dfs_type == SORT && root->c < *(char *)p)
            *(char *)p = root->c;
        if (dfs_type == TABLE)
        {
            table[root->c] = root->code;
#ifdef DBG_TABLE
            printf("%c:\t%llu\t%s\n", root->c, root->freq, root->code);
#endif
        }
    }
    else
        if (dfs_type == CHECK)
            assert(root->c == 0);
}

void tree_dot()
{
    dfs_type = DOT;
    clear_visited();
    FILE *dot = fopen("tree.dot", "w");
    fputs("digraph G {\n", dot);
    for (int i = 0; i < 511; i++)
    {
        node * n = all_nodes[i];
        if (n->freq > 0)
        {
            if (i > 31 && i < 127 && i != 34 && all_nodes[i]->freq > 0)
                fprintf(dot, "%u [label=\"'%c' frq: %llu code:%s\"];\n", n->id, n->c, n->freq, n->freq > 0 ? n->code : "");
            else if (i < 256)
                fprintf(dot, "%u [label=\"\\%u'frq: %llu code:%s\"];\n", n->id, n->c, n->freq, n->freq > 0 ? n->code : "");
            else
                fprintf(dot, "%u [color=\"green\" shape=\"box\" label=\"INNER %.2Lf%%\"];\n", n->id, ((long double)n->freq / (long double)nodes[0]->freq) * 100);
        }
    }
    
    dfs(all_nodes[0], dot);
    fputs("}", dot);
    fclose(dot);
}

bool is_leaf(node *n)
{
    if (n->left == NULL && n->right == NULL)
        return true;
    return false;
}

node * malloc_n(node *n)
{
    n = (node*)malloc(sizeof(node));
    if (n == NULL)
    {
        fprintf(stderr, "Failed to allocate memory.");
        exit(ERR_CODE);
    }
    return n;
}
