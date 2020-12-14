#include "stdlib.h"
#include <iostream>
#include "../include/config.h"



void update_snake_coordinates( int snake[], int snl, int dxdy[] , bool eat){

  // On vérifie que le snake n'a pas changé de taille.
  // Dans ce cas il faut décaler le tableau d'un cran à droite et insérer un nouvel élément.

  if(eat){
    for (int i=0;i<snl-1;i++) {
    snake[i+1] = snake[i];
    snake[SNAKE_LEN+i+1] = snake[SNAKE_LEN+i];
    snake[0]=snake[0]-dxdy[0];
    snake[SNAKE_LEN] = snake[SNAKE_LEN] - dxdy[1];
  }
  }

  // Ensuite dans tous les cas on effectue les changements de coordonnées qui correspondent au déplacement du snake.

  for (int i=0;i<(snl - 1);i++) {
    snake[i] = snake[i+1];
    snake[SNAKE_LEN+i] = snake[SNAKE_LEN+i+1];
  }
  snake[snl-1] = snake[snl - 1] + dxdy[0];
  snake[SNAKE_LEN+snl-1] = snake[SNAKE_LEN+snl - 1] + dxdy[1];
  }