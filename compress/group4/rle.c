/* Team 3 */
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include "rle.h"



/** Private helpers **/
static FILE *Fopen(const char *filename, const char *mode);
static void Fclose(FILE *fp);
static void Fputc(int c, FILE *fp_out);
void *Calloc(size_t nmemb, size_t size);

static void unix_error(char *msg); 
static void count_run(int *bit_count, int *prev_bit, int *curr_bit, int *first_bit, int *index, FILE *fp_in, FILE *fp_out, int *curr_char);
static void run_end(int *bit_count, int *curr_bit, int *prev_bit, FILE *fp_out);
static void write_count(int *bit_count, int *bite_index, FILE *fp_out, int *bite, int curr_bit);
static int get_bit(int *curr_char, FILE *fp_in, int *index);
static void to_array(int *curr_char, int *bit_array);

#define COUNT_MAX 127


int rle_encode(char *in, char *out)
{

    FILE *fp_in = Fopen(in, "rb");
    FILE *fp_out = Fopen(out, "wb");

    int curr_char;
    int curr_bit, prev_bit = EOF;
    int first_bit = 1;
    int index = -1;
    int bit_count = 0;

 while ((curr_bit = get_bit(&curr_char, fp_in, &index)) != -1)
  {
        bit_count = 1;
	
        if (curr_bit == prev_bit)
        {
            /* run has started */
	    bit_count++;
	    count_run(&bit_count, &prev_bit, &curr_bit, &first_bit, &index, fp_in, fp_out, &curr_char);
           if (curr_char == EOF){
              run_end(&bit_count, &prev_bit, &curr_bit, fp_out);
	      goto END;
	   }
	    
        }
        else if (first_bit)
        {
            /* keep looking for run */
            prev_bit = curr_bit;
	    first_bit = 0;
	}
       else 
	{
	    /* no run -- write single bit */
	    run_end(&bit_count, &prev_bit, &curr_bit, fp_out);
	}
	
	index--;
     }

     if (curr_char == EOF) {
       bit_count = 1;
       run_end(&bit_count, &prev_bit, &curr_bit, fp_out);
    }

 END:
    Fclose(fp_out);
    Fclose(fp_in);
    return 1;
}


int rle_decode(char *in, char *out)
{
    FILE *fp_in;                       
    FILE *fp_out;                      
    int curr_char;
    int curr_bit;
    int bit_count = 0;               
    int bite = 0;
    int bite_index = 7;
     
 
   fp_in = Fopen(in, "rb");
    fp_out = Fopen(out, "wb");


    while ((curr_char = fgetc(fp_in)) != EOF)
  {    
        curr_bit = (curr_char >> 7) & 1;
        bit_count = (curr_char & 0x7F);
        write_count(&bit_count, &bite_index, fp_out, &bite, curr_bit);
    }

    Fclose(fp_out);
    Fclose(fp_in);

    return 1;
}


/** I/O Wrappers **/
static FILE *Fopen(const char *filename, const char *mode) 
{
    FILE *fp;

    if ((fp = fopen(filename, mode)) == NULL)
	unix_error("Fopen error");

    return fp;
}


static void Fclose(FILE *fp) 
{
    if (fclose(fp) != 0)
	unix_error("Fclose error");
}


static void Fputc (int c, FILE *fp_out)
{
  if (fputc(c, fp_out) == EOF)
    unix_error("Fputc error");  
}


void *Calloc(size_t nmemb, size_t size) 
{
    void *p;

    if ((p = calloc(nmemb, size)) == NULL)
	unix_error("Calloc error");
    return p;
}


static void unix_error(char *msg) /* unix-style error */
{
    printf("%s\n", msg);
    exit(255);
}



/* Helper functions */
static void count_run(int *bit_count, int *prev_bit, int *curr_bit, int *first_bit, int *index, FILE *fp_in, FILE *fp_out, int *curr_char)
{
  *index = (*index) - 1;
   int temp = 0;
  while ((*curr_bit = get_bit(curr_char, fp_in, index)) != -1)
    {
      if (*curr_bit == *prev_bit)
      {
        (*bit_count)++;

      if (*bit_count == COUNT_MAX)
       {

	 /* run_end(bit_count, prev_bit, curr_bit, fp_out);*/
     	temp |= ((*prev_bit << 7 & 0x80)) | *bit_count; 
        Fputc(temp, fp_out);
	*prev_bit = EOF;
	*bit_count = 0;
        *first_bit = 1; 
 	 break;
       }

      } else {

       /* run has reached its end */
	run_end(bit_count, prev_bit, curr_bit, fp_out);
	/* *first_bit = 0; */
	break;
      }

      (*index)--;
           
    }

}


static void run_end(int *bit_count, int *prev_bit, int *curr_bit, FILE *fp_out)
{
    int bite = 0;
    bite |= ((*prev_bit << 7 & 0x80)) | *bit_count;     
    Fputc(bite, fp_out);
    *prev_bit = *curr_bit;
}


static int get_bit(int *curr_char, FILE *fp_in, int *index)
{

   int *bit_array = (int *)Calloc(8, sizeof(int));
   if((*index) == -1)
    {
      *curr_char = fgetc(fp_in);

      if ((*curr_char) == EOF) {
	return -1;
      }
      
      (*index) = 7;
      to_array(curr_char, bit_array);
      return bit_array[(*index)];
    }
  
   to_array(curr_char, bit_array);
   int temp = bit_array[(*index)];
   free(bit_array);
   return temp;
}


static void to_array(int *curr_char, int *bit_array)
{
  int i;
  for (i = 7; i >= 0; i--)
    {
      bit_array[i] = ((*curr_char) >> i) & 0x1;
    }
}


 static void write_count(int *bit_count, int *bite_index, FILE *fp_out, int *bite, int curr_bit)
{

 while ((*bit_count) > 0)
    {
      (*bite) |= (curr_bit) << (*bite_index);
      (*bite_index)--;
      (*bit_count)--;

      if ((*bite_index) == -1)
     {
      Fputc(*bite, fp_out);
      (*bite_index) = 7;
      (*bite) = 0;
      }       
   }
}
