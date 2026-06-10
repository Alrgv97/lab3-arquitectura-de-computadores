#include <iostream>
#include <chrono>
#include <omp.h>

// Estructura corregida: se fuerza la alineacion de las variables
struct AlignedCounters {
    alignas(64) long long counter1; // se fuerza la alineacion a 64 bytes
    char padding[64 - sizeof(long long)];
    alignas(64) long long counter2;
} aligned_counters; // global

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
    
    std::cout << "Tiempo corregido (sin falso compartido): " << (end - start) << " s" << std::endl;
    std::cout << "counter1 = " << aligned_counters.counter1 
              << ", counter2 = " << aligned_counters.counter2 << std::endl;

    return 0;
}