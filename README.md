# Project 2
# Project 2: Multithreaded Sudoku Validator
This repository is to track the work for the second project of Operating Systems. 

## Team Members
- Sofia Hall (halls6)
- Nick Viola (violan3)

## Project Description
The project below uses two different methods to find if a Sudoku puzzle is a solution or not. It reads in an input file and prints it to the terminal. Then, depending on the method, rows, columns, and subgrids are checked. Lastly, it times how long it takes to find if there is a solution based on the number of threads and outputs the answer and the time it took to the terminal. 

## Project Completion Split
- Sofia   : README.md, main.c, Makefile, input.txt, essay.pdf
- Nick    : README.md, main.c, report.pdf, discussion.pdf, essay.pdf

## How to Compile
1. gcc -c main.c
2. gcc -o main main.c -lpthread
- OR: "make" and it'll compile and run both modes at once. 


## How to Run
1. ./main 1 or 2, depending on which method you'd like to use.
- OR: "make" and it'll compile and run both modes at once.
- Reminder: Method 1: 11 threads, Method 2: 27 threads

## Files
- main.c            - main source code
- Makefile          - compiler
- input.txt         - suduko input
- report.pdf        - shows code and results
- discussion.pdf    - github log and communication
- essay.pdf         - AI use essay

