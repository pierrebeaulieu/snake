#include <iostream>
#include "sys/ioctl.h"

#include "stdlib.h"

#include "../include/config.h"
#include "../include/internals.h"
#include "../include/display.h"
#include "../include/add_snake.h"
#include "../include/backgroundSetup.h"
#include "../include/remove_snake.h"
#include "../include/setupSnake.h"
#include "../include/snake_movement.h"
#include "../include/update_snake_coordinates.h"
#include "../include/verifyborder.h"
#include "../include/food.h"






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