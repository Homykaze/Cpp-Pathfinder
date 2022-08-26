# Dijkstra's pathfinding algorithm implementation in C++
Grid implementation of Dijsktra's algorithm (file 'pathfinderGrid') is my very first intuitive implementation of any kind of pathfinding algorithms, which is capable of finding the shortest route on a grid, where it is only possible to move either horizontally or vertically.

<br>

Whereas the Graph implementation (file 'pathfinderGraph') is when I actually got to learn how Dijkstra's pathfinding algorithm works. Graph implementation is much more flexible, because it can have more than 4 different directions from one node to the others, and it is able to completely replace the grid implementation. Furthermore, it is a weighted algorithm, where we can assign values (distances) indicating the level of difficulty of getting from one node to another, which are used to calculate the final route. The difference between two files (pathfinderGraph.cpp and pathfinderGrid.cpp) is about half a year, within this period I got to learn the basics of STL and had a great practice using pointers with data structures.

# Breadth-first search algorithm
I learned it just before learning the graph implementation of the Dijkstra's algorithm (breadtFirstSearch.cpp). The program demonstrated in this repository simulates a situation of a search for a mango seller in a network of the user's friends (connections) using the breadth-first search algorithm.
