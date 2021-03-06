/**
 * project 2
 */

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>


const int num_of_threads = 3;

//int orig_arr[] = {20, 10, 2, 7, 19, 21, 25, 57, 89, 33};
int orig_arr[] = {7, 12, 19, 3, 18, 4, 2, 6, 15, 8};
#define num_of_elems 10
int final_arr[num_of_elems];

typedef struct {
    int left;
    int right;
} arr;


void *sorter(void *params);	/* thread that performs basic sorting algorithm */
void *merger(void *params);	/* thread that performs merging of results */

void InsertionSort(int l, int r);

int main (int argc, const char * argv[])
{
    // ORIGINAL ARRAY:
    printf("ORIGINAL ARRAY:            { ");
    int i;
    for (i = 0; i < num_of_elems; i++) {
        printf("%d ", orig_arr[i]);
    }
    printf("}\n");

    pthread_t threads[num_of_threads]; // 3 threads total
    int middle = (num_of_elems / 2);

    // 1. thread to sort first half
    arr* array = (arr *) malloc(num_of_elems / sizeof(arr)*2);
    (*array).left = 0; // first index - 0
    (*array).right = (middle - 1); // midpoint - 4
    pthread_create(&threads[0], 0, sorter, array); // (1/3) threads

    // 2. thread to sort second half
    array = (arr *)malloc(num_of_elems / sizeof(arr)*2);
    (*array).left = middle; // midpoint
    (*array).right = num_of_elems - 1; // last index
    pthread_create(&threads[1], 0, sorter, array); // (2/3) threads

    // let 2 threads finish sorting each half before continuing
    for (i = 0; i < 2; i++) {
        pthread_join(threads[i], NULL);
    } // --------------------------------------------------------------------------

    // 3. thread to merge halves into final_arr
    // allocate size of thread
    array = (arr *) malloc(num_of_elems / sizeof(arr)*2);
    // assign start position
    (*array).left = 0;
    // assign half the size of right
    (*array).right = num_of_elems - 1;
    // merge array using specific thread
    pthread_create(&threads[2], 0, merger, array); // (3/3) threads

    // let thread finish merging before continuing
    pthread_join(threads[2], NULL); // -------------------------------------

    // output the sorted array
    return 0;
}

/**
 * Sorting thread.
 */

void *sorter(void *params)
{
    // TODO: Your code here
    // 1. Cast void* ("params") to arr*
    arr* array = (arr*) params;
    // 2. Set left & right indices.
    int l = (*array).left;
    int r = (*array).right;
    //printf("left: %d right: %d", l, r);
    // 3. Hand off to sorting algorithm.
    InsertionSort(l, r);

    // loop to store both sorted arrays into final_arr
    int x;
    for(x=l; x<=r; x++)
    {
        final_arr[x]=orig_arr[x] ;
        //printf("%d ", final_arr[x]);
    }
    pthread_exit(0);
}

void InsertionSort(int l, int r) {
    int temp = 0;
    // kkkkk: i represents the # of values in the correct spot ("sorted")
    for (int i = l; i <= r; i++) { // kkkkk: left -> right
        //int j, temp = orig_arr[i]; // make a copy of a[i] // NOTE: does not increase with length of the array, since these values get thrown away after every iteration ---> doesn't need any memory (O(n)) or "in place"
        // kkkkk: takes value & shifts it to the left until it is in the right spot.
        for (int j = l; j <= r - 1; j++) { // start "moving left" // NOTE: j depends on i, and i depends on right
            if (orig_arr[j] > orig_arr[j + 1]) {
                temp = orig_arr[j];
                orig_arr[j] = orig_arr[j+1];
                orig_arr[j + 1] = temp;
            }
        }
    }
}

/**
 * Merge thread
 */

// Merge the two arrays
void *merger(void *params)
{
    arr* p = (arr *)params;

    // assign pointer variables from arr
    int start = p -> left;
    int stop = p ->  right;
    // initialize blank variables for loop and index swapping
    int i;
    int j;
    int k;

   // for loop to read through the array
    for(i=start; i< stop; i++)
    {
        for(j=start; j< stop-i; j++)
        {
            if(final_arr[j] > final_arr[j+1])// if current position is greater than next position, swap
            {
                // set new point to current sorted index
                k = final_arr[j];
                // swap index positions with position 1 to the right
                final_arr[j] = final_arr[j+1];
                // swap index positions
                final_arr[j+1] = k;
            }
        }
    }
    int a;
    // print final array
    printf("Final sorted merged array: { ");
    
    for(a=0; a < num_of_elems; a++)
    {
        printf("%d ", final_arr[a]);
    }
    printf("}\n");
    pthread_exit(0);
}