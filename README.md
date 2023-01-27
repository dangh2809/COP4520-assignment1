# COP4520-assignment1

### Compile and Run
To compile:
```g++ -std=c++11 assignment1.cpp```
Then, to run:
```./a.out```


### Analysis Summary
My first approach for this problem is to have function that takes a "start" and "end" for a range of number. Then, iteration from start to end, then get the primes by checking if the number is prime. With multithreading, I divided into smaller chunks evenly to each thread, and have each thread perform the function on that chunks. This ended to be quite slow, the execution time is about 20 seconds. Looking at the primes that are printed out, I saw multithreading is being executed as there was different order of each number from different chunks are being display. Interestingly, when it reach to about 100,000 it start to appear by order. I assume that when the number getting larger, the loop inside the function is getting more intensive as isPrime() is iterating from 2. Therefore, smaller numbers would start to finish first, thus the ordering being appeared. This shows that the works distributed are not equally. To solve this, I implemented the sieve of Sieve of Eratosthenes algorithm to get prime numbers below a limit. This approach, I created a array of bool, set true to all, then, iterating and set false to non-primes. I assigned each threads to run this algorithm in a evenly chunks. Each thread will set false to numbers to the "end" arguments. Finally, after joining all of the threads, I got a bool array of size 10^8 +1. Iterate through that, I got the number of prime and the sum of prime, and print out the last ten primes. This approach help me reduce the runtime down to only 1.6 seconds. 
My experiment is that I look at the runtime of the program with different number of threads. The program's runtime for one thread is about 2.7 seconds, with 2 threads is 2.0 seconds, 3 thread is 1.7 seconds, 4 thread is 1.67 seconds, 5 thread is 1.62 seconds, 6 thread is 1.62 seconds, 7 thread is 1.61 seconds, 8 thread is 1.6 seconds. I see that comparing one thread and two thread, we could notice the perfomance is being impoved as it run 35% faster at two thread. However the perfomance seems to not making significant difference from 4 to 8 threads. This indicates that the performance and the runtime is not a linear relationship. Therefore, with mulithreading, we don't need to have more cores to improve the perfomance for such a simple program.

