#include <mpi.h>
#include <iostream>

using namespace std;

int main (int argc, char *argv[]) {
   int num_processes = 0;
   int process_id = 0; 
   int my_message = 0;
   int sender_id = 1; // sender_id <= num_processes - 1
   const int NUM_VECTORS = 3; // Debe ser igual al numero de procesos
   const int VECTOR_SIZE = 5;
   float message[VECTOR_SIZE];
   float data[NUM_VECTORS][VECTOR_SIZE] = {{1.0, 2.0, 3.0, 4.0, 5.0},
                                           {6.0, 7.0, 8.0, 9.0, 10.0}, 
                                           {11.0, 12.0, 13.0, 14, 15}};
    float data_to_be_collected[NUM_VECTORS] = {-1, -1, -1};

   MPI_Init(&argc, &argv);
   MPI_Comm_size(MPI_COMM_WORLD, &num_processes);
   MPI_Comm_rank(MPI_COMM_WORLD, &process_id);
   
   if (process_id == sender_id) {
        my_message = 111;
   }
   
   MPI_Bcast(&my_message, 1, MPI_INT, sender_id, MPI_COMM_WORLD);

   cout << "Hola soy proceso " 
        << process_id 
        << " y recibi el mensaje " 
        << my_message << "\n";


    if (num_processes == NUM_VECTORS) {
        MPI_Scatter(data,
                    VECTOR_SIZE,
                    MPI_FLOAT,
                    message,
                    VECTOR_SIZE,
                    MPI_FLOAT,
                    sender_id,
                    MPI_COMM_WORLD);
        cout << "SCATTER Proceso " << process_id << " mensaje " 
             << message[0] << " "
             << message[1] << " "
             << message[2] << " "
             << message[3] << " "
             << message[4] << "\n";             

        float sum = 0.0;
        for (int i=0; i < VECTOR_SIZE; i++){
            sum += message[i];                    
        }

        float average = sum / VECTOR_SIZE;

        cout << "Promedio " << average << " del proceso " << process_id << endl;

        MPI_Gather(&average,
                   1,
                   MPI_FLOAT,
                   data_to_be_collected,
                   1,
                   MPI_FLOAT,
                   sender_id,
                   MPI_COMM_WORLD);
        cout << "Datos recolectados " << process_id << " - " 
             << data_to_be_collected[0] << " " 
             << data_to_be_collected[1] << " "
             << data_to_be_collected[2] << endl;

        float reduction_result = 0.0;

        MPI_Reduce(&average,
                   &reduction_result,
                   1,
                   MPI_FLOAT,
                   MPI_MIN,
                   sender_id,
                   MPI_COMM_WORLD);

        cout << " Reduccion " << " Proceso " << process_id << " " << reduction_result;






    } else {
        cout << "El numero de procesos tiene que ser igual a " << NUM_VECTORS;
    }




   MPI_Finalize();
   return 0;
}