#include <mpi.h>
#include <iostream>

using namespace std;

int main (int argc, char *argv[]) {
   int num_processes = 0;
   int process_id = 0; 
   int name_length = 0;
   char host_name[MPI_MAX_PROCESSOR_NAME];   
   MPI_Init(&argc, &argv);
   MPI_Comm_size(MPI_COMM_WORLD, &num_processes);
   MPI_Comm_rank(MPI_COMM_WORLD, &process_id);
   MPI_Get_processor_name(host_name, &name_length);

   cout << "Hola soy proceso " << process_id << " en " << host_name << "\n";
    /* Si eres el maestro, i.e., el primero proceso que sea crea, entonces*/
   
   if (process_id < num_processes/2) {
        int partner = process_id + num_processes/2;
        int etiqueta = 0;
        int mensaje = 1000 * process_id;
        MPI_Status status;
        MPI_Send(&mensaje, 1, MPI_INT, partner, etiqueta, MPI_COMM_WORLD);
        mensaje = 0;
        MPI_Recv(&mensaje, 1, MPI_INT, partner, etiqueta, MPI_COMM_WORLD, &status);
        cout << "Proceso " << process_id << " recibio " << mensaje << endl;
   } else if (process_id >= num_processes/2) {
        int partner = process_id - num_processes/2;
        int etiqueta = 0;
        int mensaje = 0;
        MPI_Status status;
        MPI_Recv(&mensaje, 1, MPI_INT, partner, etiqueta, MPI_COMM_WORLD, &status);
        cout << "Proceso " << process_id << " recibio " << mensaje << endl;
        mensaje *= 10;
        MPI_Send(&mensaje, 1, MPI_INT, partner, etiqueta, MPI_COMM_WORLD);
   }
   MPI_Finalize();
   return 0;
}