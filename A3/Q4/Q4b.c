#include <stdio.h>
#include <stdbool.h>
#include <windows.h>

#define N 8

// Function to print the final solution
void printSolution(int board[N][N]) {
    for (int row = 0; row < N; row++) {
        for (int col = 0; col < N; col++) {
            if (board[row][col] == 1) {
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 2);
                printf("Q ");
            } else {
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
                printf(". ");
            }
        }
        printf("\n");
    }
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
}

// Function to check if it is safe to place the queen in a specific row and column
bool isSafe(int board[N][N], int row, int col) {
    // Check the row on the left side
    for (int i = 0; i < col; i++) {
        if (board[row][i]) return false;
    }

    // Check upper diagonal on the left side
    for (int i = row, j = col; i >= 0 && j >= 0; i--, j--) {
        if (board[i][j]) return false;
    }

    // Check lower diagonal on the left side
    for (int i = row, j = col; j >= 0 && i < N; i++, j--) {
        if (board[i][j]) return false;
    }

    return true;
}

// Recursive utility function to solve the Eight Queens problem
bool solveNQueensUtil(int board[N][N], int col) {
    // Base case: If all queens are placed, return true
    if (col >= N) return true;

    for (int row = 0; row < N; row++) {
        if (isSafe(board, row, col)) {
            board[row][col] = 1; // Place the queen

            // Recur to place the rest of the queens
            if (solveNQueensUtil(board, col + 1)) return true;

            board[row][col] = 0; // If placing the queen doesn't lead to a solution, backtrack
        }
    }

    return false; // If a queen can't be placed in any row in this column, return false
}

// Main function to solve the Eight Queens problem
bool solveNQueens() {
    int board[N][N] = {0}; // Initialize the chessboard

    if (solveNQueensUtil(board, 0) == false) {
        printf("Solution does not exist\n");
        return false;
    }

    printSolution(board);
    return true;
}

int main() {
    if (solveNQueens()) {
        printf("Solution found!\n");
    }

    return 0;
}
