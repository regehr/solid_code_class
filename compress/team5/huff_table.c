/* Jake Guckert */

/* struct used to represent a node
	in the huffman tree. */
typedef struct node() {
	struct node *left_node;
	struct node *right_node;

}
/* struct used to represent 1 row 
	in the frequency table for a file. */
typedef struct frequency_row() {
	char c;
	unsigned int frequency;
}

/* Compares two byte frequencies. For bytes with the same 
	frequency, the lower-valued byte goes earlier in the list. */
int compare_frequencies(const void *f1, const void *f2) {	
	return ( *(int*)f1 - *(int*)f2 );
}

/* This will build the frequency table that is used to construct the huffman tree */
void build_frequency_table(char *name, struct frequency_row frequency_table[]) {
	FILE *input_file;
	int current_char;

	input_file = fopen(name, "r");
	
	/* Determine the frequency of occurrence of each byte in the input file. 
		Make a list that contains one element for each byte value. */
	while ((current_char = fgetc(input_file)) != EOF) {
        frequency_table[current_char].frequency++;
    }

    /* The list is sorted by increasing frequency (i.e., least frequently occurring
  		bytes are first). */

    qsort(frequency_table, 256, sizeof(struct frequency_row), compare_frequencies);

    build_huff_tree();
}

void build_huff_tree(struct frequency_row table[]) {

/*Remove the first two elements of the list and combine them into a
  single list element whose frequency is the sum of the frequencies of
  the removed elements. */







}