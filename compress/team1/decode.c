/*
 * Builds huffman tree from huffman table.
 */

#include "huff_tree.h"

void build_tree_tbl();
void init_all_nodes();

bool char_found = true;
node *curr_node;

/* Takes a huffman code bit. Returns true when
 * matching character is foound. Matching character
 * is referenced by second parameter. */
bool get_char(char huff_bit, char *character)
{
    assert(character != NULL);
    assert(huff_bit == 0 || huff_bit == 1);
    if (char_found == true)
    {
        /* Rewind to root node. */
        curr_node = all_nodes[0];
        char_found = false;
    }
    if (huff_bit == 0 && curr_node->left != NULL)
    {
        curr_node = curr_node->left;
    }
    if (huff_bit == 1 && curr_node->right != NULL)
    {
        curr_node = curr_node->right;
    }
    if (curr_node->right == NULL && curr_node->left == NULL)
    {
        *character = curr_node->c;
        char_found = true;
        return true;
    }
    else
        return false;
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
        int string_pos = 0;
        while (huff_table[i][string_pos] != 0)
        {
            char curr = huff_table[i][string_pos++];
            assert(curr == 48 || curr == 49);
            if (curr == 48)
            {
                if (curr_node->left == NULL)
                {
                    /* Attach a node. */
                    curr_node->left = all_nodes[all_node_curr++];
                    strcat(strcat(curr_node->left->code, curr_node->code), "0");
                }
                curr_node = curr_node->left;
                
            }
            if (curr == '1')
            {
                if (curr_node->right == NULL)
                {
                    /* Attach a node. */
                    curr_node->right = all_nodes[all_node_curr++];
                    strcat(strcat(curr_node->right->code, curr_node->code), "1");
                }
                curr_node = curr_node->right;
            }
        }
        /* Assign appropriate character to this leaf. */
        curr_node->c = i;
    }
    tree_dot();
}

void init_all_nodes()
{
    for (int i = 0; i < 512; i++)
    {
        init_node(&all_nodes[i], 0);
    }
}
