#include <iostream>
#include <random>
#include <chrono>
#include "hashtable.h" // Include your hash table header

// Generate a random integer between a given range
int generate_random(int min, int max) {
    static std::random_device rd;
    static std::mt19937 generator(rd());
    std::uniform_int_distribution<int> distribution(min, max);
    return distribution(generator);
}

int main() {
    const int min_value = 0;
    const int max_value = 1000000; // Maximum value for random generation
    const int start_N = 1000;      // Starting size
    const int step_size = 5000;    // Increment for N
    const int iterations = 10;    // Number of iterations for increasing N

    for (int i = 0; i < iterations; ++i) {
        int N = start_N + i * step_size; // Increment N
        HashTable<int, int> hashTable;  // Create a hash table instance

        auto start_time = std::chrono::high_resolution_clock::now();

        // Insert N random key-value pairs into the hash table
        for (int j = 0; j < N; ++j) {
            int key = j; // Sequential keys
            int value = generate_random(min_value, max_value);
            hashTable.insert(key, value);
        }

        auto end_time = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> elapsed_time = end_time - start_time;

        // Calculate and display average insertion cost
        double average_insertion_cost = elapsed_time.count() / N;
        std::cout << "N: " << N
                  << ", Total time: " << elapsed_time.count() << " seconds"
                  << ", Average insertion cost: " << average_insertion_cost << " seconds" 
                  << std::endl;
    }

    return 0;
}
