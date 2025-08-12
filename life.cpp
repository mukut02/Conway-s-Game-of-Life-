#include <SDL2/SDL.h>
#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;
#define WHITE 0xffffff
#define BLACK 0x000000
const int WINDOW_WIDTH  = 1000;
const int WINDOW_HEIGHT = 800;
const int CELL_SIZE=5;
const int GAME_HEIGHT =WINDOW_HEIGHT/CELL_SIZE;
const int GAME_WIDTH  =WINDOW_WIDTH/CELL_SIZE;

/*
ALGORITHM : 
At each step in time, the following transitions occur:

1. Any live cell with < 2 live neighbours dies, as if by *underpopulation.
2. Any live cell with 2 or 3 live neighbours lives on to the *next generation.
3. Any live cell with >3 live neighbours dies, as if by *overpopulation.
4. Any dead cell with ==3 live neighbours becomes a live cell, as if by *reproduction.

In this implementation 
1st matrix generated randomly with probality in that live_cell probability is 1/8 
*/

bool isAlive(vector<vector<int>> &game, 
    const int x, const int y){
    int alive=0;

    for(int dx=-1;dx<=1;++dx){
        for(int dy=-1;dy<=1;++dy){
            if(dx==0 && dy==0) continue;
            int nx=x + dx;
            int ny=y + dy;
            
           if(nx>=0 && nx<GAME_WIDTH && ny>=0 && ny<GAME_HEIGHT && game[nx][ny]==1){
              alive++;
            }
        }
    }
    if(game[x][y]==1){
        // for alive cell
        if(alive<2){
            // 1.underpopulation
            return false;
        }
        else if(alive==2 || alive==3){
            // 2.next generation lives on
            return true;
        }
        else if(alive > 3){
            // 3.overpopulation
            return false;
        }
    }
    else{
        // for dead cell
        if(alive==3){
            // 4.reproduction
            return true;
        }
        else{
            // remains dead
            
        }
    }
    return false;
}

int main(){
    // 2 buffers to update the game
   
    vector<vector<int>> display(GAME_WIDTH, vector<int>(GAME_HEIGHT, 0));
    vector<vector<int>> swap(GAME_WIDTH, vector<int>(GAME_HEIGHT, 0));

    printf("Game of Life\n");
    SDL_Init(SDL_INIT_VIDEO); // intiliased video
    SDL_Window* window=SDL_CreateWindow("Game of Life", SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,WINDOW_WIDTH,WINDOW_HEIGHT,0 );
    SDL_Surface* surface = SDL_GetWindowSurface(window);
    
    // seeder value
    // here using randome pts

    for(auto &row : display){
        for(auto &cell : row){
            if( rand() % 8==0){
                cell=1;
            }
            else{
                cell=0;
            }
        }
    }
    int simulation_running=1;
    SDL_Event event;

    SDL_Rect erase_rect = (SDL_Rect){0,0,WINDOW_WIDTH,WINDOW_HEIGHT};
    while(simulation_running){
         while(SDL_PollEvent(&event)){
            if(event.type == SDL_QUIT){
                simulation_running=0;
            }
         }
         
         SDL_FillRect(surface,&erase_rect, BLACK);

         for(int row=0;row <GAME_WIDTH; ++row){
             for(int col =0; col <GAME_HEIGHT; ++col){
                swap[row][col] = isAlive(display, row ,col) ? 1 : 0;
             }
        }
        
        for(int row=0;row <GAME_WIDTH; ++row){
             for(int col =0; col <GAME_HEIGHT; ++col){
                if(swap[row][col]==1){
                    SDL_Rect pixel = (SDL_Rect){(int)row*CELL_SIZE,(int)col*CELL_SIZE,CELL_SIZE,CELL_SIZE};
                    SDL_FillRect(surface,&pixel,WHITE);
                }
             }
        }

        copy(swap.begin(), swap.end(), display.begin());

        SDL_UpdateWindowSurface(window);
        SDL_Delay(60);

    }
    SDL_Delay(5000);
    SDL_Quit();
    
}
