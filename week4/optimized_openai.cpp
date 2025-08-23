
#include <iostream>
#include <vector>
#include <cstdint>
#include <chrono>

// Linear Congruential Generator (LCG) function
class LCG {
public:
    LCG(uint32_t seed, uint32_t a = 1664525, uint32_t c = 1013904223, uint64_t m = (1ULL << 32))
        : value(seed), a(a), c(c), m(m) {}

    uint32_t next() {
        value = (a * value + c) % m;
        return value;
    }

private:
    uint32_t value;
    uint32_t a, c;
    uint64_t m;
};

// Function to get maximum subarray sum using Kadane's algorithm
int64_t max_subarray_sum(int n, uint32_t seed, int min_val, int max_val) {
    LCG lcg(seed);
    std::vector<int> random_numbers(n);
    for (int i = 0; i < n; ++i) {
        random_numbers[i] = lcg.next() % (max_val - min_val + 1) + min_val;
    }

    int64_t max_sum = INT64_MIN, current_sum = 0;
    for (int i = 0; i < n; ++i) {
        current_sum = std::max(static_cast<int64_t>(random_numbers[i]), current_sum + random_numbers[i]);
        max_sum = std::max(max_sum, current_sum);
    }
    return max_sum;
}

// Function to calculate the total maximum subarray sum for 20 runs
int64_t total_max_subarray_sum(int n, uint32_t initial_seed, int min_val, int max_val) {
    int64_t total_sum = 0;
    LCG lcg(initial_seed);
    for (int i = 0; i < 20; ++i) {
        uint32_t seed = lcg.next();
        total_sum += max_subarray_sum(n, seed, min_val, max_val);
    }
    return total_sum;
}

int main() {
    // Parameters
    int n = 10000;
    uint32_t initial_seed = 42;
    int min_val = -10;
    int max_val = 10;

    // Timing the function
    auto start_time = std::chrono::high_resolution_clock::now();
    int64_t result = total_max_subarray_sum(n, initial_seed, min_val, max_val);
    auto end_time = std::chrono::high_resolution_clock::now();

    std::chrono::duration<double> elapsed = end_time - start_time;
    std::cout << "Total Maximum Subarray Sum (20 runs): " << result << std::endl;
    std::cout << "Execution Time: " << elapsed.count() << " seconds" << std::endl;

    return 0;
}
