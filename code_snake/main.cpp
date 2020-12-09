#include <iostream>
#include "sys/ioctl.h"

#include "stdlib.h"

#include "include/config.h"
#include "include/internals.h"
#include "include/display.h"
#include "include/food.h"


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

void add_snake(int* snake, int bg[], int snl, const int nx, const int ny){
  //on ajoute le snake sur le background en attribuant un '1' qui affiche un '#' au bon endroit du background
  for (int i=0; i<snl; i++) {
    bg[snake[i] + nx*snake[SNAKE_LEN+i]] = 1;
  }
}


void remove_snake(int* snake, int bg[], int snl, const int nx, const int ny){
  // on retire le snake du background
  for (int i=0; i<snl; i++) {
    bg[snake[i] + nx*snake[SNAKE_LEN+i]] = -1;
  }
}
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


void startGame(const int& lap, const int& nx, const int& ny, int& snl, int* snake, int* bg){
    char key;
    int dxdy[2] = {1,0};
    int food[2] = {0,0};

    createFood( bg, food, nx, ny );

    while( true ){
        internal::frameSleep(lap);
        if( internal::keyEvent() ){
            std::cin >> key; 
            snake_movement(key, dxdy);
        }
        backgroundClear();
        add_snake( snake, bg, snl, nx, ny );
        printFrame(nx, ny, bg);
        remove_snake(snake, bg, snl, nx, ny);
        bool out =  verifyBorder(snake, nx, ny, snl, dxdy);
        if( out == false){
            std::cerr << "" << std::endl;
            exit(1);
        }
        bool eat = eatFood(food, snake);
        if(eat){
            createFood(bg, food, nx, ny);
            snl++;
        }
        update_snake_coordinates(snake, snl, dxdy, eat);

    }
}



int main(){
    const int nx = 50;
    const int ny = 25;
    const int lap=200;

    int snake_len = 3;
    int background[nx*ny] ;
    for( int i=0; i<nx*ny; i++){
        background[i] = -1;
    }
    int snake[2*SNAKE_LEN];

    backgroundSetup(nx, ny, background);
    setupSnake(snake, snake_len, nx, ny);


    startGame(lap, nx, ny, snake_len, snake, background);

}