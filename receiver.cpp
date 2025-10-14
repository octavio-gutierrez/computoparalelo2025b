#include <mpi.h>
#include <iostream>

using namespace std;

int main (int argc, char *argv[]) {
   const int MASTER = 0;
   int num_processes = 0;
   int process_id = 0; 
   int name_length = 0;
   char host_name[MPI_MAX_PROCESSOR_NAME];
   int num_elements = 5;
   int mensaje[num_elements] = {0, 0, 0, 0, 0};
   int source = 1; // este es el rango del emisor
   int tag = 100; // identificador de la conversacion
   MPI_Status status;
   MPI_Init(&argc, &argv);
   MPI_Comm_size(MPI_COMM_WORLD, &num_processes);
   MPI_Comm_rank(MPI_COMM_WORLD, &process_id);
   MPI_Get_processor_name(host_name, &name_length);

   // cout << "Hi from process " << process_id << " on " << host_name << "\n";

   // Aqui se bloquea el proceso hasta que no recibe el mensaje

   MPI_Recv(&mensaje, num_elements, MPI_INT, source, tag, MPI_COMM_WORLD, &status);



   
   //cout << "Soy " << process_id << " y recibi un mensaje de " << status.MPI_SOURCE << "\n";

   for (int i=0; i < num_elements; i++) {
       cout << "Elemento " << i << " con valor " << mensaje[i] << "\n";
   }

   MPI_Finalize();

   return 0;
}
