/*
 * Names           : Sofia Hall & Nick Viola
 * File Name       : main.c
 * Description     : LATER
 * 
*/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

/* structure for passing data to threads */
typedef struct {
    int row;
    int column;
} parameters;

int results[11]; /* 11 total threads for validating puzzle */
int board[9][9]; /* store sudoku numbers */

/* function to check all rows */
void *checkRows() {
    int seen[10];
    
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 10; j++) {
            seen[j] = 0;
        }

        for (int j = 0; j < 9; j++) {
            seen[board[i][j]];
        }
    }
    results[0] = 1;
    pthread_exit(NULL);
}

/* function to re)ad in board from input.txt */
void readBoard() {
    FILE *fptr = fopen("input.txt", "r");

    /* enters input.txt into array */
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            fscanf(fptr, "%d", &board[i][j]);
        }
    }
    fclose(fptr);
}

/* function to print out board */
void printBoard() {
printf("BOARD STATE IN input.txt:\n"); /* header */

    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            printf("%d ", board[i][j]);
        }
        printf("\n"); /* newline after 9 numbers */
    }
}

/* main function */
int main(int argc, char *argv) {
    readBoard();

    /* printBoard();
    printf("SOLUTION: NO\n"); */

    pthread_t tid;
    pthread_create(&tid, NULL, checkRows, NULL);
    pthread_join(tid, NULL);
    printf("rows result: %d\n", results[0]);
    return 0;
}