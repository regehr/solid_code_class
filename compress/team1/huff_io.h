//
//  huff_io.h
//  Compress
//
//  Created by Andres Monroy on 2/3/14.
//  Copyright (c) 2014 Andres Monroy. All rights reserved.
//

#ifndef Compress_huff_io_h
#define Compress_huff_io_h

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#define MAGIC_NUM "HUFF"
#define HUFF_EXT ".huff"


bool is_huff_file(char* filename);

bool is_huff_header(FILE* file);

bool write_huff_header(FILE* file);

bool get_huff_table(FILE* file);

#endif
