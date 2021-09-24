Act. 1.3: Implementacion de la tecnica de programacion "backtracking" y "ramificacion y poda"
- Ana Cristina Munguia Romero, A01740019
- Carlos Noel Ojeda Angulo, A01741085


Este codigo es una implementacion de algoritmos para **solucionar un laberinto, mediante el uso de Backtracking y Branch & Bound**.

En este README.md colocamos nuestros cuatro casos de prueba sugeridos:

1. Caso para evaluar que sucede si la matriz contiene solamente unos. Entrada:
    5
    5
    1 1 1 1 1
    1 1 1 1 1
    1 1 1 1 1
    1 1 1 1 1
    1 1 1 1 1
    
    Salida esperada (primero con Backtracking y luego con Branch & Bound):
        
        1 1 1 1 1 
        0 0 0 0 1 
        0 0 0 0 1 
        0 0 0 0 1 
        0 0 0 0 1 

        1 0 0 0 0 
        1 0 0 0 0 
        1 0 0 0 0 
        1 0 0 0 0 
        1 1 1 1 1 
        

2. Caso para evaluar que sucede si la matriz contiene solamente unos, a excepcion de un cero (para afectar a la solucion por Backtracking). Entrada:
    5
    5
    1 1 1 0 1
    1 1 1 1 1
    1 1 1 1 1
    1 1 1 1 1
    1 1 1 1 1
    
    Salida esperada (primero con Backtracking y luego con Branch & Bound):
        
        1 1 1 0 0 
        0 0 1 1 1 
        0 0 0 0 1 
        0 0 0 0 1 
        0 0 0 0 1 

        1 0 0 0 0 
        1 0 0 0 0 
        1 0 0 0 0 
        1 0 0 0 0 
        1 1 1 1 1 
        

3. Caso para evaluar un laberinto con solo una posible solucion y algunos callejones. Entrada:
    7
    6
    1 1 0 1 1 1
    1 0 0 1 0 1
    1 1 0 1 0 1
    1 0 0 1 0 1
    1 1 1 1 0 1
    0 1 0 0 0 1
    0 1 1 1 0 1
    
    Salida esperada (primero con Backtracking y luego con Branch & Bound):
        
        1 0 0 1 1 1 
        1 0 0 1 0 1 
        1 0 0 1 0 1 
        1 0 0 1 0 1 
        1 1 1 1 0 1 
        0 0 0 0 0 1 
        0 0 0 0 0 1 

        1 0 0 1 1 1 
        1 0 0 1 0 1 
        1 0 0 1 0 1 
        1 0 0 1 0 1 
        1 1 1 1 0 1 
        0 0 0 0 0 1 
        0 0 0 0 0 1 


4. Caso para evaluar un laberinto con varias soluciones (donde Branch & Bound encuentra la solucion optima). Entrada:
    14
    6
    1 0 1 1 1 1
    1 0 1 1 0 1
    1 0 1 1 0 1
    1 0 0 1 0 1
    1 1 1 1 0 1
    1 0 0 0 0 1
    1 0 0 0 0 1
    1 0 1 1 1 1
    1 0 1 1 0 0
    1 1 1 1 1 1
    1 0 0 1 0 1
    1 1 1 1 1 1
    0 1 0 0 0 0
    0 1 1 1 1 1

    Salida esperada (primero con Backtracking y luego con Branch & Bound): 
        
        1 0 0 1 1 1 
        1 0 1 1 0 1 
        1 0 1 1 0 1 
        1 0 0 1 0 1 
        1 1 1 1 0 1 
        0 0 0 0 0 1 
        0 0 0 0 0 1 
        0 0 0 1 1 1 
        0 0 0 1 0 0 
        0 0 0 1 1 1 
        0 0 0 0 0 1 
        0 1 1 1 1 1 
        0 1 0 0 0 0 
        0 1 1 1 1 1 

        1 0 0 0 0 0 
        1 0 0 0 0 0 
        1 0 0 0 0 0 
        1 0 0 0 0 0 
        1 0 0 0 0 0 
        1 0 0 0 0 0 
        1 0 0 0 0 0 
        1 0 0 0 0 0 
        1 0 0 0 0 0 
        1 0 0 0 0 0 
        1 0 0 0 0 0 
        1 1 0 0 0 0 
        0 1 0 0 0 0 
        0 1 1 1 1 1 

