Actividad Integradora 2
- Ana Cristina Munguia Romero, A01740019
- Carlos Noel Ojeda Angulo, A01741085

This code is an implementation of different graph-related algorithms to **find the shortest distance between two nodes, solve pseudo-optimally the Traveling Salesman Problem, find maximum information flow between two nodes and, by using a Voronoi diagram, find the nearest station for a given site**.

Here we specify the meaning behind every output line and how to correctly interpret it.

- The output is composed of three sections that are delimited by linebreaks.

    1. The first section shows the shortest possible distance for connecting every two neighborhoods in the format *(a,b): #*, where *a* and *b* are the neighborhoods being connected and *#* is the distance in km.
    2. The second section shows a pseudo-optimal path for traversing all neighborhoods in a single path (the neighborhoods are shown as letters and separeted by spaces).
    3. The third section shows the maximum possible information flow between the starting neighborhood and the final neighborhood (*0* and *n-1*, where *n* is the number of neighborhoods).
    4. The fourth section shows the vertices of the Voronoi region that a given place/house (point) would be a part of. This point needs to be provided by the user (type it on the terminal) using format *(x,y)*. Example: 
	
	(420,580)


- Expected output*:

        (a,b): 16
        (a,c): 34
        (a,d): 32
        (b,c): 18
        (b,d): 21
        (c,d): 7

        a b c d a 

        78

        Query point (420,580) lies on a Voronoi face.
        The vertices of the Voronoi face are (in counterclockwise order):
            point at infinity
            (350.841,343.458)

*There is a screenshot of the expected Voronoi diagram included (example.png)