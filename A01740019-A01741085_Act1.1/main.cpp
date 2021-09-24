/*  Act. 1.1: Implementacion de la tecnica de programacion "divide y venceras"
'n' numeros de entrada son almacenados en un vector<double> que es ordenado usando Merge Sort de mayor a menor.
Se imprime el vector ordenado.
    Ana Cristina Munguia Romero, A01740019
    Carlos Noel Ojeda Angulo, A01741085
    Fecha: 26/08/21
 */

#include <iostream>
#include <vector>

using namespace std;

// Metodo mezcla para reintegrar las sublistas ordenadas de Merge Sort. Recibe los indices de los extremos del vector y el vector a ordenar.
// Complejidad: O(2n) = O(n).
void mezcla(int inicio, int fin, vector<double>& vector){
    int centro = (inicio+fin)/2,
        size = fin-inicio+1,
        i = inicio,
        j = centro+1;
    double aux[size];
    for(int pos=0; pos<size; pos++){
        if(i<=centro && j<=fin){
            if(vector[i] > vector[j]){
                aux[pos] = vector[i];
                i += 1;
            }else{
                aux[pos] = vector[j];
                j += 1;
            }
        }else if(i <= centro){
            aux[pos] = vector[i];
            i += 1;
        }else{
            aux[pos] = vector[j];
            j += 1;
        }
    }
    for(int k=0; k < size; k++){
        vector[inicio+k] = aux[k];
    }
}

// Funcion recursiva para el metodo Merge Sort. Recibe el vector a ordenar y los indices de los extremos de las sublistas.
// Complejidad: O(n log2(n)).
void ordenaMerge(vector<double>& vector, int inicio, int fin){
    if(inicio < fin){
        int centro = (inicio+fin)/2;
        ordenaMerge(vector, inicio, centro);
        ordenaMerge(vector, centro+1, fin);
        mezcla(inicio, fin, vector);
    }
}

// Ordena en forma descendente los datos con el metodo de Merge Sort. Recibe el vector a ordenar.
// Complejidad: O(n log2(n)).
void ordenaMerge(vector<double>& vector){
    ordenaMerge(vector, 0, vector.size()-1);
}

int main(){
    vector<double> v;
    int n;
    double dato;
    cin >> n;
    for (int i=0; i<n; i++){
        cin >> dato;
        v.push_back(dato);
    }
    ordenaMerge(v);
    
    cout << endl;
    
    for (int i=0; i<n; i++) {
        cout << v[i] << " ";
    }
    cout << endl;
    return 0;
}
