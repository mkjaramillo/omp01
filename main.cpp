#include <iostream>
#include <omp.h>
#include<chrono>

namespace ch=std::chrono;
#define numeroIteraciones 1000000000
double pi_serial(){
    double respuesta=0.0;
    bool esIndicePar=true;
    for(long i=0;i<=numeroIteraciones;i++) {
        if(esIndicePar==true) {
            respuesta+=4.0/(2.0* i+1.0);
        }else {
            respuesta-=4.0/(2.0* i+1.0);
        }
        esIndicePar=!esIndicePar;

    }
    return respuesta;
}
double pi_omp1(){
    int numero_hilos=0;
#pragma omp parallel
    {
            #pragma opm master//le pone en hilo cero
            numero_hilos= omp_get_num_threads();

    };
    std::printf("num hilos: %d \n", numero_hilos);
    double sumas_parciales[numero_hilos];

#pragma omp parallel shared(sumas_parciales)//para demostrar que esta variable es global
    {
        //variable local
        int thread_id= omp_get_thread_num();

        for(long i=thread_id;i<=numeroIteraciones;i+=numero_hilos) {
            if(i%2==0) {
                sumas_parciales[thread_id]+=4.0/(2.0* i+1.0);
            }else {
                sumas_parciales[thread_id]-=4.0/(2.0* i+1.0);
            }


        }
    }
    double respuesta=0;
    //suma de todos los hilos
    for(int i=0;i<=numero_hilos;i++){
       respuesta=respuesta+sumas_parciales[i];
    }
    return respuesta;
}
int main() {
    double pi1;
   auto start= ch::high_resolution_clock::now();
    {
        pi1=pi_omp1();
    }

    auto end=ch::high_resolution_clock::now();
    ch::duration<double,std::milli>duration=end-start;
    std::printf( "tiempo serial %lf,pi=%lf \n",duration.count()*1000,pi1);

    //omp_set_num_threads(8);//definir el numero de hilos
/*#pragma omp parallel default(none)
    {
        int nthreads= omp_get_num_threads();//numero de hilos
        int thread_id= omp_get_thread_num();//id del hilo
        std::printf( "Hello, World! \n");
        std::printf("i have %d threads and my thread_id is %d \n", nthreads,thread_id);
    }*/
/*
#pragma omp parallel default(none)
    {
        if(omp_get_thread_num()==0){
            std::printf(" i have %d proc \n", omp_get_num_procs());
            std::printf( "i have %d threads  \n", omp_get_num_threads());
        }
        int thread_id= omp_get_thread_num();//id del hilo
        std::printf( "My thread_id is %d \n",thread_id);
    }
    return 0;*/
}
