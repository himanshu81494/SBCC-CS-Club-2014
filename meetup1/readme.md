# First Meet Puzzle
> Take a single dimension array of integers and fill a double dimension array with values of concentric shrinking boxes.

I ended up writing two methods from a couple in mind; brute force and less brute force-y. The brute force is simply filling the 2D array with expanding margins per iteration until the center is reached. The less brute force-y method I ended up spreadhseeting to get my thoughts in order:

![alt text](https://github.com/ryunp/SBCC-CS-Club-2014/blob/master/meetup1/MeetUp1_Puzzle1.png)

**Results for 'Brute Force' solution:**

    void printIntPtrInfo(int* data, int length)
    int* data...    address: 0x23aaa0       size: 8
    data...         address: 0x23aac0       size: 4         length: 6
    data[] contents: {1,2,3,4,5,6}
    
    Brute force method. Lots of overwriting.
    {{1 1 1 1 1 1 1 1 1 1 1}
     {1 2 2 2 2 2 2 2 2 2 1}
     {1 2 3 3 3 3 3 3 3 2 1}
     {1 2 3 4 4 4 4 4 3 2 1}
     {1 2 3 4 5 5 5 4 3 2 1}
     {1 2 3 4 5 6 5 4 3 2 1}
     {1 2 3 4 5 5 5 4 3 2 1}
     {1 2 3 4 4 4 4 4 3 2 1}
     {1 2 3 3 3 3 3 3 3 2 1}
     {1 2 2 2 2 2 2 2 2 2 1}
     {1 1 1 1 1 1 1 1 1 1 1}}
    
    
    RUN SUCCESSFUL (total time: 19ms)


**Results for 'More Work' solution:**

    void printIntPtrInfo(int* data, int length)
    int* data...    address: 0x23aa90       size: 8
    data...         address: 0x23aab0       size: 4         length: 9
    data[] contents: {1,2,3,4,5,6,7,8,9}
    
    Mirror line method. Minimal overwriting.
    {{1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1}
     {1 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 1}
     {1 2 3 3 3 3 3 3 3 3 3 3 3 3 3 2 1}
     {1 2 3 4 4 4 4 4 4 4 4 4 4 4 3 2 1}
     {1 2 3 4 5 5 5 5 5 5 5 5 5 4 3 2 1}
     {1 2 3 4 5 6 6 6 6 6 6 6 5 4 3 2 1}
     {1 2 3 4 5 6 7 7 7 7 7 6 5 4 3 2 1}
     {1 2 3 4 5 6 7 8 8 8 7 6 5 4 3 2 1}
     {1 2 3 4 5 6 7 8 9 8 7 6 5 4 3 2 1}
     {1 2 3 4 5 6 7 8 8 8 7 6 5 4 3 2 1}
     {1 2 3 4 5 6 7 7 7 7 7 6 5 4 3 2 1}
     {1 2 3 4 5 6 6 6 6 6 6 6 5 4 3 2 1}
     {1 2 3 4 5 5 5 5 5 5 5 5 5 4 3 2 1}
     {1 2 3 4 4 4 4 4 4 4 4 4 4 4 3 2 1}
     {1 2 3 3 3 3 3 3 3 3 3 3 3 3 3 2 1}
     {1 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 1}
     {1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1}}
    
    
    RUN SUCCESSFUL (total time: 22ms)


