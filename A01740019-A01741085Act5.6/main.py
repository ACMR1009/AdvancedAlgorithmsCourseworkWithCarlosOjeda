# Actividad 5.6 Implementación de Simulated Annealing
# Ana Cristina Munguía Romero, A0174019
# Carlos Noel Ojeda Angulo, A01741085
# Date: November 26th, 2021

import pandas as pd
import matplotlib.pyplot as plt
import random
import math

N = 128 # Total number of cities

# Read the file
cities_distance = pd.read_csv("data/cities_128.csv", header = None)

# Function to calculate the total cost of a path
# Complexity: O(N)
def path_cost(path):
    cost = 0
    for i in range(1,N):
        city1 = path[i-1]
        city2 = path[i]
        cost = cost + cities_distance[city1][city2]
    cost = cost + cities_distance[path[N-1]][path[0]] #Cost to hometown
    return cost

# Function to find a neighboring succesor to any given possible solution
# Complexity: O(1)
def succesor(path):
    sample = random.sample(range(N), 2)
    
    city1 = sample[0]
    city2 = sample[1]

    aux = path[city1]
    path[city1] = path[city2]
    path[city2] = aux
    return path
    
solution = random.sample(range(N), N) # Create a random solution
cost = path_cost(solution) # Calculate initial cost

# Simulated Annealing
# Depending on the number of iterations for a given temperature, the time complexity could be linear O(n) or quadratic O(n^2). Note that 'n' does not represent the number of cities ('N'), rather it depends on the cooling schedule.
temperature = 1000
counter = 0
result = [["iteration", "temperature", "cost"]]
while temperature >= 10:
    for i in range(250):
        succesor_solution = solution.copy()
        succesor_solution = succesor(succesor_solution)
        succesor_cost = path_cost(succesor_solution)
        
        delta = succesor_cost - cost
        if(delta > 0):
            if(random.random() <= math.exp(-delta / temperature)):
                solution = succesor_solution
                cost = succesor_cost
        else:
            solution = succesor_solution
            cost = succesor_cost

    result.append([counter, temperature, cost])
    temperature = temperature * 0.95
    counter = counter + 1
    
# Print the path proposed and its cost
print('Final solution Path: ', solution)
print('Cost of final solution: ', cost)

# Create a file with a table
path_file = pd.DataFrame(result)
path_file.to_csv('simulated_annealing_data.csv', index = False, header = 0)

# Create a file with a table
data = pd.read_csv("simulated_annealing_data.csv", header = 0)
data.plot(x="iteration", y="cost")
data.plot(x="iteration", y="temperature")