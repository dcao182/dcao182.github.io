Daniel Cao
dcao182@csu.fullerton.edu

Programming language used: C and C++


How to execute the three programs:
g++ -std=c++17 serial.cpp
./a.out

g++ -std=c++17 parallel.cpp
./a.out

g++ -std=c++17 bonus.cpp
./a.out


Execution time for both downloaders:

Serial downloader:
real  1m 30.335s
user  0m  0.943s
sys   0m 14.519s


Parallel downloader:
real  1m 6.744s
user  0m 0.602s
sys   0m 12.657s


1.	In the output of time, what is the difference between real, user, and sys times?
Between the serial and the parallel downloaders, the difference in real time is about 23.591 seconds.  The difference in user time is 0.341 seconds.  The difference in sys times is 1.862 seconds.

2.	Which is longer: user time or sys time? Use your knowledge to explain why.
After doing some research, user time is the CPU time spent in the user-mode, which is in unprivileged mode.  The sys time is the amount of CPU time spent in the kernel, which means the executing CPU time is spent in system mode.  Since the sys time requires invoking system calls, the sys time would be longer than the user time.

3.	When downloading the files above, which downloader finishes faster? Why do you think that is?
From my observation, the serial downloader finishes faster because the downloader is able to focus downloading one file at a time instead of having to intermingle between downloading multiple files, which would cause the downloads to slow down.

4.	Repeat the experiment for 10 files (any reasonably large-sized files, e.g., 100 MB, will do). Is the downloader in the previous question still faster? If not so, why do you think that is?
Yes, the serial downloader still finishes faster than the parallel downloader.  The downloader is able to put all it’s resources into downloading one file at a time, which makes the download for a single file faster.


The extra credit bonus section has been implemented.

Nothing special about my submission to take note of.
