#include "stdlib.h"
#include <iostream>
#include "../include/config.h"

void setupSnake(int snake[], int len, int nx, int ny){
  // On place aléatoirement le snake sur le plateau au début
  // Il faut faire attention à ne pas faire dépasser le snake du plateau au début donc on se place à une distance len (taille initiale
  // du snake) des bords.
  snake[0] = rand()% (nx - 2*len);
  snake[SNAKE_LEN] =rand()% (ny - 2*len);
  snake[0] = snake[0]+len;
  snake[SNAKE_LEN]=snake[SNAKE_LEN]+len;
  for (int i=1; i < len; i++) {
    // on initialise le snake à l'horizontal
    snake[i] = snake[i-1] - 1;
    snake[SNAKE_LEN+i] = snake[SNAKE_LEN+i-1]; 
  }
}