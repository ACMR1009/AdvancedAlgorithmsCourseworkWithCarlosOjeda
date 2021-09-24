Act. 1.2: Implementacion de la tecnica de programacion "Programacion dinamica" y "algoritmos avaros", fecha: 27/08/21
- Ana Cristina Munguia Romero, A01740019
- Carlos Noel Ojeda Angulo, A01741085


Este codigo es una implementacion de algoritmos para calcular las monedas necesarias para dar cambio (q-p), mediante un algoritmo avaro y uno dinamico.

En este README.md colocamos nuestros cuatro casos de prueba sugeridos:

1. Ingresaremos 4 monedas para un cambio de 7 unidades. Entrada:
    4
    1
    3
    4
    5
    7
    14
    
    Salida esperada:
    
        Resultado del metodo avaro
        5: 1
        4: 0
        3: 0
        1: 2

        Resultado del metodo dinamico
        5: 0
        4: 1
        3: 1
        1: 0
        

2. Ingresaremos 3 monedas para un cambio de 15 unidades. Entrada:
    3
    1
    7
    10
    15
    30

    Salida esperada: 
    
        Resultado del metodo avaro
        10: 1
        7: 0
        1: 5

        Resultado del metodo dinamico
        10: 0
        7: 2
        1: 1


3. Ingresaremos 5 monedas para un cambio de 63 unidades. Entrada:
    5
    1
    5
    10
    21
    25
    1
    64
    
    Salida esperada: 
        
        Resultado del metodo avaro
        25: 2
        21: 0
        10: 1
        5: 0
        1: 3

        Resultado del metodo dinamico
        25: 0
        21: 3
        10: 0
        5: 0
        1: 0


4. Ingresaremos 4 monedas para un cambio de 8 unidades. Entrada:
    4
    1
    4
    6
    10
    0
    8 

    Salida esperada: 
    
        Resultado del metodo avaro
        10: 0
        6: 1
        4: 0
        1: 2

        Resultado del metodo dinamico
        10: 0
        6: 0
        4: 2
        1: 0

