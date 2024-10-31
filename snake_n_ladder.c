#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define WINNING_POSITION 100

// Snakes and Ladders positions
int board[101];

void initializeBoard() {
    // Initialize board with no snakes or ladders
    for (int i = 0; i <= WINNING_POSITION; i++) {
        board[i] = i;
    }

    // Ladders
    board[3] = 22;
    board[5] = 8;
    board[11] = 26;
    board[20] = 29;
    board[17] = 4;  // Snake
    board[19] = 7;  // Snake
    board[21] = 9;  // Snake
    board[27] = 1;  // Snake

    // Snakes
    board[34] = 54;
    board[47] = 19;
    board[65] = 95;
    board[87] = 57;
    board[91] = 61;
    board[99] = 69;
}

int rollDice() {
    return (rand() % 6) + 1;
}

void displayPosition(int player, int position) {
    printf("Player %d is now at position %d\n", player, position);
}

int main() {
    int player1Pos = 1, player2Pos = 1;
    int diceRoll;
    srand(time(0));

    initializeBoard();
    printf("Welcome to the Snake and Ladder Game!\n");
    printf("First player to reach position %d wins!\n\n", WINNING_POSITION);

    while (player1Pos < WINNING_POSITION && player2Pos < WINNING_POSITION) {
        // Player 1's turn
        printf("Player 1, press Enter to roll the dice...");
        getchar();
        diceRoll = rollDice();
        player1Pos += diceRoll;
        if (player1Pos > WINNING_POSITION) player1Pos = WINNING_POSITION;
        player1Pos = board[player1Pos];
        displayPosition(1, player1Pos);

        if (player1Pos >= WINNING_POSITION) {
            printf("Congratulations! Player 1 wins!\n");
            break;
        }

        // Player 2's turn
        printf("Player 2, press Enter to roll the dice...");
        getchar();
        diceRoll = rollDice();
        player2Pos += diceRoll;
        if (player2Pos > WINNING_POSITION) player2Pos = WINNING_POSITION;
        player2Pos = board[player2Pos];
        displayPosition(2, player2Pos);

        if (player2Pos >= WINNING_POSITION) {
            printf("Congratulations! Player 2 wins!\n");
            break;
        }
    }

    return 0;
}
