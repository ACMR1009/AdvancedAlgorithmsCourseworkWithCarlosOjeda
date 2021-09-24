/*  Act. 1.2: Implementacion de la tecnica de programacion "Programacion dinamica" y "algoritmos avaros"
Se reciben 'n' denominaciones de monedas que son almacenadas en un vector<int>, un precio 'p' y un pago 'q'.
Se imprimen las cantidades necesarias de cada moneda de acuerdo a un algoritmo avaro y un dinamico.
    Ana Cristina Munguia Romero, A01740019
    Carlos Noel Ojeda Angulo, A01741085
    Fecha: 27/08/21
 */

#include <iostream>
#include <vector>

using namespace std;

// Metodo mezcla para reintegrar las sublistas ordenadas de Merge Sort. Recibe los indices de los extremos del vector y el vector a ordenar.
// Complejidad: O(2n) = O(n).
void mezcla(int inicio, int fin, vector<int>& vector){
    int centro = (inicio+fin)/2,
        size = fin-inicio+1,
        i = inicio,
        j = centro+1;
    int aux[size];
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
void ordenaMerge(vector<int>& vector, int inicio, int fin){
    if(inicio < fin){
        int centro = (inicio+fin)/2;
        ordenaMerge(vector, inicio, centro);
        ordenaMerge(vector, centro+1, fin);
        mezcla(inicio, fin, vector);
    }
}

// Ordena en forma descendente los datos con el metodo de Merge Sort. Recibe el vector a ordenar.
// Complejidad: O(n log2(n)).
void ordenaMerge(vector<int>& vector){
    ordenaMerge(vector, 0, vector.size()-1);
}

// Calcula el minimo de monedas necesarias y la denominacion de cada una. Recibe un vector de monedas, un vector que almacena cuantas monedas de cada tipo son necesarias y el cambio a entregar.
// Complejidad: O(n^3) vectorMonedas.size() es una constante que puede ser despreciable segun su tamano, resultando en complejidades de O(n).
void cambioDinamico(vector<int>& vectorMonedas, vector<int>& monedasTotales, int cambio){
    vector<int> aux;
    aux.push_back(0);
    for(int i=1; i<=cambio; i++){
        int temp = cambio+1; // siempre será mayor la primera vez
        int j = vectorMonedas.size()-1;
        while(j>=0 && i>=vectorMonedas[j]){
            temp = min(aux[i-vectorMonedas[j]], temp);
            if(temp==aux[i-vectorMonedas[j]] && i==cambio){
                monedasTotales[j] = floor(cambio/vectorMonedas[j]);
                int resta = cambio - (monedasTotales[j] * vectorMonedas[j]);
                for(int k=j+1; k<vectorMonedas.size(); k++){
                    if(vectorMonedas[k]<=resta){
                        monedasTotales[k] = floor(resta/vectorMonedas[k]);
                        resta -= (monedasTotales[k] * vectorMonedas[k]);
                        if(resta==0){
                            monedasTotales[k+1] = 0;
                        }
                    }
                    else if(resta==0){
                        monedasTotales[k] = 0;
                    }
                }
            }
            j--;
        }
        aux.push_back(temp+1);
    }
}

// Calcula cuantas monedas son necesarias de cada denominacion, iniciando con la moneda de mayor valor posible (sin pasarse del cambio que necesita entregar). Recibe un vector de monedas, un vector que almacena cuantas monedas de cada tipo son necesarias y el cambio a entregar.
// Complejidad: O(n).
void cambioAvaro(vector<int>& vectorMonedas, vector<int>& monedasTotales, int cambio){
    for(int i=0; i<vectorMonedas.size(); i++){
        if(vectorMonedas[i]<=cambio){
            monedasTotales[i] = floor(cambio/vectorMonedas[i]);
            cambio -= vectorMonedas[i] * monedasTotales[i];
        }
    }
}

int main(){
    vector<int> v;
    vector<int> monedasTotalesDinamico;
    vector<int> monedasTotalesAvaro;
    int n, dato, p, q;
    
    //Se pide la cantidad total de monedas
    cin >> n;
    
    //Se ingresan las denominaciones de moneda
    for (int i=0; i<n; i++){
        cin >> dato;
        while(dato<=0){
            cout << "Ingresa un numero entero mayor a 0: " << endl;
            cin >> dato;
        }
        v.push_back(dato);
        monedasTotalesDinamico.push_back(0);
        monedasTotalesAvaro.push_back(0);
    }
    
    //Se pide el precio a pagar
    cin >> p;
    
    //Se ingresa el pago
    cin >> q;
    
    ordenaMerge(v);
    cambioDinamico(v, monedasTotalesDinamico, q-p);
    cambioAvaro(v, monedasTotalesAvaro, q-p);
    
    cout << endl << "Resultado del metodo avaro" << endl;
    for (int i=0; i<n; i++) {
        cout << v[i] << ": " <<  monedasTotalesAvaro[i] << endl;
    }
    cout << endl;
    cout << "Resultado del metodo dinamico" << endl;
    for (int i=0; i<n; i++) {
        cout << v[i] << ": " << monedasTotalesDinamico[i] << endl;
    }
    cout << endl;
    
    return 0;
}

