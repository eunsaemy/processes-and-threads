## Processes vs Threads

The programs use multiple processes and threads to perform Sieve of Eratosthenes to find all prime numbers up to 10,000 on each process/thread.
Its performance is measured by the individual process/thread time and its efficiency is measured by the total time of all the processes/threads.

### To run processes.c:

gcc processes.c -o processes.out

### To run threads.c:

gcc threads.c -o threads.out -pthread
