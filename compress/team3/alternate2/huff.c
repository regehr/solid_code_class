//
// Huff.c
//
// Jon Parker
// (c) Feb, 2014
//
// This program runs a Huffman compression algorithm on a specified file, or decompresses a compressed huffman file
// with the .huff extension.
//

#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#define ENTRIES 256
#define ENTRY_LENGTH 256

/*
 * The mode determines if we compress, decompress, or print out the table to the commandline.
 * Possibilities: -t, -c, or -d
 * If it's -d, file has to be of .huff extension type.
 */
typedef enum {TABLE_MODE_HUFF, TABLE_MODE_GENERIC, COMPRESS_MODE, DECOMPRESS_MODE, INVALID_MODE} eMode;
typedef enum {FILE_SUCCESS, FILE_MISSING, FILE_INVALID_FORMAT} eFileCode;


/*
 * Determines if commandline input is the right format.
 */
eMode getModeOfOperation(int argc, char **argv)
{
    // Need three commandline arguments, the right mode, and a .huff if option is -d.
    int isThreeArgs = argc == 3;
    if (!isThreeArgs)
    {
        return INVALID_MODE;
    }

    int isT = !strcmp(argv[1], "-t"); // strcmp returns 0 when strings are equal.
    int isC = !strcmp(argv[1], "-c");
    int isD = !strcmp(argv[1], "-d");
    int isHuff = strstr(argv[2], ".huff\0") != NULL;
    int isValidFileName = strlen(argv[2]);

    if (isT && isHuff)
    {
        return TABLE_MODE_HUFF;
    }
    else if (isT && isValidFileName)
    {
        return TABLE_MODE_GENERIC;
    }
    else if (isC && isValidFileName)
    {
        return COMPRESS_MODE;
    }
    else if (isD && isHuff)
    {
        return DECOMPRESS_MODE;
    }
    else
    {
        return INVALID_MODE;
    }
}

/*
 * This will try to read a .huff files header (not including the compression table).
 * Reads bytes 0-3 expecting them to be HUFF
 * Reads bytes 4-11 expecting them to be bits for a 64 bit integer.
 * Returns the size of the uncompressed file (which is the also the number of huffman symbols in the compressed file).
 */
eFileCode ReadHeader(FILE* pFile, unsigned long long* pHuffmanSize)
{
    int i = 0;
    int c;
    char* header = "HUFF";

    // First check the first four letters to see if they are valid.
    for (i = 0, c = fgetc(pFile); i < 4 && c == header[i] && c != EOF; i++, c = fgetc(pFile));

    if (i < 4)
    {
        return FILE_INVALID_FORMAT;
    }

    for (i = 0, c = fgetc(pFile); i < 64 && c != EOF; i += 8, c = fgetc(pFile))
    {
        *pHuffmanSize &= ((char) c) << i; // Little endian, so as address increases we become more significant.
    }

    if (i < 64)
    {
        return FILE_INVALID_FORMAT;
    }

    return FILE_SUCCESS;
}

/*
 * This function will go through a .huff and extract the compression table at the top of the file.
 * The compression table is returned in pOutCompressionTable.
 *
 * File stream is expected to already be in the proper location for this call to succeed (must be
 * at the beginning of the compression table section, byte 12).
 */
eFileCode GetTableForHuff(FILE* pFile, unsigned long long huffmanSize, char pOutCompressionTable[ENTRIES][ENTRY_LENGTH])
{
    int i;
    char* line;

    // Go through the next 256 lines of the file, read them out line by line.
    for (i = 0; i < ENTRIES && fgets(pOutCompressionTable[i], ENTRY_LENGTH, pFile) != NULL; i++);

    // If there weren't 256 entries, the .huff was an invalid format.
    if (i < ENTRIES)
    {
        return FILE_INVALID_FORMAT;
    }

    return FILE_SUCCESS;
}

/*
 * Given a table of frequencies as an input, this function will generate the compression table.
 * Caller must pass in an empty compression table to be filled by this function, and a table
 * of character frequencies.
 *
 * Table will have 256 entries and look like:
 * 01001
 * 001
 * 0111
 * ...
 * 00001
 */
eFileCode GetTableForGeneric(unsigned long long pFrequencies[ENTRIES], char pOutCompressionTable[ENTRIES][ENTRY_LENGTH])
{
    return FILE_SUCCESS;
}

/*
 * This function will generate a table of how often each character in a file occurs.
 * The result is stored in pOutFrequencies.
 */
eFileCode GenerateFrequenciesForGeneric(FILE* pFile, unsigned long long pOutFrequencies[ENTRIES])
{
    int c;

    for (c = fgetc(pFile); c != EOF; c = fgetc(pFile))
    {
        pOutFrequencies[c]++;
    }

    return FILE_SUCCESS;
}

/*
 * Given a valid huffman mode, this function will generate the compression table that lists the codes for each
 * of the ascii characters that the compression scheme uses.  That table is placed into the pOutTable passed
 * in by the caller.
 *
 * Table will have 256 entries and look like:
 * 01001
 * 001
 * 0111
 * ...
 * 00001
 */
eFileCode GenerateTable(eMode huffmanMode, char* fileName, char pOutTable[ENTRIES][ENTRY_LENGTH])
{
    FILE* pFile;
    unsigned long long huffmanSize; // The size of the decompressed file, also the number of Huffman codes in the compressed data of the .huff
    unsigned long long pFrequencies[ENTRIES] = {0}; // The frequency of occurrence of each character in the uncompressed file.
    eFileCode fileCode; // And error code which tells if the operation was successful or not.
        
    pFile = fopen(fileName, "r"); // Open file for reading.
    fileCode = FILE_SUCCESS;

    // Check that file was successfully opened.  If not, return an error code.
    if (pFile == NULL)
    {
        return FILE_MISSING;
    }
    else if (huffmanMode == DECOMPRESS_MODE)
    {
        // If the file is a compressed huffman file, then use the get table for huff function to open it.
        if (ReadHeader(pFile, &huffmanSize) == FILE_SUCCESS)
        {
            fileCode = GetTableForHuff(pFile, huffmanSize, pOutTable);
        }
        else 
        {
            fileCode = FILE_INVALID_FORMAT;
        }
    }
    else if (huffmanMode == TABLE_MODE_HUFF)
    {
        // If we want a table and the file is .huff, it may or may not be the same .huff we want it to be.
        // We'll try to treat it as a .huff but if it's the wrong format, we will treat it like a generic
        // file.
        if(ReadHeader(pFile, &huffmanSize) == FILE_SUCCESS && GetTableForHuff(pFile, huffmanSize, pOutTable) == FILE_SUCCESS)
        {
            fileCode = FILE_SUCCESS;
        }
        else
        {
            // File was a .huff, but internally format doesn't fit. Oh well, we can still generate a compression table.
            // Maybe someone else in the world created their own .huff file format. We need to handle that format.
            fseek(pFile, 0, SEEK_SET);
            
            if (GenerateFrequenciesForGeneric(pFile, pFrequencies) == FILE_SUCCESS)
            {
                fileCode = GetTableForGeneric(pFrequencies, pOutTable);
            }
            else
            {
                fileCode = FILE_INVALID_FORMAT;
            }
        }
    }
    else if (huffmanMode == TABLE_MODE_GENERIC || huffmanMode == COMPRESS_MODE)
    {
        // If the file is not a .huff, then generate frequencies and then a table for the file.
        if (GenerateFrequenciesForGeneric(pFile, pFrequencies) == FILE_SUCCESS)
        {
            fileCode = GetTableForGeneric(pFrequencies, pOutTable);
        }
        else
        {
            fileCode = FILE_INVALID_FORMAT;
        }
    }
    else
    {
        // File must not be valid for the specified commandline options if we get this far.
        fileCode = FILE_INVALID_FORMAT;
    }

    fclose(pFile);
    return fileCode;
}

int main(int argc, char **argv)
{
    // The mode determines if we compress, decompress, or print out the table to the commandline.
    // Possibilities: -t, -c, or -d
    // If it's -d, file has to be of .huff extension type.
    eMode mode;
    char* fileName; // Name of the file passes in as a commandline arg.
    char pTable[ENTRIES][ENTRY_LENGTH] = {0}; // The table of 010101001 codes for each ascii character.
    eFileCode fileCode; // Used for error handling.

    mode = getModeOfOperation(argc, argv); // -t, -c, or -d, plus this checks if the file name/extension is valid.

    // Ensure proper commandline arguments!
    if (mode == INVALID_MODE)
    {
        fprintf(stderr, "Invalid commandline args. Should be:\nhuff (-t | -c) file\nOR\nhuff -d file.huff\ni.e.: ./huff -t MyFile.txt\n");
        return 255;
    }
    
    fileName = argv[2];
    fileCode = GenerateTable(mode, fileName, pTable);

    // Check if function succeeded.
    if (fileCode != FILE_SUCCESS)
    {
        fprintf(stderr, "Invalid File and commandline Parameter combination.\n");
        return 255;
    }

    return 0;
}
