#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

typedef struct Queen{
        int size;       //sizes of the vectors
        int* xvector;   //the squares the queen sees horizontaly
        int* yvector;   //the squares the queen sees verticaly
        int* zvector;   //the squares the queen sees diagonaly 
}Queen_t;

typedef struct Board{
        int nqueens;    //the number of queens on the board
        int size;       //n size of the board
        int** board;    //the 2d array that will hold the values of the board (0 for empty, 1 if there is a queen on that coordinate)
}Board_t;

int board_init(Board_t **chessboard, int n);
int queen_init(Queen_t **queen, int n);