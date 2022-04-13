
//
//  main.cpp
//  SnakePro
//  Created by Alexis Gasga on 04/01/21.
//  Copyright © 2021 Alexis Gasga. All rights reserved.
//

#include <iostream>
#include <cstdlib>
#include <ncurses.h>
using namespace std;
//#include <time.h>
bool endGame;
const int width = 20, height = 20;
int x,y, pointX, pointY, score;
enum eDirection {STOP = 0, LEFT, RIGHT, UP, DOWN};//direction
eDirection dir;

int TailX[100], TailY[100];
int nTail = 0;

void Setting() {
// Function of settings
    initscr();
    clear();
    noecho();
    cbreak();
    curs_set(0);

    endGame = false;
    dir = STOP; //the snake will not move at first
    x = width/2; // snake will start at the middle, divide screen by half
    y = height/2;
    pointX = (rand() % width) + 1;
    pointY = (rand() % height) + 1;
    score = 0;

}
//Matrix of drawling game

void Draw() {

    clear();

    for (int i = 0; i < width + 2; i++)
        mvprintw(0, i, "+");// mvprint iscout in cursers,cout does not work

    for (int i = 0; i < height + 2; i++)
    {
        for (int j = 0; j < width + 2; j++)
        {
            if (i == 0 | i ==21)
                mvprintw(i, j, "-");
            else if (j == 0 | j == 21)
                mvprintw(i, j, "|");
            else if (i == y && j == x)
                mvprintw(i, j, "*");
            else if (i == pointY && j == pointX)
                mvprintw(i, j, "*");
            else
                for (int k = 0; k < nTail; k++)
                {
                    if (TailX[k] == j && TailY[k] == i)
                        mvprintw(i, j, "@");
                }
        }
    }
    mvprintw(7, 27, "------BIENVENIDO------");//Menu
    mvprintw(8, 27, "---------AL-----------");
    mvprintw(9, 27, "----JUEGO DE SNAKE----");
    mvprintw(10, 27, "-------CREADO---------");
    mvprintw(11, 27, "--------POR-----------");
    mvprintw(12, 27,  "----ALEXIS GASGA------");
    mvprintw(20, 27,  "------Puntos %d-----", score);
 

    refresh();


}
//switch of direction
void Input() {

    keypad(stdscr, TRUE);
    halfdelay(3);//Speed of Game

    int c = getch();

    switch(c)//Direction of snake
    {
    case KEY_LEFT:
        dir = LEFT;
        break;
    case KEY_RIGHT:
        dir = RIGHT;
        break;
    case KEY_UP:
        dir = UP;
        break;
    case KEY_DOWN:
        dir = DOWN;
        break;
    case 113:// Code for letter 'Q' this will end the game if key 'Q' pressed
            endGame = true;
            break;
    }

}

void Cord() {

    int prevX = TailX[0];
    int prevY = TailY[0];
    int prev2X, prev2Y;

    //Tail point to head
    TailX[0] = x;
    TailY[0] = y;

    for (int i = 1; i < nTail; i++)
    {
        prev2X = TailX[i];
        prev2Y = TailY[i];
        TailX[i] = prevX;
        TailY[i] = prevY;
        prevX = prev2X;
        prevY = prev2Y;
       
    }

    //This moves the snake by using the coordinate adding and subtracting
    switch (dir) {
        case LEFT:
            x--;
            break;
        case RIGHT:
            x++;
            break;
        case UP:
            y--;
            break;
        case DOWN:
            y++;
            break;
        default:
            break;
    }
//Will end the game when it hits end of graph
    if (x > width || x < 1 || y > height){
        endGame = true;
    }
    if (x == pointX && y == pointY)
    {
        score++;
        pointX = (rand() % width)+1;
        pointY = (rand() % height)+1;
        nTail++;
    }

    for (int i = 0; i < nTail; i++)
        if (TailX[i] == x && TailY[i] == y)
        {
            endGame = true;
        }
}

int main() {
   
    
    Setting();

    while(!endGame)//The player does not lose conintue with game
    {
        

        Draw();
        Input();
        Cord();
        
    }

    getch();
    endwin();

    return 0;
}
