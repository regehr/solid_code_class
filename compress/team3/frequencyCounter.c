//
//  FrequencyCounter.c
//  huff
//
//  Created by Adam Bradford on 2/2/14.
//  Copyright (c) 2014 Adam Bradford. All rights reserved.
//

#include <stdio.h>
#include <assert.h>
void generateFrequencyTable(FILE* file, long long length, unsigned *frequencys )
{
    long long i;
    
    for(i= 0; i< 256; i++)
    {
        frequencys[i] = 0;
    }
    
    for(i = 0; i < length; i++)
    {
        unsigned char currentByte;
        size_t err = fread( &currentByte , 1, 1 , file);
        assert(err == 1);
        frequencys[(int) currentByte]++;
    }
}

void printFrequencyArray(unsigned* frequencies)
{
    for(int i = 0; i < 256; i++)
    {
        printf("%02d: %d\n",i,frequencies[i]);
        
    }
}