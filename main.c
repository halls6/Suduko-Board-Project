/*
 * Names           : Sofia Hall & Nick Viola
 * File Name       : main.c
 * Description     : LATER
 * 
*/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>

/* structure for passing data to threads */
typedef struct {
    int row;
    int column;
    int index;
} parameters;

int results[27]; /* max 27 threads for both methods */
int board[9][9]; /* store sudoku numbers */

/* METHOD 1 (11 THREADS) FUNCS */

/* checks each row if it contains all digits 1-9 */
void *checkRows1(void *param) {
    parameters *data = (parameters*) param;
    int idx = data->index;
    
    int seen[10];
    
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 10; j++) { seen[j] = 0; }

        for (int j = 0; j < 9; j++) {
            int val = board[i][j];
            if (val < 1 || val > 9 || seen[val] != 0) {
                results[idx] = 0; /* returns 0 if duplicates */
                pthread_exit(NULL);
            }
            seen[val] = 1;
        }
    }
    results[idx] = 1; /* returns 1 if all digits 1-9 are seen */
    pthread_exit(NULL);
}

/* checks each col if it contains all digits 1-9 */
void *checkCols1(void *param) {
    parameters *data = (parameters*) param;
    int idx = data->index;

    int seen[10];
    
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 10; j++) { seen[j] = 0; }

        for (int j = 0; j < 9; j++) {
            int val = board[j][i];
            if (val < 1 || val > 9 || seen[val] != 0) {
                results[idx] = 0; /* returns 0 if duplicates */
                pthread_exit(NULL);
            }
            seen[val] = 1;
        }
    }
    results[idx] = 1; /* returns 1 if all digits 1-9 are seen */
    pthread_exit(NULL);
}

/* checks 3 by 3 if it contains all digits 1-9 */
void *checkSquare(void *param) { /* used by method 1 and 2 */
    parameters *data = (parameters *) param;
    int row = data->row;
    int col = data->column;
    int idx = data->index;

    int seen[10];

    for (int i = 0; i < 10; i++) { seen[i] = 0; }

    for (int i = row; i < row + 3; i++) {
        for (int j = col; j < col + 3; j++) {
            int val = board[i][j];
            if (val < 1 || val > 9 || seen[val] != 0) {
                results[idx] = 0; /* returns 0 if duplicates */
                pthread_exit(NULL);
            }
            seen[val] = 1;
        }
    }
    results[idx] = 1; /* returns 1 if 1-9 is in square */
    pthread_exit(NULL);
}

/* METHOD 2 (27 THREADS) FUNCS */

/* checks one row if it contains all digits 1-9 */
void *checkRows2(void *param) {
    parameters *data = (parameters*) param;
    int row = data->row;
    int idx = data->index;
    
    int seen[10];
    
    for (int j = 0; j < 10; j++) { seen[j] = 0; }

        for (int j = 0; j < 9; j++) {
            int val = board[row][j]; /* checking only 1 row */
            if (val < 1 || val > 9 || seen[val] != 0) {
                results[idx] = 0; /* returns 0 if duplicates */
                pthread_exit(NULL);
            }
            seen[val] = 1;
        }
    results[idx] = 1; /* returns 1 if all digits 1-9 are seen */
    pthread_exit(NULL);
}

/* checks one col if it contains all digits 1-9 */
void *checkCols2(void *param) {
    parameters *data = (parameters*) param;
    int col = data->column;
    int idx = data->index;
    
    int seen[10];
    
    for (int j = 0; j < 10; j++) { seen[j] = 0; }

        for (int i = 0; i < 9; i++) {
            int val = board[i][col]; /* checking only 1 row */
            if (val < 1 || val > 9 || seen[val] != 0) {
                results[idx] = 0; /* returns 0 if duplicates */
                pthread_exit(NULL);
            }
            seen[val] = 1;
        }
    results[idx] = 1; /* returns 1 if all digits 1-9 are seen */
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
int main(int argc, char *argv[]) {
    int mode = atoi(argv[1]);

    readBoard();
    printBoard();

    /* 9 threads for 3 by 3 square (used by both methods)*/
    int rows[9] = {0, 0, 0, 3, 3, 3, 6, 6, 6}; /* starting positions*/
    int cols[9] = {0, 3, 6, 0, 3, 6, 0, 3, 6};

    if (mode == 1) { /* Method 1: 11 threads */
        /* thread 1: all rows, thread 2: all cols, threads 3-11: subgrids */

        pthread_t threads[11];
        parameters* data[11];

        for (int i = 0; i < 11; i++) {
            data[i] = (parameters *) malloc(sizeof(parameters));
            results[i] = 0;
        }

        /* row thread */
        data[0]->row = 0;
        data[0]->column = 0;
        data[0]->index = 1;
        pthread_create(&threads[0], NULL, checkRows1, data[0]);

        /* col thread */
        data[1]->row = 0;
        data[1]->column = 0;
        data[1]->index = 0;
        pthread_create(&threads[1], NULL, checkCols1, data[1]);

        /* subgrids threads */
        for (int i = 2; i < 11; i++) {
            data[i]->row = rows[i - 2];
            data[i]->column = cols[i - 2];
            data[i]->index = i;
            pthread_create(&threads[i], NULL, checkSquare, data[i]);
        }

        for (int i = 0; i < 11; i++) {
            pthread_join(threads[i], NULL);
        }

        int valid = 1;
        for (int i = 0; i < 11; i++) {
            if (results[i] == 0) {
                valid = 0;
                break;
            }
        }
    /* printing to the terminal */
    if (valid) { printf("SOLUTION: YES\n"); }
    else { printf("SOLUTION: NO\n"); }

    /* freeing the memory */
    for (int i = 0; i < 11; i++) { free(data[i]); }

    }

    if (mode == 2) { /* Method 2: 27 threads */
        /* threads 1-9: each row, threads 10-18: each cols, threads 19-27: subgrids */

        pthread_t threads[27];
        parameters* data[27];

        for (int i = 0; i < 27; i++) {
            data[i] = (parameters *) malloc(sizeof(parameters));
            results[i] = 0;
        }

        /* row threads */
        for (int i = 0; i < 9; i++) {
            data[i]->row = i;
            data[i]->column = 0;
            data[i]->index = i;
            pthread_create(&threads[i], NULL, checkRows2, data[i]);
        }

        /* col thread */
        for (int i = 9; i < 18; i++) {
            data[i]->row = 0;
            data[i]->column = i - 9;
            data[i]->index = i;
            pthread_create(&threads[i], NULL, checkRows2, data[i]);
        }

        /* subgrids threads */
        for (int i = 18; i < 27; i++) {
            data[i]->row = rows[i - 18];
            data[i]->column = cols[i - 18];
            data[i]->index = i;
            pthread_create(&threads[i], NULL, checkSquare, data[i]);
        }

        for (int i = 0; i < 27; i++) {
            pthread_join(threads[i], NULL);
        }

        int valid = 1;
        for (int i = 0; i < 27; i++) {
            if (results[i] == 0) {
                valid = 0;
                break;
            }
        }
    /* printing to the terminal */
    if (valid) { printf("SOLUTION: YES\n"); }
    else { printf("SOLUTION: NO\n"); }

    /* freeing the memory */
    for (int i = 0; i < 27; i++) { free(data[i]); }

    }

    return 0;
}