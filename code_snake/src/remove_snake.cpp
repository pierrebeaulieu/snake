#include "stdlib.h"
#include <iostream>
#include "../include/config.h"


void remove_snake(int* snake, int bg[], int snl, const int nx, const int ny){
  // on retire le snake du background
  for (int i=0; i<snl; i++) {
    bg[snake[i] + nx*snake[SNAKE_LEN+i]] = -1;
  }
}