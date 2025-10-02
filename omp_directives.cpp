#include <iostream>
#include <omp.h>
using namespace std;
int main(int argc, char** argv) {
	const int number_threads = 4;
	const long long int vector_size = 1000;
	const int chunk_size = vector_size / number_threads;
	int* a = new int[vector_size];
	int* b = new int[vector_size];
	int* c = new int[vector_size];
	long long int i; 
	int thread_id;
	omp_set_num_threads(number_threads);
    #pragma omp parallel shared(a, b, c, vector_size, chunk_size) private(i, thread_id)
    {
        thread_id = omp_get_thread_num();
		cout << "Thread " << thread_id << " waiting...\n";
		#pragma omp barrier 
		cout << "Thread " << thread_id << " moving on...\n";
		#pragma omp for schedule(static, chunk_size)
		for (i=0; i < vector_size; i++)
			a[i] = b[i] = i + 1;
        // SECTIONS Permite que un hilo (y no más) sea asignado a cada Section 
        #pragma omp sections 
        {
            #pragma omp section
            {
                cout << "Gane la seccion A y soy: " << thread_id << "\n";
                for(i=0; i < vector_size/2; i++) {
                    c[i] = a[i] + b[i];                    
                }
            }
            #pragma omp section  
            {
                cout << "Gane la sección B y soy: " << thread_id << "\n";
                for(i=vector_size/2; i < vector_size; i++){
                    c[i] = a[i] + b[i];
                }
            }
        }
    }
        //cout << "Soy: " << thread_id << " y esto saliendo del Sections\n";   }
    int x = 0; // recurso compartido cuya actualización podria causar condicion de carrera
    #pragma omp parallel shared(x) private(i) 
    {
        #pragma omp critical (region_uno)
        {
            for (i=0; i<1000; i++){
                x = x + 1;
            }
        }
        #pragma omp critical (region_dos)
        {
            for (i=0; i<1000; i++){
                x = x + 1;
            }
        }
     } 
    cout << "Valor de x = " << x << "\n";
    long long int total = 0;
    #pragma omp parallel shared(total, a, b, c, chunk_size, vector_size) private(i)
    {
        #pragma omp for schedule(static, chunk_size) reduction (+:total)
        for (i=0; i < vector_size; i++){
            total += a[i] + b[i];
        }
        #pragma omp barrier
        #pragma omp master
        cout << "El total es " << total << "\n";
    }
    long long int minimo = 30000000;
    #pragma omp parallel shared(minimo, a, b, c) private(i)
    {
        #pragma omp for schedule(static, chunk_size) reduction (min:minimo)
        for (i=0; i < vector_size; i++){
            if  ((a[i] + b[i]) < minimo) {
                minimo = a[i] + b[i];
            }
        }        
        #pragma omp barrier
        #pragma omp master
        cout << "El minimo es " << minimo << "\n";
    } 
    delete[] a;    
    delete[] b;    
    delete[] c;    
    return 0;
}
