# README.md

### Summary 

This project follows the topic of threads and asks you to design a real scenario/application with multiple threads. You will use the threads programming interface, POSIX Threads (Pthreads). You should implement this in Linux, which supports Pthreads as part of the GNU C library. 

### Description 

This project asks to write a multithreaded sorting program that works as follows: A list of integers is divided into two smaller lists of equal size. Two separate threads (which we will term sorting threads) sort each sublist using a sorting algorithm of your choice. The two sublists are then merged by a third thread—a merging thread—which merges the two sublists into a single sorted list. In the above list, x is a placeholder for the student identifier. Because global data are shared across all threads, perhaps the easiest way to set up the data is to create a global array. Each sorting thread will work on one half of this array. A second global array of the same size as the unsorted integer array will also be established. The merging thread will then merge the two sublists into this second array. 

Graphically, this program is structured as in the below figure:

![image-20210304185540011](C:\Users\keira\Desktop\Spring 2020\typora-images\image-20210304185540011.png)

This programming project will require passing parameters to each of the sorting threads. In particular, it will be necessary to identify the starting index from which each thread is to begin sorting. The parent thread will output the sorted array once all sorting threads have exited.