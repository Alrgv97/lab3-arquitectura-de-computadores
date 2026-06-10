#include <iostream>
#include <chrono>
#include <omp.h>

struct Counters {
    long long counter1;
    long long counter2;
} counters; 

void work_on_counter1(int iterations) {
    long long local_counter = 0; // Privatización: variable local 
    for (int i = 0; i < iterations; ++i) {
        local_counter++;
    }
    counters.counter1 += local_counter; // Solo una escritura a memoria global
}

void work_on_counter2(int iterations) {
    long long local_counter = 0; // Privatización
    for (int i = 0; i < iterations; ++i) {
        local_counter++;
    }
    counters.counter2 += local_counter; // Solo una escritura a memoria global
}

int main() {
    const long long ITER = 500000000; 
    double start = omp_get_wtime();

    #pragma omp parallel sections
    {
        #pragma omp section
        work_on_counter1(ITER);
        #pragma omp section
        work_on_counter2(ITER);
    }

    double end = omp_get_wtime();
    
    std::cout << "Tiempo con Privatizacion: " << (end - start) << " s" << std::endl;
    std::cout << "counter1 = " << counters.counter1 
              << ", counter2 = " << counters.counter2 << std::endl;

    return 0;
}