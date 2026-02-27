#include "hw1.h"
long long solutions = 0;
pthread_mutex_t sol_mutex = PTHREAD_MUTEX_INITIALIZER;

/**
 * initialised a chessboard
 * it takes a Board_t and a size nz
 * it returns 0 if anything failed
 * it returns 1 if all went well
 */
int board_init(Board_t *chessboard, int n){
        if (n > MAX_N || n <= 0) {
                printf("Error: Board size must be between 1 and %d.\n", MAX_N);
                exit(1);
        }

        (*chessboard).size = n;

        for(int i = 0; i<n; i++){
                (*chessboard).board[i] = -1;    //-1 is empty
                (*chessboard).col_attack[i] = 0;
        }

        for(int i = 0; i<(2*n-1); i++){
                (*chessboard).left_diagonal_attack[i] = 0;
                (*chessboard).right_diagonal_attack[i] = 0;
        }
        return 1;
}

void backtrack(Board_t *state, int row){
        //if we reached the last row return
        if(row == state->size){
                pthread_mutex_lock(&sol_mutex);
                solutions++;
                pthread_mutex_unlock(&sol_mutex);
                return;
        }

        for(int col = 0; col<state->size; col++){
                //calculate diagonals
                int left_diagonal = row+col;
                int right_diagonal = row-col + (state->size - 1);
                //check if the square is safe 
                if(!state->col_attack[col] && !state->left_diagonal_attack[left_diagonal]\
                && !state->right_diagonal_attack[right_diagonal]){
                        //make the move
                        state->board[row] = col;
                        state->col_attack[col] = 1;
                        state->left_diagonal_attack[left_diagonal] = 1;
                        state->right_diagonal_attack[right_diagonal] = 1;

                        backtrack(state, row+1);        //move to the next row

                        //undo the move
                        state->col_attack[col] = 0;
                        state->left_diagonal_attack[left_diagonal] = 0;
                        state->right_diagonal_attack[right_diagonal] = 0;
                }
        }
}

void *solve(void* args){
        thread_args* t_args = (thread_args*)args;
        Board_t chessboard = t_args->chessboard;
        int column = t_args->start_column;
        
        int row = 0;
        int left_diagonal = row+column;
        int right_diagonal = row-column + (chessboard.size - 1);

        //place the first queen
        chessboard.board[row] = column;
        chessboard.col_attack[column] = 1;
        chessboard.left_diagonal_attack[left_diagonal] = 1;
        chessboard.right_diagonal_attack[right_diagonal] = 1;

        backtrack(&chessboard, 1);       
        return NULL;
}