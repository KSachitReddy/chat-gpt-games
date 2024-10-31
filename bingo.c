#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 5

void generateBoard(int board[SIZE][SIZE]);
void displayBoard(int board[SIZE][SIZE]);
int markNumber(int board[SIZE][SIZE], int num);
int checkWin(int board[SIZE][SIZE]);

int main() {
    int board[SIZE][SIZE];
    int num;

    srand(time(0));
    generateBoard(board);

    printf("Welcome to Bingo!\n");
    while (1) {
        displayBoard(board);

        printf("Enter a number to mark (1-25): ");
        scanf("%d", &num);

        if (num < 1 || num > 25) {
            printf("Invalid number! Try again.\n");
            continue;
        }

        if (markNumber(board, num)) {
            printf("Marked %d.\n", num);
        } else {
            printf("Number not found or already marked.\n");
        }

        if (checkWin(board)) {
            printf("Bingo! You won!\n");
            displayBoard(board);
            break;
        }
    }

    return 0;
}

void generateBoard(int board[SIZE][SIZE]) {
    int used[SIZE * SIZE + 1] = {0};
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            int num;
            do {
                num = rand() % 25 + 1;
            } while (used[num]);
            board[i][j] = num;
            used[num] = 1;
        }
    }
}

void displayBoard(int board[SIZE][SIZE]) {
    printf("\nBingo Board:\n");
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (board[i][j] == -1) {
                printf(" X ");
            } else {
                printf("%2d ", board[i][j]);
            }
        }
        printf("\n");
    }
    printf("\n");
}

int markNumber(int board[SIZE][SIZE], int num) {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (board[i][j] == num) {
                board[i][j] = -1; // Mark number as "X"
                return 1;
            }
        }
    }
    return 0;
}

int checkWin(int board[SIZE][SIZE]) {
    for (int i = 0; i < SIZE; i++) {
        int rowWin = 1, colWin = 1;
        for (int j = 0; j < SIZE; j++) {
            if (board[i][j] != -1) rowWin = 0;
            if (board[j][i] != -1) colWin = 0;
        }
        if (rowWin || colWin) return 1;
    }

    int diag1 = 1, diag2 = 1;
    for (int i = 0; i < SIZE; i++) {
        if (board[i][i] != -1) diag1 = 0;
        if (board[i][SIZE - i - 1] != -1) diag2 = 0;
    }
    return diag1 || diag2;
}
