#include "stdlib.h"
#include <iostream>
#include "../include/config.h"

void snake_movement( char key, int dxdy[] ){
  // On joue avec les touches q,s,d,z d'un clavier azerty.
  if (key == 'q') {
    dxdy[0] = -1;
    dxdy[1] = 0;
  }
  if (key == 'd') {
    dxdy[0] = 1;
    dxdy[1] = 0;
  }
  if (key == 's') {
    dxdy[0] = 0;
    dxdy[1] = 1;
  }
  if (key == 'z') {
    dxdy[0] = 0;
    dxdy[1] = -1;
  }
}