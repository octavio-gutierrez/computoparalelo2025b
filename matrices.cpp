#include <iostream>
using namespace std;

int main() {    
    int ren = 2;
    int col = 4;
    //int matriz[ren][col];
    //int** matriz {new int*[ren]};
    // Reservamos memoria para la matriz dinamicamente
    int** matriz = new int*[ren];
    for (int i = 0; i < ren; i++){
        matriz[i] = new int[col];
    }

    // Codigo de procesamiento de la matriz
    for (int i = 0; i < ren; i++) {        
        for (int j = 0; j < col; j++) {
            cout << matriz[i][j] << " ";
        }
        cout << "\n";
    }
    cout << "\n";

    cout << *matriz << "\n";
    for (int i = 0; i < ren; i++) {        
        cout << matriz[i] << "\n";    
        for (int j = 0; j < col; j++) {
            cout << &matriz[i][j] << " ";
        }
        cout << "\n";
    }
    cout << "\n";


    // liberando la memoria reservada dinamicamente 
    for (int i = 0; i < ren; i++) {
        delete [] matriz[i];
    }
    delete[] matriz;

    return 0;
}
