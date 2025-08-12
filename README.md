# Conway-s-Game-of-Life-
Implementation of Conway's Game of Life in C++ using SDL2

ALGORITHM : 
At each step in time, the following transitions occur:

1. Any live cell with < 2 live neighbours dies, as if by *underpopulation.
2. Any live cell with 2 or 3 live neighbours lives on to the *next generation.
3. Any live cell with >3 live neighbours dies, as if by *overpopulation.
4. Any dead cell with ==3 live neighbours becomes a live cell, as if by *reproduction.

In this implementation 
1st matrix generated randomly with probality in that live_cell probability is 1/8 

TO RUN:
g++ -std=c++17 life.cpp -o life `sdl2-config --cflags --libs` -lSDL2_tt 

./life
