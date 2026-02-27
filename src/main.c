#include "hw1.h"

int main(int argc, char** argv){
        if(argc != 2){
                printf("No or wrong arguments givven. Abort!\n");
                return -1;
        }
        else{
                int n = atoi(argv[1]);
                Board_t chessboard;
                board_init(&chessboard, n);

                //make n threads
                pthread_t threads[MAX_N];
                thread_args t_args[MAX_N];
                for(int i = 0; i<n; i++){
                        t_args[i].chessboard = chessboard;
                        t_args[i].start_column = i;

                        if(pthread_create(&threads[i], NULL, solve, &t_args[i]) != 0){
                                printf("Failed to create thread %d\n", i);
                        }                
                }
                
                for(int i = 0; i<n; i++){
                        pthread_join(threads[i], NULL);
                }

                printf("The total solutions are %lld\n", solutions);
        }
}