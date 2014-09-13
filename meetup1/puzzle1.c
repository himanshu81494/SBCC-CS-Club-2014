/*
 * File:   main.c
 * Author: Ryan
 *
 * Created on September 6, 2014, 1:01 PM
 */

#include <stdio.h>
#include <stdlib.h>

void bruteForce(int* data, int dataLength);
void mirrorLine(int* data, int dataLength);
void printIntPtrInfo(int* data, int dataLength);

/*
 *
 */
int main(int argc, char** argv) {
    int data[] = {1,2,3,4,5,6};
    int dataLen = sizeof data/sizeof data[0];

    printIntPtrInfo(data, dataLen);
    bruteForce(data, dataLen);
    //mirrorLine(data, dataLen);

    return (EXIT_SUCCESS);
}

void bruteForce(int* data, int dataLength) {

    // Setup environment
    int resultWidth = 2 * dataLength - 1,
        result[resultWidth][resultWidth],  // Create double dimension array for result
        startNdx = 0, endNdx = resultWidth,  // Logic limits
        i, j, k;  // Looping counters (due to pre c99 warnings)


    // Flood double dimension array with input data
    for (i = 0; i < dataLength; i++) {  // Traverse input array
        for (j = startNdx; j < endNdx; j++) { // Y axis
            for (k = startNdx; k < endNdx; k++) { // X axis
                result[j][k] = data[i];
            }
        }
        startNdx++;
        endNdx--;
    }

    // Print results
    printf("Brute force method. Lots of overwriting.\n{");
    for (i=0; i < resultWidth; i++) {
        if ( i > 0) { printf(" "); } // Conditional formatting
        printf("{");
        for (j=0; j < resultWidth; j++) {
            printf("%d", result[i][j]);
            if (j < resultWidth-1) { printf(" "); } // Conditional formatting
        }
        printf("}");
        if (i < resultWidth-1) { printf("\n"); } // Conditional formatting
    }
    printf("}\n\n");
}

void mirrorLine(int* data, int dataLength) {

    // Setup environment
    int resultWidth = 2 * dataLength - 1,
        result[resultWidth][resultWidth],
        diagNdx, dataNdx,
        fillPos, fillLength = resultWidth,
        i, j;


    for (diagNdx = 0; diagNdx < resultWidth; diagNdx++) {  // Traverse result array length
	// Each step diagonally adjusts the fill margins by a factor of two;
        // one from each border. To account for the mirror line reversal we can
        // use modulus to reset the margins and reverse the traversal direction.
        //   Moving towards center: + X traversal, - Y traversal, - length
        //   Moving away from center: - X traversal, + Y traversal, + length
        //
        // reminder: result[Y][X]

        // Increment or decrement the data[] index position based on current index within result[]
        if (diagNdx < dataLength) {
            dataNdx = diagNdx;
        } else {
            dataNdx--;
        }

        // The length to travel from the diagonal index position
        // to the mirror line for each X & Y iteration
        if (diagNdx < dataLength) {
			fillLength = resultWidth - diagNdx * 2;
        } else {
        	fillLength += 2;
        }



        for (fillPos = 0; fillPos < fillLength; fillPos++) {
            // Iterate one index at a time until mirror line
            if (diagNdx < dataLength) {  // Before crossing mirror line
                // Filling along X axis (>)
                result[diagNdx][diagNdx + fillPos] = data[dataNdx];
                // Filling along Y axis (\/)
                result[diagNdx + fillPos][diagNdx] = data[dataNdx];
            } else {                     // After crossing mirror line
                // Filling along X axis (<)
                result[diagNdx][diagNdx - fillPos] = data[dataNdx];
                // Filling along Y axis (/\)
                result[diagNdx - fillPos][diagNdx] = data[dataNdx];
            }
        }
    }

    // Print results
    printf("Mirror line method. Minimal overwriting.\n{");
    for (i=0; i < resultWidth; i++) {
        if ( i > 0) { printf(" "); } // Conditional formatting
        printf("{");
        for (j=0; j < resultWidth; j++) {
            printf("%d", result[i][j]);
            if (j < resultWidth-1) { printf(" "); } // Conditional formatting
        }
        printf("}");
        if (i < resultWidth-1) { printf("\n"); } // Conditional formatting
    }
    printf("}\n\n");
}

void printIntPtrInfo(int* data, int length) {
    int i;

    printf(
        "void printIntPtrInfo(int* data, int length)\n"
        "int* data...\taddress: %p\tsize: %d\n"
        "data...\t\taddress: %p\tsize: %d\t\tlength: %d\tcontents: ",
        &data, sizeof data,
        data, sizeof *data, length);

    printf("{");
    for (i=0; i < length; i++) {
        printf("%d",data[i]);
        if (i < length-1) { printf(","); }
    }
    printf("}\n\n");
}
