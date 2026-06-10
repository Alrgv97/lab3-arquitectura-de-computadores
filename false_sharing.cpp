# include <iostream >
# include <chrono >
# include <omp .h>

 // Estructura que provoca falso compartido 
 struct Counters {
 long long counter1 ;
 long long counter2 ;
 } counters ; // global

 void work_on_counter1 (int iterations ) {
    for (int i = 0; i < iterations ; ++i) {
        counters . counter1 ++;
    }
 }

 void work_on_counter2 (int iterations ) {
    for (int i = 0; i < iterations ; ++i) {
        counters . counter2 ++;
    }
}

int main () {
    const long long ITER = 500000000; // 500 millones de
    // incrementos por hilo
    
    double start = omp_get_wtime ();

    # pragma omp parallel sections
    {
     # pragma omp section
     work_on_counter1 ( ITER );
     # pragma omp section
     work_on_counter2 ( ITER );
    }
    double end = omp_get_wtime ();

 std :: cout << " Tiempo con falso compartido : " << (end - start )
       << " s" << std :: endl ;
 std :: cout << " counter1 = " << counters . counter1 << ",
     counter2 = " << counters . counter2 << std :: endl ;
 return 0;
}