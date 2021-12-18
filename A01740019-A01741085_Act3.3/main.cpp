/*  Act. 3.3: Implementacion de "Knapsack problem" 
Este codigo es una implementacion del algoritmo para resolver el "Knapsack problem". Se encuentra el beneficio maximo posible a partir de una lista de 'n' articulos con peso sin exceder la capacidad de la mochila (peso maximo).
Se recibe el entero 'n' seguido de 'n' enteros que representan los valores de los articulos y 'n' enteros que representan sus pesos. Al final se recibe el peso maximo 'w'.
Se imprime el beneficio maximo obtenido. 
    Ana Cristina Munguia Romero, A01740019
    Carlos Noel Ojeda Angulo, A01741085
    Fecha: 08/10/2021
*/

#include <iostream>
#include <vector>

using namespace std;

int main() {
    int n, w, value;
    cin >> n;
    vector<int> values, weights;
    
    for(int i=0; i<n; i++){
        cin >> value;
		values.push_back(value);
    }

    for(int i=0; i<n; i++){
        cin >> value;
        weights.push_back(value);
    }

    cin >> w;
    
    // Se encuentra el beneficio maximo posible para 'k' elementos (donde 'k' va de 0 a 'n') de acuerdo a un peso maximo (que va de 0 a 'w').
    // Complejidad: O(n*w) donde 'n' es el numero total de elementos y 'w' el peso maximo de la mochila.
    int matrix[n+1][w+1];
	for(int i=0; i<=n; i++){
		matrix[i][0] = 0;
	}
    for(int i=0; i<=w; i++){
        matrix[0][i] = 0;
    }
	for(int i=1; i<=n; i++){	
		for(int j=1; j<=w; j++){
            if(weights[i-1]>j){
                matrix[i][j] = matrix[i-1][j];
            }else {
                matrix[i][j] = max(values[i-1]+matrix[i-1][j-weights[i-1]], matrix[i-1][j]);
            }
		}
	}
	
    cout << endl << matrix[n][w] << endl;

    return 0;
}