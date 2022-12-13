#include <iostream>
#include <omp.h>
int main() {
    //omp_set_num_threads(8);//definir el numero de hilos
/*#pragma omp parallel default(none)
    {
        int nthreads= omp_get_num_threads();//numero de hilos
        int thread_id= omp_get_thread_num();//id del hilo
        std::printf( "Hello, World! \n");
        std::printf("i have %d threads and my thread_id is %d \n", nthreads,thread_id);
    }*/
#pragma omp parallel default(none)
    {
        if(omp_get_thread_num()==0){
            std::printf(" i have %d proc \n", omp_get_num_procs());
            std::printf( "i have %d threads  \n", omp_get_num_threads());
        }
        int thread_id= omp_get_thread_num();//id del hilo
        std::printf( "My thread_id is %d \n",thread_id);
    }
    return 0;
}
