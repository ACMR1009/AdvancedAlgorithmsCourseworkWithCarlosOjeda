/*  Act. 1.3: Implementacion de la tecnica de programacion "backtracking" y "ramificacion y poda"
Este codigo es una implementacion de algoritmos para solucionar un laberinto, mediante el uso de Backtracking y Branch & Bound.
Se reciben 'm' filas y 'n' columnas para formar una matriz que representa el laberinto.
Se imprimen dos soluciones obtenidas con los metodos Backtracking y Branch & Bound (respectivamente).
    Ana Cristina Munguia Romero, A01740019
    Carlos Noel Ojeda Angulo, A01741085
    Fecha: 03/09/21
*/

#include <iostream>
#include <stack>
#include <queue>

using namespace std;

int main(){
    int m, n; // m filas y n columnas

    cin >> m;
    cin >> n;

    // Agregamos columnas y filas para insertar un marco de 0s al laberinto
    m += 2;
    n += 2;

    int matrizBranch[m][n], matrizBacktracking[m][n];

    // Ingresa datos a la matriz
    int dato;
    for (int i=0; i<m; i++) {
        for (int j=0; j<n; j++) {
            if (i==0 || i==m-1) { // Marco de 0s
                dato = 0;
            }
            else if(j==0 || j==n-1) { // Marco de 0s
                dato = 0;
            }
            else {
                cin >> dato; // Casillas del laberinto (0 / 1)
            }
            matrizBranch[i][j] = dato;
            matrizBacktracking[i][j] = dato;
        }
    }

    //---------------------------------------------------------------------------------
    // Inicio de Backtracking

    // A partir de la casilla de origen (1, 1) se realiza un Depth First Search (busqueda por profundidad)
    // hasta llegar a la casilla del fin del laberinto (m-2, n-2). Esta busqueda NO GARANTIZA una solucion optima.
    // Complejidad: La busqueda tiene complejidad O(m+n) y la impresion tiene complejidad O(m*n).
    deque<pair<int,int>> posiciones;
    posiciones.push_back({1,1});
    int x, y;
    while ((posiciones.back().first != m-2) || (posiciones.back().second != n-2)) {

        y = posiciones.back().first;
        x = posiciones.back().second;
        matrizBacktracking[y][x] = 0;

        if (matrizBacktracking[y][x+1] == 1) {
            posiciones.push_back({y, x+1});
        }
        else if (matrizBacktracking[y+1][x] == 1) {
            posiciones.push_back({y+1, x});
        }
        else if (matrizBacktracking[y][x-1] == 1) {
            posiciones.push_back({y, x-1});
        }
        else if (matrizBacktracking[y-1][x] == 1) {
            posiciones.push_back({y-1, x});
        }
        else {
            posiciones.pop_back();
        }
    }
    posiciones.push_back({y, x});

    // Imprime resultado de Backtracking
    for (int i=1; i<=m-2; i++) {
        for (int j=1; j<=n-2; j++) {
            matrizBacktracking[i][j] = 0; // Llenamos la matriz de 0s
        }
    }

    int pos = posiciones.size();
    for (int i=0; i<pos; i++) { // Llenamos la matriz de 1s donde corresponde
        matrizBacktracking[posiciones.front().first][posiciones.front().second] = 1;
        posiciones.pop_front();
    }
    cout << endl;

    // Mostramos la solucion del laberinto por Backtracking
    for (int i=1; i<=m-2; i++) {
        for (int j=1; j<=n-2; j++) {
            cout << matrizBacktracking[i][j] << " ";
        }
        cout << endl;
    }

    // Fin de Backtracking
    //---------------------------------------------------------------------------------
    // Inicio de Branch & Bound

    // A partir de la casilla de origen (1, 1) se realiza un Breadth First Search (busqueda por layers)
    // hasta llegar a la casilla del fin del laberinto (m-2, n-2). Esta busqueda encuentra la SOLUCION OPTIMA.
    // Complejidad: La busqueda tiene complejidad cuadratica y la impresion tiene complejidad O(m*n).
    deque<pair<pair<int,int>,pair<int,int>>> finalPath;
    queue<pair<int,int>> pos2;
    x = 1;
    y = 1;
    finalPath.push_back({{x,y},{x,y}});
    while (x!=m-2 || y!=n-2) {
        matrizBranch[x][y] = 0;
        if (matrizBranch[x][y+1] == 1) {
            pos2.push({x,y+1});
            finalPath.push_back({{x,y+1},{x,y}});
        }
        if (matrizBranch[x+1][y] == 1) {
            pos2.push({x+1,y});
            finalPath.push_back({{x+1,y},{x,y}});
        }
        if (matrizBranch[x][y-1] == 1) {
            pos2.push({x,y-1});
            finalPath.push_back({{x,y-1},{x,y}});
        }
        if (matrizBranch[x-1][y] == 1) {
            pos2.push({x-1,y});
            finalPath.push_back({{x-1,y},{x,y}});
        }
        x = pos2.front().first;
        y = pos2.front().second;
        pos2.pop();

    }

    // Imprime resultado de Branch & Bound
    for (int i=1; i<=m-2; i++) {
        for (int j=1; j<=n-2; j++) {
            matrizBranch[i][j] = 0; // Llenamos la matriz de 0s
        }
    }

    // Llenamos la matriz de 1s donde corresponde
    finalPath.push_back({{m-1,n-1},{m-2,n-2}});
    int nodos = finalPath.size();
    int auxY, auxX;
    matrizBranch[1][1] = 1;
    for (int i=0; i<nodos; i++) {
        auxY = finalPath.back().second.first;
        auxX = finalPath.back().second.second;
        if (auxY != 1 || auxX !=1) {
            matrizBranch[auxY][auxX] = 1;
            finalPath.pop_back();
            while (auxY != finalPath.back().first.first || auxX != finalPath.back().first.second) {
                finalPath.pop_back();
            }
            auxY = finalPath.back().second.first;
            auxX = finalPath.back().second.second;
        }
    }
    matrizBranch[m-2][n-2] = 1;
    cout << endl;

    // Mostramos la solucion del laberinto por Branch & Bound
    for (int i=1; i<=m-2; i++) {
        for (int j=1; j<=n-2; j++) {
            cout << matrizBranch[i][j] << " ";
        }
        cout << endl;
    }

    // Fin de Branch & Bound
    //---------------------------------------------------------------------------------

    return 0;
}
