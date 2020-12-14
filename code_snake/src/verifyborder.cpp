#include "stdlib.h"
#include <iostream>
#include "../include/config.h"

bool verifyBorder(int snake[], int nx, int ny, int snl, int dxdy[]){  

  // On vérifie d'abord que la tête du snake ne sort pas du plateau

  if (dxdy[0] == 1 && snake[snl-1] == nx - 2) {
    return false;
  }
  if (dxdy[0] == -1 && snake[snl-1] == 1) {
    return false;
  }
  if (dxdy[1] == 1 && snake[SNAKE_LEN + snl - 1] == ny-2) {
    return false;
  }
  if (dxdy[1] == -1 && snake[SNAKE_LEN + snl - 1] == 1) {
    return false;
  }

  // Puis on vérifie que le snake ne se mord pas la queue

  if (snl > 3) {
    int test_x = snake[snl - 1];
    int test_y = snake[SNAKE_LEN + snl - 1];
    for (int i=0; i<snl-1; i++) {
      if (test_x == snake[i] && test_y == snake[SNAKE_LEN + i]) {
        return false;
      }
    }
  } 
  return true;
}