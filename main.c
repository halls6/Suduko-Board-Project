/*
 * Names           : Sofia Hall & Nick Viola
 * File Name       : main.c
 * Description     : LATER
 * 
*/

#include <stdio.h>
#include <stdlib.h>

int board[9][9]; /* store sudoku numbers */

/* function to read in board from input.txt */
void readBoard() {
    FILE *fptr = fopen("input.txt", "r");

    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            fscanf(fptr, "%d", &board[i][j]);
        }
    }
    fclose(fptr);
}

/* function to print out board */
void printBoard() {

}

/* main function */
int main() {
    readBoard();
    printf("%d\n", board[0][0]);
    return 0;
}