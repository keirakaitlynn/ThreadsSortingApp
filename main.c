/**
 * project 2
 */

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>


const int num_of_threads = 2;

int orig_arr[] = {20, 10, 2, 7, 19, 21, 25, 57, 89, 33};
const int num_of_elems = sizeof(orig_arr);
int final_arr[num_of_elems];
typedef struct {
    int left;
    int right
} arr;


void *sorter(void *params);	/* thread that performs basic sorting algorithm */
void *merger(void *params);	/* thread that performs merging of results */



void InsertionSort(arr *array, int l, int r);

int main (int argc, const char * argv[])
{
	//Your code here
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

    return NULL;
}

void InsertionSort(arr *array, int l, int r) {
    // kkkkk: i represents the # of values in the correct spot ("sorted")
    for (int i = l + 1; i <= r; i++) { // kkkkk: i depends on right
        int j, temp = orig_arr[i]; // make a copy of a[i] // NOTE: does not increase with length of the array, since these values get thrown away after every iteration ---> doesn't need any memory (O(n)) or "in place"
        // kkkkk: takes value & shifts it to the left until it is in the right spot.
        for (j = i - 1; j >= 0; j--) { // start "moving left" // NOTE: j depends on i, and i depnds on right
            if (orig_arr[j] > temp) {
                orig_arr[j + 1] = orig_arr[j]; // inversion detected; move a[j] to the right
            }
            else {
                break;
            } // index j is one spot to the left of where temp belongs
        }
        orig_arr[j+1] = temp;
    }
}

/**
 * Merge thread
 */

void *merger(void *params)
{
	// TODO: Your code here
}

