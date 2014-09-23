/*
 * File:   main.c
 * Author: Ryan
 *
 * Created on September 18, 2014, 2:23 PM
 */

/**
 * HEADERS
 */

#include <stdio.h>      /* printf, NULL */
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include <math.h>
#include <string.h>

/**
 * DEFINES
 */

#define OUTPUT 1
#define ARRAYLEN 7


/**
 * TYPEDEFS
 */

typedef struct DBA_t DBA;
typedef struct DBArow_t highest;
typedef char bool;

/**
 * STRUCTS
 */

struct DBArow_t {
    int max, index;
};

struct DBA_t {
    int length;
    bool array[ARRAYLEN][ARRAYLEN];
    highest winner;
};


/**
 * PROTOTYPES
 */

void fillDBA(DBA * data, bool fill);
void printDBAHeader(DBA * data);
void printDBAArray(DBA * data);
void printDBAWinner(DBA * data);
int searchDBAArray(DBA * data, bool needle);


/**
 * LOGIC
 */


int main(int argc, char** argv) {
    DBA * data; // Pointer to our DD array object

    // Setup data
    srand(time(NULL)); // Set random generator seed
    data = malloc(sizeof (DBA)); // Create our DD array object
    data->length = ARRAYLEN; // Set n x n DD array size

    // Core work
    if (OUTPUT) {
        printf("sizeof data (outside function): %d\n", sizeof * data);
        printDBAHeader(data); // Print random info about our object
    }
    fillDBA(data, 1); // Fill with random amount per row
    searchDBAArray(data, 1); // Search and find row with most amount
    if (OUTPUT) printDBAArray(data); // Print array
    printDBAWinner(data); // Print winning row information

    // Clean up our object
    free(data); // Free the memory associated with our object
    data = NULL; // Replace value with null

    return (EXIT_SUCCESS);
}

/**
 * Fill object double dimension array with random amount per row
 * @param data Pointer to DD array
 * @param fill Object to fill with
 */
void fillDBA(DBA * data, bool fill) {
    int i, j, randAmt,
            length = data->length; // Set local var for our data set height/width

    // Fill with passed type
    for (i = 0; i < length; i++) { // Row
        randAmt = length - (rand() % length); // Gen random between 0 and length

        for (j = 0; j < length; j++) { // Column
            if (j < (length - randAmt)) {
                data->array[i][j] = 0; // Before reaching random fill amount
            } else {
                data->array[i][j] = fill; // After reaching random fill amount
            }
        }
    }
}

/**
 * Print out memory information about the DD array
 * @param data Pointer to DD array
 */
void printDBAHeader(DBA * data) {
	// Print object info
	printf("\t%s\t\t%s\t%s\t%s\n"
		"%s\t%d\t\t%d\t\t%d\t\t%d\n"
		"%s\t%p\t%p\t%p\t%p\n"
		"%s\tn/a\t\t%d\t\tn/a\t\tn/a\n",
		"data", "data.length", "data.array", "data.winner",
		"sizeof", sizeof * data, sizeof data->length, sizeof data->array, sizeof data->winner,
		"address", &data, &data->length, &data->array, &data->winner,
		"value", data->length);
}

/**
 * Print out array values of the DD array
 * @param data Pointer to DD array
 */
void printDBAArray(DBA * data) {
    int i, j;

	// Print boolean matrix
	printf("\n{"); // Print
	for (i = 0; i < data->length; i++) {
		(i > 0) ? printf(" {") : printf("{"); // Conditional print
		for (j = 0; j < data->length; j++) {
			printf("%d", data->array[i][j]); // Print
			if (j < data->length - 1) printf(","); // Conditional print
		}
		(i < (data->length) - 1) ? printf("}\n") : printf("}"); // Conditional print
	}
	printf("}\n\n"); // Print
}

/**
 * Print the matching index array information
 * @param data DD boolean array
 */
void printDBAWinner(DBA * data) {
    int i;

    printf("Winner Index: %d\nMax Count: %d\nArray: {", data->winner.index, data->winner.max); // Print
    for (i = 0; i < data->length; i++) {
        printf("%d", (i < (data->length - data->winner.max)) ? 0 : 1); // Print
		if (i < data->length - 1) { printf(","); } // Conditional print
    }
    printf("}\n"); // Print
}

/**
 * Search through each row and determine which has highest number of needle
 * @param data Pointer to DD array
 * @param needle object to search for
 * @return
 */
int searchDBAArray(DBA * data, bool needle) {
    int i, j;

    for (i = 0; i < data->length; i++) { // Horizontal traversal from left to right
        for (j = data->length; j > 0; j--) { // Vertical traversal from bottom to top
            if (data->array[j][i] == needle) {  // Match needle
                data->winner.max = data->length - i; // Capture X position (length) of match
                data->winner.index = j; // Capture row index number
                return 1; // exit function - done!
            }
        }
    }
}
