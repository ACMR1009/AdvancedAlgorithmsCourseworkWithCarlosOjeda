Act. 3.3: Implementacion de "Knapsack problem" 
- Ana Cristina Munguia Romero, A01740019
- Carlos Noel Ojeda Angulo, A01741085


Este codigo es una implementacion del algoritmo para **resolver el "Knapsack problem"**. Se encuentra el beneficio maximo posible a partir de una lista de 'n' articulos con peso sin exceder la capacidad de la mochila (peso maximo 'w').

En este README.md colocamos nuestros cuatro casos de prueba sugeridos:

1. Caso para evaluar que sucede **si los objetos tienen peso 0**. 
    
    Entrada:

        3
        1
        2
        3
        0
        0
        0
        10

    Salida esperada:

        6

2. Caso para evaluar que sucede **si todos los objetos excenden el peso maximo de la mochila**. 

    Entrada:

        3
        1
        2
        3
        3
        3
        3
        2

    Salida esperada:

        0

3. Caso para evaluar que sucede **si hay varias maneras de llenar la mochila con el mismo peso pero beneficios distintos**. 
    
    Entrada:

        4
        4
        3
        3
        11
        1
        1
        1
        3
        3

    Salida esperada:

        11

4. Caso para evaluar que sucede **si hay varias maneras de llenar la mochila con distintos pesos y beneficios**. 

    Entrada:

        6
        1
        3
        2
        4
        6
        5
        5
        6
        4
        2
        3
        1
        3

    Salida esperada:

        9