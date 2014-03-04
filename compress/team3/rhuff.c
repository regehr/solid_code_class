//
// rhuff.c
//
// Jon Parker
// (c) Feb, 2014
//
// Modified by Oscar Marshall.
//
// This program runs a Huffman compression algorithm on a specified file, or decompresses a compressed huffman file
// with the .hurl extension.
//

#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "encodedOutputFileWriter.h"
#include "decodedOutputFileWriter.h"
#include "syscalls.h"
#include "encoder.h"
#include "decoder.h"
#include "rle.c"

#define ENTRIES 256
#define ENTRY_LENGTH 256

/*
 * The mode determines if we compress, decompress, or print out the table to the
 * commandline.
 * Possibilities: -t, -c, or -d
 * If it's -d, file has to be of .hurl extension type.
 */
typedef enum
{
    TABLE_MODE_HURL,
    TABLE_MODE_GENERIC,
    COMPRESS_MODE,
    DECOMPRESS_MODE,
    INVALID_MODE
} eMode;

typedef enum
{
    FILE_SUCCESS,
    FILE_MISSING,
    FILE_INVALID_FORMAT
} eFileCode;


/*
 * Determines if commandline input is the right format.
 */
eMode getModeOfOperation(int argc, char *argv[3])
{
    // Need three arguments: the mode and a .hurl if option is -d.
    if (argc != 3)
    {
        return INVALID_MODE;
    }

    int fileNameLength = strlen(argv[2]);
    bool isHurl = strstr(argv[2], ".hurl\0") != NULL && fileNameLength > 5;
    if (fileNameLength <= 0)
    {
        return INVALID_MODE;
    }
    if (strcmp(argv[1], "-t") == 0)
    {
        if (isHurl)
        {
            return TABLE_MODE_HURL;
        }
        return TABLE_MODE_GENERIC;
    }
    if (strcmp(argv[1], "-c") == 0)
    {
        return COMPRESS_MODE;
    }
    if (strcmp(argv[1], "-d") == 0 && isHurl)
    {
        return DECOMPRESS_MODE;
    }
    return INVALID_MODE;
}

/*
 * This will try to read a .hurl files header (not including the compression table).
 * Reads bytes 0-3 expecting them to be HURL
 * Reads bytes 4-11 expecting them to be bits for a 64 bit integer.
 * Returns the size of the uncompressed file (which is the also the number of huffman symbols in the compressed file).
 */
eFileCode ReadHeader(FILE* pFile, unsigned long long* pHuffmanSize)
{
    int i = 0;
    int c;
    *pHuffmanSize = 0;
    char* header = "HURL";

    assert(pFile != NULL);

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

    assert(i == 64);

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
eFileCode GetTableForGeneric(unsigned long long pFrequencies[ENTRIES], huffResult resultArray[256])
{
    createHuffmanTree(pFrequencies, resultArray);

    return FILE_SUCCESS;
}

/*
 * This function will generate a table of how often each character in a file occurs.
 * The result is stored in pOutFrequencies.
 */
eFileCode GenerateFrequenciesForGeneric(FILE* pFile, unsigned long long pOutFrequencies[256])
{
    assert(pFile != NULL);

    while (true)
    {
        char byte;
        size_t read = xfread(&byte, 1, 1, pFile);

        if (read == 0) return FILE_SUCCESS;

        unsigned index = (unsigned char)byte;
        assert(index < 256);

        pOutFrequencies[index]++;
    }
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
eFileCode GenerateTableAndCompressOrDecompress(eMode huffmanMode, const char *fileName)
{
    eFileCode fileCode; // And error code which tells if the operation was successful or not.

    FILE *pFile = fopen(fileName, "r"); // Open file for reading.
    fileCode = FILE_SUCCESS;

    // Check that file was successfully opened.  If not, return an error code.
    if (pFile == NULL)
    {
        return FILE_MISSING;
    }

    switch(huffmanMode)
    {
        case DECOMPRESS_MODE:
        {
            // If the file is a compressed huffman file, then use the get table for huff function to open it.
            char huffmanEncodings[ENTRIES * ENTRY_LENGTH];
            unsigned long long lengthOfFile =
                huffmanEncodingsFromFile(pFile, huffmanEncodings);

            huffResult resultArray[ENTRIES];
            createHuffResultArrayFromFileEncodings(huffmanEncodings, resultArray);
            huffNode huffmanTree[ENTRIES + ENTRIES - 1];
            createDecodeTreeFromResultArray(resultArray, huffmanTree);
            FILE *rle_file = xtmpfile();
            writeCompressedFileToNonCompressedOutput(pFile, rle_file, lengthOfFile, &huffmanTree[0]);

            rewind(rle_file);
            int nameLength = strlen(fileName) - strlen(".hurl");
            char newFileName[nameLength + 1];
            strncpy(newFileName, fileName, nameLength);
            newFileName[nameLength] = 0;
            FILE *pNewFile = xfopen(newFileName, "w");
            rle_decode(rle_file, pNewFile);

            fclose(rle_file);
            fclose(pNewFile);
            break;
        }

        case TABLE_MODE_HURL:
        {
            // If we want a table and the file is .hurl, it may or may not be the same .hurl we want it to be.
            // We'll try to treat it as a .hurl but if it's the wrong format, we will treat it like a generic
            // file.
            char huffmanEncodings[ENTRIES * ENTRY_LENGTH];
            huffmanEncodingsFromFile(pFile, huffmanEncodings);
            if (huffmanEncodings[0] != 0)
            {
                huffResult resultArray[ENTRIES];
                createHuffResultArrayFromFileEncodings(huffmanEncodings, resultArray);
                printHuffResultArray(resultArray);
            }
            else
            {
                // File was a .hurl, but internally format doesn't fit. Oh well, we can still generate a compression table.
                // Maybe someone else in the world created their own .hurl file format. We need to handle that format.
                fseek(pFile, 0, SEEK_SET);

                // The frequency of occurrence of each character in the uncompressed file.
                unsigned long long pFrequencies[ENTRIES];
                memset(pFrequencies, 0, sizeof(pFrequencies));
                if (GenerateFrequenciesForGeneric(pFile, pFrequencies) == FILE_SUCCESS)
                {
                    huffResult resultArray[ENTRIES];
                    fileCode = GetTableForGeneric(pFrequencies, resultArray);
                }
                else
                {
                    fileCode = FILE_INVALID_FORMAT;
                }
            }
            break;
        }

        case TABLE_MODE_GENERIC:
        {
            // If the file is not a .hurl, then generate frequencies and then a table for the file.
            // The frequency of occurrence of each character in the uncompressed file.
            unsigned long long pFrequencies[ENTRIES];
            memset(pFrequencies, 0, sizeof(pFrequencies));
            if (GenerateFrequenciesForGeneric(pFile, pFrequencies) == FILE_SUCCESS)
            {
                huffResult resultArray[ENTRIES];
                fileCode = GetTableForGeneric(pFrequencies, resultArray);
                printHuffResultArray(resultArray);
            }
            else
            {
                fileCode = FILE_INVALID_FORMAT;
            }
            break;
        }

        case COMPRESS_MODE:
        {
            FILE *rle_file = xtmpfile();

            rle_encode(pFile, rle_file);

            rewind(rle_file);
            unsigned long long pFrequencies[ENTRIES];
            memset(pFrequencies, 0, sizeof(pFrequencies));
            if (GenerateFrequenciesForGeneric(rle_file, pFrequencies) != FILE_SUCCESS)
            {
                fileCode = FILE_INVALID_FORMAT;
                break;
            }
            huffResult resultArray[ENTRIES];
            fileCode = GetTableForGeneric(pFrequencies, resultArray);
            char newFileName[strlen(fileName) + 6];
            strcpy(newFileName, fileName);
            FILE *pNewFile = fopen(strcat(newFileName, ".hurl"), "w+");

            if (pNewFile == NULL)
            {
                fileCode = FILE_INVALID_FORMAT;
                break;
            }
            writeNonCompressedFileToCompressedOutput(rle_file, pNewFile, resultArray);
            fclose(rle_file);
            fclose(pNewFile);
            break;
        }

        default:
        {
            // File must not be valid for the specified commandline options if we get this far.
            fileCode = FILE_INVALID_FORMAT;
            break;
        }
    }

    fclose(pFile);
    return fileCode;
}

int main(int argc, char **argv)
{
    // The mode determines if we compress, decompress, or print out the table to
    // the commandline.
    // Possibilities: -t, -c, or -d
    // If it's -d, file has to be of .hurl extension type.

    // -t, -c, or -d, plus this checks if the file name/extension is valid.
    eMode mode = getModeOfOperation(argc, argv);

    // Ensure proper commandline arguments!
    if (mode == INVALID_MODE)
    {
        fprintf(stderr,
            "Invalid commandline args. Should be:\n%s (-t | -c | -d) file\nOR\n%s -d file.hurl\ni.e.: %s -t MyFile.txt\n",
            argv[0], argv[0], argv[0]);
        return -1;
    }

    // Name of the file passes in as a commandline arg.
    char *fileName = argv[2];
    // `fileCode` used for error handling.
    eFileCode fileCode = GenerateTableAndCompressOrDecompress(mode, fileName);

    // Check if function succeeded.
    if (fileCode != FILE_SUCCESS)
    {
        fprintf(stderr,
            "Invalid File and commandline Parameter combination.\n");
        return -1;
    }

    return 0;
}
