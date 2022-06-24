Daniel Cao
dcao182@csu.fullerton.edu

Instructions on how to run the program:
g++ threads.cpp -o threads -lpthread
./threads 10

Anything special about the program:
The program runs as expected.


1.  The program shall be invoked as ./threads <number> where <number> is the number of threads.  For example, ./threads 10 will create 10 threads.

2. The program will then create the specified number of threads and each thread will then generate 100 random numbers in range of 0 -- 100000 and insert them into the same shared binary search tree that is shared between all threads.

3.  All threads should be allowed to insert the numbers at the same time while ensuring proper synchronization using pthread mutexes (i.e., no two threads will be modifying the tree at the same time).

4. While the created threads are busy inserting numbers, the main thread waits for the other threads to terminate.  Once all threads terminate the main thread will print all numbers in the binary tree. Correctly printed numbers should be in order (as that is the point of the binary search tree).