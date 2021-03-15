/**
 * project 2
 */

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>


const int num_of_threads = 3;

int orig_arr[] = {7,12,19,3,18,4,2,6,15,8};
#define num_of_elems 10
int final_arr[num_of_elems];

typedef struct {
    int left;
    int right;
} arr;


void *sorter(void *params);	/* thread that performs basic sorting algorithm */
void *merger(void *params);	/* thread that performs merging of results */

void InsertionSort(arr *array, int l, int r);

int main (int argc, const char * argv[])
{
	// ORIGINAL ARRAY:
	printf("ORIGINAL ARRAY: { ");
	int i;
	for (i = 0; i < num_of_elems; i++) {
	    printf("%d ", orig_arr[i]);
	}
	printf("}\n");

    pthread_t threads[num_of_threads]; // 3 threads total
    int middle = (num_of_elems / 2);

    arr array;                                                  
    array.left = 0;
    array.right = sizeof(orig_arr)/sizeof(orig_arr[0])-1;
    
    // sort
    pthread_create(&threads[0], 0, sorter, &array); // (1/3) threads

    // // 2. thread to sort second half
    
    pthread_create(&threads[1], 0, sorter, &array); // (2/3) threads

    // let 2 threads finish sorting each half before continuing
    for (i = 0; i < 2; i++) {
        pthread_join(threads[i], NULL);
    } // --------------------------------------------------------------------------

    // // merge array using specific thread
    pthread_create(&threads[2], 0, merger, &array); // (3/3) threads

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
	int r = (*array).right + 1;
	// 3. Hand off to sorting algorithm.
    InsertionSort(array, l, r);

  

    pthread_exit(0);
}

void InsertionSort(arr *array, int l, int r) {
    int z;

    for(z = l; z < r; z++)
    {
        printf("The array recieved is: %d\n", orig_arr[z]);
    }
    // // kkkkk: i represents the # of values in the correct spot ("sorted")
    // for (int i = l + 1; i < r; i++) { // kkkkk: i depends on right
    //     int j, temp = orig_arr[i]; // make a copy of a[i] // NOTE: does not increase with length of the array, since these values get thrown away after every iteration ---> doesn't need any memory (O(n)) or "in place"
    //     // kkkkk: takes value & shifts it to the left until it is in the right spot.
    //     for (j = i - 1; j > 0; j--) { // start "moving left" // NOTE: j depends on i, and i depnds on right
    //         if (orig_arr[j] > temp) {
    //             orig_arr[j + 1] = orig_arr[j]; // inversion detected; move a[j] to the right
    //             // printf("%d ", orig_arr[j]);
    //             // printf("\n");
    //         }
    //         else {
    //             break;
    //         } // index j is one spot to the left of where temp belongs
    //     }
    //     orig_arr[j+1] = temp;
    // }
      int x;
    for(x=l; x<r; x++)
    {
            final_arr[x]=orig_arr[x] ;
            // printf("sorted numbers \n");
            // printf("%d ", orig_arr[x]);
            // printf("\n");
    }
    //  int y;
    // for(y=6; y<11; y++)
    // {
    //         // final_arr[x]=orig_arr[x] ;
    //         printf("sorted numbers \n");
    //         printf("%d ", orig_arr[y]);
    //         printf("\n");
    // }
}

/**
 * Merge thread
 */

// Merge the two arrays
void *merger(void *params)
{
    arr* p = (arr *)params;

    //MERGE
    int start = p -> left;
    int stop = p ->  right;
    // 2. Set left & right indices.
	// int l = (*array).left;
	// int r = (*array).right;
    // int middle = (l + r)/2;
    int i;
    int j;
    int k;

    // if index is less than end point, move on
    for(i=start; i< stop; i++)
    {
        for(j=start; j< stop-i; j++)
        {
            if(final_arr[j] > final_arr[j+1])
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
    printf("Final sorted merged array:{");
    
    for(a=0; a < num_of_elems; a++)
    {
        printf("%d ", final_arr[a]);
    }
    printf("}\n");
    pthread_exit(0);
}