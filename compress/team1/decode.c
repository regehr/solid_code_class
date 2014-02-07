/*
 * Builds huffman tree from huffman table.
 */

#include "huff_tree.h"

void build_tree_tbl();
void init_all_nodes();
bool get_char(char *, char *);

bool char_found = false;
node *curr_node;

/* Takes a huffman code bit. Returns true when
 * matching character is foound. Matching character 
 * is referenced by second parameter. */
bool get_char(char *huff_bit, char *character)
{
    assert(*huff_bit == 48 || *huff_bit == 49);
    if (char_found == true)
    {
        /* Rewind to root node. */
        curr_node = all_nodes[0];
        char_found = false;
    }
    if (*huff_bit == 48 && curr_node->left != NULL)
    {
        curr_node = curr_node->left;
        return false;
    }
    if (*huff_bit == 49 && curr_node->right != NULL)
    {
        curr_node = curr_node->right;
        return false;
    }
    *character = curr_node->c;
    return char_found = true;
}

/* Builds a huffman tree from huffman table. */
void build_tree_tbl(char *huff_table[256])
{
    init_all_nodes();
    /* Create a root node. */
    all_node_curr = 0;
    node *root = all_nodes[all_node_curr++];
    node *curr_node;
    
    /* For each code in the table. */
    for (int i = 0; i < 256; i++)
    {
        /* Always start at the root node for each code. */
        curr_node = root;
        char *curr_char = huff_table[i];
        while (*curr_char != 0)
        {
            assert(*curr_char == 48 || *curr_char == 49);
            if (*curr_char == 48)
            {
                if (curr_node->left == NULL)
                {
                    /* Attach a node. */
                    curr_node->left = all_nodes[all_node_curr++];
                    strcat(strcat(root->left->code, root->code), "0");
                }
                curr_node = curr_node->left;

            }
            if (*curr_char == '1')
            {
                if (curr_node->right == NULL)
                {
                    /* Attach a node. */
                    curr_node->right = all_nodes[all_node_curr++];
                    strcat(strcat(root->right->code, root->code), "1");
                }
                curr_node = curr_node->right;
            }
            curr_char++;
        }
        /* Assign appropriate character to this leaf. */
        curr_node->c = i;
    }
}

void init_all_nodes()
{
    for (int i = 0; i < 512; i++)
    {
        init_node(&all_nodes[i], 0);
    }
}
