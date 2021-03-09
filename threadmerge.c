#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#define ArrSize 10
#define ThreadNum 3

// Assign thread to merging results
void *merge(void *params);    

int sorted[ArrSize];
int list[SIZE] = {7,1,8,3,4,2,6,9,12,15};


typedef struct
{
    int arrIndex;
    int arrOutdex;
} parameters;

int main (int argc, const char * argv[])
{
    pthread_t threads[ThreadNum];

    // establish the merge thread
    // allocate size of thread
    sortArr = (givArray *) malloc(sizeof(givArray)); 
    // assign sorted array into new int arrIndex
    sortArr -> arrIndex = 0;
    // assign half the size of array to arrayOutdex
    sortArr -> arrOutdex = (ArrSize/2);
    // merge array using specific thread
    pthread_create(&threads[2], 0, merger, sortArr);

    // let thread finish before continuing
    pthread_join(threads[2], NULL);

    // output the sorted array 
    return 0;
}

// Merge the two arrays
void *merge(void *params)
{
    givArray* p = (givArray *)params;

   //MERGE
    int start = p -> arrIndex;
    int stop = p ->  arrOutdex + 1;
    int i;
    int j;
    int k;
   
   // if index is less than end point, move on 
    for(i=start; i< stop; i++)
    {
        for(j=start; j< stop-i; j++)
        {
            if(sorted[j] > sorted[j+1])
            {
                // set new point to current sorted index
                k = sorted[j];
                // swap index positions with position 1 to the right
                sorted[j] = sorted[j+1];
                // swap index positions
                sorted[j+1] = k;
            }
        }
    }
    int a;

    for(a=0; a < ArrSize; a++)
    {
        printf("Final sorted array is: %d\n", sorted[a]);
    }
    pthread_exit(0);
}