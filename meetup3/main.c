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

#define DEBUG 1
#define ARRAYLEN 40


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
    char row[ARRAYLEN];
};

struct DBA_t {
    int length;
    char drink[255];
    bool array[ARRAYLEN][ARRAYLEN];
    highest winner;
};


/**
 * PROTOTYPES
 */

void fillDBA(DBA * data, bool fill);
void randomizeDBA(DBA * data, bool fill);
void printDBAHeader(DBA * data);
void printDBAArray(DBA * data);
void printDBAWinner(DBA * data);
void searchDBAArray(DBA * data, bool needle);


/**
 * LOGIC
 */

/* I have no clue how I managed to get this thing working */
int main(int argc, char** argv) {
    int i, j;
    DBA * data;

    // Setup data
    data = malloc(sizeof (DBA));
    strcpy(data->drink, "Smithwick's Irish Ale!");
    data->length = ARRAYLEN;

    // Print info, fill array, print again, randomize array, print again, search, print winner
    printDBAHeader(data);
    fillDBA(data, 1);
    printDBAArray(data);
    randomizeDBA(data, 0);
    printDBAArray(data);
    searchDBAArray(data, 1);
    printDBAWinner(data);

    // Free the struct
    free(data);
    data = NULL;
    
    return (EXIT_SUCCESS);
}

/**
 * Fill object double dimension array
 * @param data Pointer to DD array
 * @param fill Object to fill with
 */
void fillDBA(DBA * data, bool fill) {
    int i, j;

    // Fill with passed type
    for (i = 0; i < data->length; i++) {
        for (j = 0; j < data->length; j++) {
            data->array[i][j] = fill;
        }
    }
}

/**
 * Generate a random number between zero and length of array to determine fill
 * quantity from left, removing the need for a randomly filled 0 & 1 sorting
 * @param data Pointer to DD array
 * @param fill Object to fill with
 */
void randomizeDBA(DBA * data, bool fill) {
    int i, j,
            curRand, fillNum,
            length = data->length, // Set local var for our data set height/width
            size = sizeof data->array[0][0]; // Determine size of each element

    // Randomize each row
    for (i = 0; i < length; i++) {
        // Keep adding and overflowing seed integer each iteration
        srand(curRand += time(NULL) * 80088008 + 69696969);

        // Subtract random number (between 0 and length) from length
        fillNum = length - (rand() % (length + 1));

        // Test print info
        printf("[%d] memset(%p, %d, %d*%d);\n", i, data->array[i], fill, fillNum, size);

        // Access current row's array and fill with zeros from left side
        // note: memset works with bytes! Not index numbers!
        memset(data->array[i], fill, fillNum * size);
    }
}

/**
 * Print out memory information about the DD array
 * @param data Pointer to DD array
 */
void printDBAHeader(DBA * data) {
    int i, j;

    if (data) {
        // Print object info
        printf("%s: %dB\n"
                "%s: %p\t%s: %p\n"
                "%s: %d\n"
                "%s: %s\n"
                "%s: %d\n"
                "%s: %p\n",
                "sizeof (DBA)", sizeof (DBA),
                "&data", data, "&data+1", data + 1,
                "sizeof data->drink", sizeof data->drink,
                "data->drink", data->drink,
                "strlen(data->drink)", strlen(data->drink),
                "&(data->drink)", &(data->drink));
    }

}

/**
 * Print out array values of the DD array
 * @param data Pointer to DD array
 */
void printDBAArray(DBA * data) {
    int i, j;

    if (data) {
        // Print boolean matrix
        printf("\n{");
        for (i = 0; i < data->length; i++) {
            (i > 0) ? printf(" {") : printf("{");
            for (j = 0; j < data->length; j++) {
                printf("%d", data->array[i][j]);
                (j < data->length - 1) ? printf(",") : printf("");
            }
            (i < (data->length) - 1) ? printf("}\n") : printf("}");
        }
        printf("}\n\n");
    }
}

void printDBAWinner(DBA * data) {
    int i = data->winner.index, j;

    printf("Winner Index: %d\nMax Count: %d\nArray: ", data->winner.index, data->winner.max);
    printf("{");
    for (j = 0; j < data->length; j++) {
        printf("%d", data->array[i][j]);
        (j < data->length - 1) ? printf(",") : printf("");
    }
    printf("}\n");
}

/**
 * Search through each row and determine which has most of needle
 * @param data Pointer to DD array
 * @param needle object to search for
 * @return 
 */
void searchDBAArray(DBA * data, bool needle) {
    int i, j, counter,
            length = data->length;

    for (i = 0; i < length; i++) {
        counter = 0; // Reset counter per row

        for (j = 0; j < length; j++) {
            if (data->array[i][j] == needle)
                counter++;
            
            if ((j + data->winner.max) > length)
                continue;
        }

        // Post loop assessment
        if (counter >= data->winner.max) {
            data->winner.max = counter; // Capture number of matches
            data->winner.index = i; // Capture row index number
        }
    }
}
