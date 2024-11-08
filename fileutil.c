#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "fileutil.h"

// DIRECTIONS
// Choose whether you are doing the 2D array or
// the array of arrays.
// For the 2D array,
//    implement loadFile2D, substringSearch2D, and free2D.
// For the array of arrays, 
//    implement loadFileAA, substringSearchAA, and freeAA.


// Load the text file from the given filename.
// Return a pointer to the array of strings.
// Sets the value of size to be the number of valid
// entries in the array (not the total array length).
char ** loadFileAA(char *filename, int *size)
{
	FILE *in = fopen(filename, "r");
	if (!in)
	{
	    perror("Can't open file");
	    exit(1);
	}
	
	// TODO
	int capacity = 10;
	*size = 0;
	// Allocate memory for an array of strings (arr).
	char **arr = malloc(capacity * sizeof(char*));

	char temp[1000]; // Temporary buffer to hold each line

	// Read the file line by line.
	while (fgets(temp, sizeof(temp), in) != NULL) //if it reaches the end of file
    {
    //   Trim newline.
        size_t length = strlen(temp);
        if (length > 0 && temp[length - 1] == '\n') 
        {
            temp[length - 1] = '\0';
        }

	//   Expand array if necessary (realloc). size = capacity
	    if (*size == capacity)
        {
            capacity += 10;

	//   Allocate memory for the string (str).
	 	    char **str = realloc(arr, capacity * sizeof(char *));
		    if (!str) 
            {
                printf("Memory reallocation failed\n");
                for (int i = 0; i < *size; i++) 
                {
                    free(arr[i]);
                }
                free(arr);
                fclose(in);
                exit(1);
            }
            arr = str;
        }

	//   Attach the string to the large array (assignment =).
        arr[*size] = malloc(strlen(temp) + 1);
        if (!arr[*size]) 
        {
            for (int i = 0; i < *size; i++) 
            {
                free(arr[i]);
            }
            free(arr);
            fclose(in);
            exit(1);
        }
	//   Copy each line into the string (use strcpy).
	    strcpy(arr[*size], temp);
        
	// The size needs to be incremented inside the loop.
	    (*size)++;
	}
    // Close the file.
	fclose(in);
	
	
	// Return pointer to the array of strings.
	return arr;
}

// Search the array for the target string.
// Return the found string or NULL if not found.
char * substringSearchAA(char *target, char **lines, int size)
{
	for (int i = 0; i < size; i++)
    {
        if (strstr(lines[i], target) != NULL)
        {
            return lines[i];
        }
    }
	return NULL;
}

// Free the memory used by the array
void freeAA(char ** arr, int size)
{
	for (int i = 0; i < size; i++) 
	{
        free(arr[i]); // Free each string
    }
	free(arr);
}