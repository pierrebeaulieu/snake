#include <iostream>
#include "sys/ioctl.h"

#include "stdlib.h"

#include "include/config.h"
#include "include/internals.h"
#include "include/display.h"
#include "include/add_snake.h"
#include "include/backgroundSetup.h"
#include "include/remove_snake.h"
#include "include/setupSnake.h"
#include "include/snake_movement.h"
#include "include/update_snake_coordinates.h"
#include "include/verifyborder.h"
#include "include/food.h"
#include "include/startGame.h"


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