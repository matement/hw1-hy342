#ifndef HW1_H
#define HW1_H

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define MAX_N 15

typedef struct{
        int size;       //n size of the board
        int board[MAX_N];    //array holding the chessboard (indeex = rows, value = columns)

        int col_attack[MAX_N];      //it tracks the columns if a queen is attacking another (0=safe, 1=udner attack)
        int left_diagonal_attack[2*MAX_N-1];        //it tracks the left to right diagonal if a queen attack another
        int right_diagonal_attack[2*MAX_N-1];       //it tracks the right to left diagonal if a queen attack another
}Board_t;

typedef struct{
        Board_t chessboard;
        int start_column;
}thread_args;

extern long long  solutions;
extern pthread_mutex_t sol_mutex;

int board_init(Board_t *chessboard, int n);
void *solve(void* args);

#endif