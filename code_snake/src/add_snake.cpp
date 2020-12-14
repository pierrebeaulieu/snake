#include "stdlib.h"
#include <iostream>
#include "../include/config.h"

void add_snake(int* snake, int bg[], int snl, const int nx, const int ny){
  //on ajoute le snake sur le background en attribuant un '1' qui affiche un '#' au bon endroit du background
  for (int i=0; i<snl; i++) {
    bg[snake[i] + nx*snake[SNAKE_LEN+i]] = 1;
  }
}