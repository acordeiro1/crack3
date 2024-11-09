#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "md5.h"

#if __has_include("fileutil.h")
#include "fileutil.h"
#endif

#define PASS_LEN 50     // Maximum length any password will be.
#define HASH_LEN 33     // Length of hash plus one for null.

int compareHashes(const void *a, const void *b) 
{
    char **aa = (char **)a;
    char **bb = (char **)b;

    return strcmp(*aa, *bb);
}

int main(int argc, char *argv[])
{
    if (argc < 3) 
    {
        printf("Usage: %s hash_file dictionary_file\n", argv[0]);
        exit(1);
    }

    // TODO: Read the hashes file into an array.
    //   Use either a 2D array or an array of arrays.
    //   Use the loadFile function from fileutil.c
    //   Uncomment the appropriate statement.
    int size;
    //char (*hashes)[HASH_LEN] = loadFile(argv[1], &size);
    char **hashes = loadFileAA(argv[1], &size);
    
    // CHALLENGE1: Sort the hashes using qsort.
    qsort(hashes, size, sizeof(char*), compareHashes);
    
    // TODO
    // Open the password file for reading.
    FILE *passFile = fopen(argv[2], "r");
    if (!passFile)
    {
        printf("Can't open file\n");
        free(hashes);
        exit(1);
    }

    char password[PASS_LEN];
    int hashesFound = 0;

    // TODO
    // For each password, hash it, then use the array search
    // function from fileutil.h to find the hash.
    // If you find it, display the password and the hash.
    // Keep track of how many hashes were found.
    while (fgets(password, sizeof(password), passFile) != NULL) 
    {
        size_t length = strlen(password);
        if (length > 0 && password[length - 1] == '\n') 
        {
            password[length - 1] = '\0';
        }

        //hash
        char *hash = md5(password, strlen(password)); 

        // CHALLENGE1: Use binary search instead of linear search.
        if (substringSearchAA(hash, hashes, size) != NULL) 
        { 
            printf("Found password: %s with hash: %s\n", password, hash);
            hashesFound++;
        }

        free(hash); 
    }
    
    // TODO
    // When done with the file:
    //   Close the file
    fclose(passFile);

    //   Display the number of hashes found.
    printf("Total hashes found: %d\n", hashesFound);

    //   Free up memory.
    for (int i = 0; i < size; i++) {
        free(hashes[i]);
    }
    free(hashes);

    return 0;

}
