#include <iostream>
#include <thread>
#include <vector>
#include <chrono>
#include <algorithm>
#include <fstream>

#define NUM_THREADS 8
#define LIMIT 100000000L

using namespace std;

vector<bool> is_prime(LIMIT + 1, true);

void findPrimes(int start, int end) {
    int count = 0;
    int sum = 0;
    for (unsigned long i = 2; i * i <= end; i++) {
        if (is_prime[i]) {
            for (unsigned long j = i * i; j <= end; j += i) {
                if (j >= start) is_prime[j] = false;
            }
        }
    }
}

int main() {
    ofstream MyFile("primes.txt");
    auto startTime = chrono::high_resolution_clock::now();
    vector<thread> threads;

    int chunk_size = LIMIT / NUM_THREADS;
    for (int i = 0; i < NUM_THREADS; i++) {
        int start = i * chunk_size;
        int end = start + chunk_size - 1;
        if (i == NUM_THREADS - 1) end = LIMIT;
        threads.emplace_back(findPrimes, start, end);
    }
    for (auto &t : threads) t.join();
    // Collect the primes
    vector<unsigned long> primes;
    unsigned long count= 0;
    unsigned long sum = 0;
    for (unsigned long i = 2; i <= LIMIT; i++) {
        if (is_prime[i]) {
            count++;
            sum = sum +i;
            primes.push_back(i);
        }
    }
    
    auto stopTime = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::milliseconds>(stopTime - startTime);
    auto converted = (double)duration.count()/1000;
    MyFile << converted << "s ";
    MyFile << count << " ";
    MyFile << sum << endl;
    
    for (int i  = primes.size() - 10 ; i < primes.size(); i++){
        MyFile << primes[i] << " ";
    }
    return 0;
}