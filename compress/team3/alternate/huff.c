//Implemented by Chad Miller Feb. 2013
//Makes a huffman table and prints it to stdout
//Only needs to be adapted to print an existing huffman table

#include "string.h"
#include "csapp.h"
#include <limits.h>


#define NUM_CHARS           257     /* 256 bytes + EOF */
#define COUNT_T_MAX     UINT_MAX    /* based on count_t being unsigned int */
#define EOF_CHAR    (NUM_CHARS - 1) /* index used for EOF */
#define COMBINED      -1      /* node represents multiple characters */


typedef struct node
{
    int value;               /* ascii value of char */
    unsigned int count;      /* number of occurrences of value */
    char ignore;        /* already handled or no need to handle */
    int level;          /* depth in tree (root is 0) */
    struct node *left, *right, *parent;
} node;


typedef struct table_row
{
  int value;
  char code[NUM_CHARS-1];
} table_row;

node *leaves[NUM_CHARS]; /* array of all leaves */


int get_tree(char *in);
node *tree_io(FILE *in_file);
node *build_tree(node **ht, int elements);
static int find_min(node **ht, int elements);
static node *mk_node(int value);
static node *mk_combined_node(node *left, node *right);
void free_tree(node *ht);
void print_list(table_row *list);


/* 
 * main - Main routine 
 */
int main(int argc, char **argv)
{
   
    /* Check command line args */
    if (argc != 3) {
	fprintf(stderr, "usage: %s -t <file>\n", argv[0]);
	exit(255);
    }

    char *in = argv[2];
    get_tree(in);

}


int get_tree(char *inFile){

    FILE *fpIn, *fpOut;
    node *ht;        /* root of tree */
    node *htp;                /* pointer into tree */
    
    table_row *list = (table_row*)Calloc(257, sizeof(struct table_row));

    if ((fpIn = Fopen(inFile, "rb")) == NULL)
      exit(255);


    /* build tree */
    if ((ht = tree_io(fpIn)) == NULL)
    {
        Fclose(fpIn);
        return -1;
    }

    htp = ht;

    char code[NUM_CHARS - 1];
    int depth = 0;           
    int k = 0;
    for(;;)
    {
        /* go left */
        while (htp->left != NULL)
        {
            code[depth] = '0';
            htp = htp->left;
            depth++;
        }

        if (htp->value != COMBINED)
        {
            /* single symbol */
            if (depth == 0)
            {
                code[depth] = '0';
                depth++;
            }

            code[depth] = '\0';
	    table_row *t = &list[htp->value];
	    strcpy(t->code, code);
	    t->value = htp->value;

        }

        while (htp->parent != NULL)
        {
            if (htp != htp->parent->right)
            {
                /* go to the parent's right */
                code[depth - 1] = '1';
                htp = htp->parent->right;
                break;
            }
            else
            {
                /* go up one level */
                depth--;
                htp = htp->parent;
                code[depth] = '\0';
            }
        }

        if (htp->parent == NULL)
        {
            /* done */
            break;
        }
    }

    /* clean up */
    fclose(fpIn);
    free_tree(ht);
    print_list(list);
    Free(list);
    return 1;


}

void print_list(table_row *list){

  int l;
  for (l = 0; l < NUM_CHARS; l++)
      printf("%s\n", list[l].code);

}



node *tree_io(FILE *in_file){

    node *ht;              /* root of tree */
    int c;

    /* allocate leaves for all characters */
    for (c = 0; c < NUM_CHARS; c++)
    {
        if ((leaves[c] = mk_node(c)) == NULL)
        {
            /* allocation failed free */
            for (c--; c >= 0; c--)
            {
                Free(leaves[c]);
            }
            return NULL;
        }
    }

    /*  EOF */
    leaves[EOF_CHAR]->count = 1;
    leaves[EOF_CHAR]->ignore = 0; //false

    /* count each char */
    while ((c = fgetc(in_file)) != EOF)
    {
        if (leaves[c]->count < COUNT_T_MAX)
        {
            /* increment count for char and don't ignore */
            leaves[c]->count++;
            leaves[c]->ignore = 0; //false
        }
        else
        {
            fprintf(stderr,
                "Input file contains too many 0x%02X to count.\n", c);
            return NULL;
        }
    }

    /* put array of leaves into a huffman tree */
    ht = build_tree(leaves, NUM_CHARS);

    return ht;

}


node *build_tree(node **ht, int elements)
{
    int min1, min2;     /* two nodes with the lowest count */

    /* keep looking until no more nodes can be found */
    for (;;)
    {
        /* find node with lowest count */
        min1 = find_min(ht, elements);

        if (min1 == -1)
        {
            /* no more nodes to combine */
            break;
        }

        ht[min1]->ignore = 1;    /* ignore */

        /* find node with second lowest count */
        min2 = find_min(ht, elements);

        if (min2 == -1)
        {
            /* no more nodes to combine */
            break;
        }

        ht[min2]->ignore = 1;    /* ignore */

        /* combine nodes */
        if ((ht[min1] = mk_combined_node(ht[min1], ht[min2])) == NULL)
        {
            return NULL;
        }

        ht[min2] = NULL;
    }

    return ht[min1];
}



static int find_min(node **ht, int elements)
{
    int i;                          /* array index */
    int index = -1;          /* index with lowest count seen so far */
    int count = INT_MAX;     /* lowest count seen so far */
    int level = INT_MAX;     /* level of lowest count seen so far */

    /* sequentially search array */
    for (i = 0; i < elements; i++)
    {
        /* check for lowest count (or equally as low, but not as deep) */
        if ((ht[i] != NULL) && (!ht[i]->ignore) &&
            (ht[i]->count < count ||
                (ht[i]->count == count && ht[i]->level < level)))
        {
            index = i;
            count = ht[i]->count;
            level = ht[i]->level;
        }
    }

    return index;
}






static node *mk_node(int value)
{
    node *ht;

    ht = (node *)(Malloc(sizeof(node)));

    if (ht != NULL)
    {
        ht->value = value;
        ht->ignore = 1;      /* will be FALSE if one is found */

        /* at this point, the node is not part of a tree */
        ht->count = 0;
        ht->level = 0;
        ht->left = NULL;
        ht->right = NULL;
        ht->parent = NULL;
    }

    return ht;
}



static node *mk_combined_node(node *left,
    node *right)
{
    node *ht;

    ht = (node *)(Malloc(sizeof(node)));

    if (ht != NULL)
    {
        ht->value = COMBINED;     /* represents multiple chars */
        ht->ignore = 0; //false
        ht->count = left->count + right->count;     /* sum of children */
        ht->level = max(left->level, right->level) + 1;

        /* attach children */
        ht->left = left;
        ht->left->parent = ht;
        ht->right = right;
        ht->right->parent = ht;
        ht->parent = NULL;
    }

    return ht;
}




void free_tree(node *ht)
{
    if (ht->left != NULL)
    {
        free_tree(ht->left);
    }

    if (ht->right != NULL)
    {
        free_tree(ht->right);
    }

    free(ht);
}


int max(int x, int y){
  return x > y ? x : y;
}











