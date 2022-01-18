#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/wait.h>

 /*H************************************************************
 * FUNCTION NAME :      main
 *
 * DESCRIPTION:
 *      Each of the child processes perform Sieve of Eratosthenes to find
 *      all prime numbers up to 10,000.
 *
 * PARAMETERS:
 *
 * RETURN VALUES:
 *
 * AUTHOR :     Eunsaem Lee         START DATE :        15 Jan 22
 *
 *H*/

void sieve(FILE *file);

int main (void)
{
  // create variables
  FILE *fptr1, *fptr2;
  fptr1 = fopen("processes_efficiency.txt", "w");
  fptr2 = fopen("processes_answer.txt", "w");

  int n, status;
  status = 0;
  pid_t pid, wait_pid;
  struct timeval start, end;

  // input error checking
  while (1)
  {
    // prompt user for # of processes
    printf("Enter the number of processes: ");

    int next;

    if (scanf("%d", &n) < 0 || n <= 0 || ((next = getchar()) != EOF && next != '\n'))
    {
      clearerr(stdin);

      do
      {
        next = getchar();
      }
      while (next != EOF && next != '\n');

      clearerr(stdin);
      printf("\nInvalid input: enter a positive integer!\n");
    }
    else
    {
      break;
    }
  }
  
  // start time
  gettimeofday(&start, NULL);

  // create 'n' number of child processes & run sieve
  for (int i = 0; i < n; i++)
  {
    pid = fork();

    // if child process, run sieve
    if (pid == 0)
    {
      sieve(fptr2);

      exit(0);
    }
  }

  // wait for child processes to end
  while ((wait_pid = wait(&status)) > 0);

  // if parent process
  if (pid > 0)
  {
    // wait for child processes to end
    wait((int*) 0);

    // end time
    gettimeofday(&end, NULL);

    // calculate total time taken
    long int totalTime = end.tv_usec - start.tv_usec;

    // record total time taken
    fprintf(fptr1, "total process time in microseconds : %ld\n", totalTime);

    fclose(fptr1);
    fclose(fptr2);
  }

  return 0;
}

 /*H************************************************************
 * FUNCTION NAME :      sieve
 *
 * DESCRIPTION:
 *      Sieve of Eratosthenes - finds all prime numbers up to 10,000, and
 *      inputs them into a text file.
 *
 * PARAMETERS:
 *
 * RETURN VALUES:
 *
 * AUTHOR :     Blogs Dope
 *              https://www.codesdope.com/blog/article/prime-numbers-using-sieve-algorithm-in-c/
 *
 *H*/

void sieve(FILE *file)
{
  // create variables
  FILE *fptr3;
  fptr3 = fopen("processes_performance.txt", "w");

  int num = 10000;
  int i, j;
  int primes[num + 1];
  struct timeval start_performance, end_performance;

  // start time
  gettimeofday(&start_performance, NULL);

  // populate array with natural numbers
  for (i = 2; i < num; i++)
  {
    primes[i] = i;
  }

  i = 2;

  while ((i * i) <= num)
  {
    if (primes[i] != 0)
    {
      for (j = 2; j < num; j++)
      {
        if (primes[i] * j > num)
        {
          break;
        }
        else {
          // instead of deleting, make elements 0
          primes[primes[i] * j] = 0;
        }
      }
    }
    i++;
  }

  for (int i = 2; i < num; i++)
  {
    // if number is not 0, then it is prime
    if (primes[i] != 0)
    {
      fprintf(file, "%d, ", primes[i]);
    }
  }
  fprintf(file, "\n");

  // end time
  gettimeofday(&end_performance, NULL);

  // calculate total time taken
  long int performanceTime = end_performance.tv_usec - start_performance.tv_usec;

  // record total time taken
  fprintf(fptr3, "single process time in microseconds : %ld\n", performanceTime);

  fclose(fptr3);
}