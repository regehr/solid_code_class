//
//  FrequencyCounter.h
//  huff
//
//  Created by Adam Bradford on 2/2/14.
//  Copyright (c) 2014 Adam Bradford. All rights reserved.
//

#ifndef huff_FrequencyCounter_h
#define huff_FrequencyCounter_h

//pass in the input file, lenght and an array in which you wish to put the results.
//the frequencies must have a length of 256 or greater, but only 256 bins will be used
void generateFrequencyTable(FILE* inputFile, long long length, unsigned *frequencys );

//I bet you can figure out what this does....
void printFrequencyArray(unsigned* frequencies);

#endif
