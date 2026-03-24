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

/* checks each row if it contains all digits 1-9 */
void *checkRows(void *param) {
    int seen[10];
    
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 10; j++) {
            seen[j] = 0;
        }

        for (int j = 0; j < 9; j++) {
            int val = board[i][j];
            if (seen[val] != 0) {
                results[0] = 0; /* returns 0 if duplicates */
                pthread_exit(NULL);
            }
            seen[val] = 1;
        }
    }
    results[0] = 1; /* returns 1 if all digits 1-9 are seen */
    pthread_exit(NULL);
}

/* checks each col if it contains all digits 1-9 */
void *checkCols(void *param) {
    int seen[10];
    
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 10; j++) {
            seen[j] = 0;
        }

        for (int j = 0; j < 9; j++) {
            int val = board[j][i];
            if (seen[val] != 0) {
                results[1] = 0; /* returns 0 if duplicates */
                pthread_exit(NULL);
            }
            seen[val] = 1;
        }
    }
    results[1] = 1; /* returns 1 if all digits 1-9 are seen */
    pthread_exit(NULL);
}

/* checks 3 by 3 if it contains all digits 1-9 */
void *checkSquare(void *param) {
    parameters *data = (parameters *) param;
    int row = data->row;
    int col = data->column;
    int index = (row / 3) * 3 + (col / 3) + 2;

    int seen[10];
    for (int i = 0; i < 10; i++) {
        seen[i] = 0;
    }

    for (int i = row; i < row + 3; i++) {
        for (int j = col; j < col + 3; j++) {
            int val = board[i][j];
            if (seen[val] != 0) {
                results[index] = 0; /* returns 0 if duplicates */
                pthread_exit(NULL);
            }
            seen[val] = 1;
        }
    }
    results[index] = 1; /* returns 1 if 1-9 is in square */
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
    printBoard();

    return 0;
}