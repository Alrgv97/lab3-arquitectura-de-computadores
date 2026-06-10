#include <iostream>
#include <chrono>
#include <omp.h>

// Estructura mejorada: Alineación a 128 bytes para evadir el Hardware Prefetcher
struct AlignedCounters {
    alignas(128) long long counter1; 
    alignas(128) long long counter2; 
} aligned_counters; 

void work_on_counter1(int iterations) {
    for (int i = 0; i < iterations; ++i) {
        aligned_counters.counter1++;
    }
}

void work_on_counter2(int iterations) {
    for (int i = 0; i < iterations; ++i) {
        aligned_counters.counter2++;
    }
}

int main() {
    const long long ITER = 500000000; // 500 millones de incrementos por hilo
    double start = omp_get_wtime();

    #pragma omp parallel sections
    {
        #pragma omp section
        work_on_counter1(ITER);
        #pragma omp section
        work_on_counter2(ITER);
    }

    double end = omp_get_wtime();
    
    std::cout << "Tiempo corregido (padding 128b): " << (end - start) << " s" << std::endl;
    std::cout << "counter1 = " << aligned_counters.counter1 
              << ", counter2 = " << aligned_counters.counter2 << std::endl;

    return 0;
}