#include "stdlib.h"
#include <iostream>
#include "../include/config.h"

void backgroundSetup(const int nx, const int ny, int background[] ){
  // Création du plateau qui sera délimité par des # qui correspondent à '1' dans display.cpp
  for (int i=0; i<nx; i++) {
    background[i] = 1;
    background[nx*ny-i] = 1;}
  for (int i=0;i<ny;i++){
    background[i*nx] = 1;
    background[i*nx+nx-1] = 1;
  }
}