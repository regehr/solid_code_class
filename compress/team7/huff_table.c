#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "huff_table.h"
#include "util.h"

/************************ Tree Forwards "private" **************************/
huff_node *create_huff_node(int char_number, long long frequency, char *encoding);
huff_node *create_parent_node(huff_node *left_child, huff_node *right_child);
void set_right_child(huff_node *parent, huff_node *right_child);
void set_left_child(huff_node *parent, huff_node *left_child);
void set_children_nodes(huff_node *parent, huff_node *left_child, huff_node *right_child);
int huff_node_frequency_comparer(const void *a, const void *b);

void insert_encoded_node(huff_node *root, huff_node *node);
huff_node *find_leaf_node(int char_value, huff_node *root);
void free_huff_node(huff_node *node);

void generate_encoding_tree(huff_node *root);
huff_node *build_encoded_tree(huff_node *nodes[]);
void generate_encoding(huff_node *root, char *path);
char *encoding_for_char(int char_value, huff_node *root);

int min(int a, int b);
char *create_string_from_cat(char *start, char *end);


//************************  Tree Code  ****************************//

huff_node *create_huff_tree_from_frequency(unsigned long long frequencyArray[256]) {
    huff_node  *nodes[256];
    for (int i = 0; i < 256; i++) {
        nodes[i] = NULL;
        nodes[i] = create_huff_node(i, frequencyArray[i], NULL);
        
    }
    /*for(int i = 0; i<255; i++){
        assert(nodes[i]->char_number == i+1);
    }
    assert(nodes[255]->char_number == 0);
     */

    // Unfortunately, the old queue-based construction system was just incorrect
    // It gave wrong trees

    // Perform 255 node merges
    for (int firstIndex = 0; firstIndex < 255; firstIndex++) {
      qsort(nodes+firstIndex, 256-firstIndex, sizeof (huff_node *), huff_node_frequency_comparer);

      huff_node* left_child = nodes[firstIndex];
      huff_node* right_child = nodes[firstIndex+1];
      huff_node* new_parent = create_parent_node(left_child, right_child);
      nodes[firstIndex+1] = new_parent;
    }
    huff_node *root = nodes[255];
    generate_encoding_tree(root);
    return root;
}

huff_node *create_huff_tree_from_encoding(char **encoding) {

    huff_node  *nodes[256];
    for (int i = 0; i < 256; i++) {
        nodes[i] = NULL;
        // All node encodings have to be malloc'd (they're freed on destruct)
        char *node_encoding = xmalloc(strlen(encoding[i]) + 1);
        strcpy(node_encoding, encoding[i]);
        nodes[i] = create_huff_node(i, -2, node_encoding);
    }

    huff_node *root = build_encoded_tree(nodes);

    return root;
}

void destroy_huff_tree(huff_node *root) {
    if (root == NULL) {
        return;
    }
    while (root->parent != NULL) {
      root = root->parent;
    }
    free_huff_node(root);
}

char **get_encoding(huff_node *root) {
  char **encodings = xmalloc(sizeof(char*[256]));
  for (int i = 0; i < 256; i++) {
    char *seqence = encoding_for_char(i, root);
    encodings[i] = seqence;
  }
  
  return encodings;
}

int get_next_character(huff_node *root, int one_bit)
{
    static huff_node *current = 0;
    
    if(current == 0){
        current = root;
    }
    
    //character nodes have no children at all
    if(one_bit){
        assert(current->right_child != 0);
        current = current->right_child;
    } else{
        assert(current->left_child != 0);
        current = current->left_child;
    }
    int result = -1;
    int character = current->char_number;
    if(character >= 0){
        result = character;
        current = root;
    }

    return result;
}

huff_node *create_huff_node(int char_number, long long frequency, char *encoding) {
    huff_node *node = (huff_node *)xmalloc(sizeof(huff_node));
    node->left_child = NULL;
    node->right_child = NULL;
    node->char_number = char_number;
    node->lowest_value = char_number;
    node->frequency = frequency;
    node->parent = NULL;
    node->encoding = encoding;
    
    return node;
}

void set_right_child(huff_node *parent, huff_node *right_child){
    assert(parent != 0 && "Parent can't be NULL");
    parent->right_child = right_child;
    if(right_child != 0){
        right_child ->parent = parent;
    }
}

void set_left_child(huff_node *parent, huff_node *left_child){
    assert(parent != 0 && "Parent can't be NULL");
    parent->left_child = left_child;
    if(left_child != 0){
        left_child ->parent = parent;
    }
}

void set_children_nodes(huff_node *parent, huff_node *left_child, huff_node *right_child){
    assert(parent != 0);
    parent->left_child = left_child;
    parent->right_child = right_child;
    if(left_child != 0){
        left_child->parent = parent;
    }
    if(right_child != 0){
        right_child->parent = parent;
    }
}

//Creates a parent node and fills in all fields.
//Sets the left_child and right_child of the parent.
//Sets the parent field of the parent's left and right child.

huff_node *create_parent_node(huff_node *left_child, huff_node *right_child) {
    //create huff_node
    huff_node *parent = create_huff_node( -1, left_child->frequency + right_child->frequency, NULL);
    set_children_nodes(parent, left_child, right_child);
    parent->lowest_value = min(left_child->lowest_value, right_child->lowest_value);
    
    return parent;
}

// Returns negative if huff_node *a has a lower frequency or
// will be the lower ascii value if they have the same frequency.

int huff_node_frequency_comparer(const void  *a, const void  *b) {
    // negative value means a comes before b
    // positive means b comes before a
    huff_node *node_a = *((huff_node **) a);
    huff_node *node_b = *((huff_node **) b);
    int result = node_a->frequency - node_b->frequency;
    if (result == 0) {
        if (node_a->lowest_value < node_b->lowest_value) {
            return -1;
        } else {
            return 1;
        }
    }
    return result;
}

void insert_encoded_node(huff_node *root, huff_node *node){
    int length = strlen(node->encoding);
    char *encoding = node->encoding;
    huff_node *current = root;
    for(int i = 0; i < length; i++){
        if(encoding[i] == '0'){
            if(current->left_child == 0){
                if(i == length-1){
                    current->left_child = node;
                    return;
                } else{
                    huff_node *left_child = create_huff_node(-1, -1,create_string_from_cat(current->encoding, "0"));
                    set_left_child(current, left_child);
                    current = left_child;
                    continue;
                }
            } else{
                    current = current->left_child;
            }
        } 
        //next character is a 1
        else{
            if(current->right_child == 0){
                if(i == length-1){
                    current->right_child = node;
                    return;
                } else{
                    huff_node *right_child = create_huff_node(-1, -1,create_string_from_cat(current->encoding, "1"));
                    set_right_child(current, right_child);
                    current = right_child;
                    continue;
                }
            } else{
                    current = current->right_child;
            }
        }
    }
}

huff_node *build_encoded_tree(huff_node *nodes[]) {
    huff_node *root = NULL;

    // All the encodings in the tree have to be dynamically allocated
    char* root_encoding = xmalloc(1);
    root_encoding[0] = '\0';

    root = create_huff_node(-1, -2, root_encoding);
    
    for(int i = 0;i < 256; i++){
        insert_encoded_node(root, nodes[i]);
    }
    
    return root;
}

// Sets the encoding field of every node in the tree.
// To be called on the root of the tree.

void generate_encoding_tree(huff_node *root) {
    assert(root != NULL);

    char *encoding = (char *)xmalloc(1);
    encoding[0] = '\0';

    root->encoding = encoding;
    generate_encoding(root->right_child, "1");
    generate_encoding(root->left_child, "0");
    
}

// Recursive depth-first tree encoding method.
void generate_encoding(huff_node *node, char *path) {
    if (node == NULL) {
        return;
    }
    char *parent_encoding = node->parent->encoding;
    char *encoding = create_string_from_cat(parent_encoding, path);
    node->encoding = encoding;
    generate_encoding(node->left_child, "0");
    generate_encoding(node->right_child, "1");
}

// Frees this roots subtree before itself.
// Returns if node is NULL

void free_huff_node(huff_node *node) {
    if (node == NULL) {
        return;
    }
    if (node->left_child != NULL) {
      free_huff_node(node->left_child);
    }
    if (node->right_child != NULL) {
      free_huff_node(node->right_child);
    }
    if (node->encoding != NULL) {
      free(node->encoding);
    }
    free(node);
}

// Finds the huff_node * that contains char ascii value

huff_node *find_leaf_node(int char_value, huff_node *root) {

    if (root == NULL) {
        return NULL;
    }
    if (root->char_number == char_value) {
        return root;
    }
    huff_node *result = find_leaf_node(char_value, root->left_child);
    if (result == NULL) {
        result = find_leaf_node(char_value, root->right_child);
    }
    return result;
}

// Gets the encoding for the specified character value.
char *encoding_for_char(int char_value, huff_node *root) {
    huff_node *node = find_leaf_node(char_value, root);
    assert(node != NULL);
    return node->encoding;
}

//Returns the smaller of the 2 ints.
int min(int a, int b) {
    if (a > b) {
        return b;
    } else {
        return a;
    }
}

char *create_string_from_cat(char *start, char *end) {
  size_t length_s = strlen(start);
  size_t length_e = strlen(end);
  size_t total_length = length_s + length_e + 1;
  char *new_string = (char *)xmalloc(total_length);
  strncpy(new_string, start, length_s + 1);
  strncat(new_string, end, length_e);
  return new_string;
}

//**************************** End Tree Code  *****************************//


/*************************  Check Reps *****************************/
// Notably empty...
