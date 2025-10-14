#include <mpi.h>
#include <iostream>

using namespace std;

int main (int argc, char *argv[]) {
   const int MASTER = 0;
   int num_processes = 0;
   int process_id = 0; 
   int name_length = 0;
   char host_name[MPI_MAX_PROCESSOR_NAME];
   int destination = 0;
   int source = 1;
   int mensaje[5] = {11, 12, 13, 14, 15};
   MPI_Status status;
   int tag = 101;
   MPI_Init(&argc, &argv);
   MPI_Comm_size(MPI_COMM_WORLD, &num_processes);
   MPI_Comm_rank(MPI_COMM_WORLD, &process_id);
   MPI_Get_processor_name(host_name, &name_length);
   
   if (process_id == 0) { // eres el receptor
        cout << "Hi from process " << process_id << " on " << host_name << "\n";
        MPI_Recv(&mensaje, 5, MPI_INT, source, tag, MPI_COMM_WORLD, &status);
        cout << "Recibi mensaje de " << status.MPI_SOURCE << "\n";
        for (int i = 0; i < 5; i++) {
            cout << "valor " <<  i << " == " << mensaje[i] << "\n";          
        }
   } else { // if process_id == 1  // eres el emisor
        mensaje[0] = 0;
        MPI_Send(&mensaje, 5, MPI_INT, destination, tag, MPI_COMM_WORLD); 
        cout << "Envie un mensaje \n";
   } 
   
   cout << "Hi from process " << process_id << " on " << host_name << "\n";


   MPI_Finalize();

   return 0;
}