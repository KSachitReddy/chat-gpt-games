#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define FINISH_LINE 50

void displayProgress(int player, int position);

int main() {
    int player1Pos = 0, player2Pos = 0;
    int diceRoll;
    char enterKey;
    
    srand(time(0)); // Seed the random number generator

    printf("Welcome to the Simple Text-Based Racing Game!\n");
    printf("First player to reach position %d wins!\n\n", FINISH_LINE);

    while (player1Pos < FINISH_LINE && player2Pos < FINISH_LINE) {
        // Player 1's turn
        printf("Player 1, press Enter to roll the dice...");
        getchar(); // Wait for Enter key
        diceRoll = (rand() % 6) + 1; // Generate random number from 1 to 6
        player1Pos += diceRoll;
        printf("Player 1 rolled a %d and moved to position %d\n", diceRoll, player1Pos);
        displayProgress(1, player1Pos);

        // Check if Player 1 has won
        if (player1Pos >= FINISH_LINE) {
            printf("Congratulations! Player 1 wins!\n");
            break;
        }

        // Player 2's turn
        printf("Player 2, press Enter to roll the dice...");
        getchar(); // Wait for Enter key
        diceRoll = (rand() % 6) + 1;
        player2Pos += diceRoll;
        printf("Player 2 rolled a %d and moved to position %d\n", diceRoll, player2Pos);
        displayProgress(2, player2Pos);

        // Check if Player 2 has won
        if (player2Pos >= FINISH_LINE) {
            printf("Congratulations! Player 2 wins!\n");
            break;
        }
    }

    return 0;
}

void displayProgress(int player, int position) {
    printf("Player %d's progress: ", player);
    for (int i = 0; i < FINISH_LINE; i += 5) {
        if (i < position) {
            printf("=");
        } else {
            printf("-");
        }
    }
    printf(">\n\n");
}
