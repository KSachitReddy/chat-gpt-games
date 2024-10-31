#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8080

int main() {
    int server_fd, new_socket;
    struct sockaddr_in address;
    int addrlen = sizeof(address);
    char buffer[1024] = {0};
    int target_number = rand() % 100 + 1; // Random number between 1 and 100
    int guess;

    // Create socket file descriptor
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("Socket failed");
        exit(EXIT_FAILURE);
    }

    // Configure server address
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    // Bind the socket to the port
    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("Bind failed");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    // Listen for connections
    if (listen(server_fd, 3) < 0) {
        perror("Listen failed");
        close(server_fd);
        exit(EXIT_FAILURE);
    }
    printf("Server is waiting for a player to connect...\n");

    // Accept a client connection
    if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t *)&addrlen)) < 0) {
        perror("Accept failed");
        close(server_fd);
        exit(EXIT_FAILURE);
    }
    printf("Player connected! Starting the game...\n");

    // Game loop
    while (1) {
        read(new_socket, buffer, 1024); // Read guess from client
        guess = atoi(buffer);
        printf("Player guessed: %d\n", guess);

        if (guess > target_number) {
            strcpy(buffer, "Too High!");
        } else if (guess < target_number) {
            strcpy(buffer, "Too Low!");
        } else {
            strcpy(buffer, "Correct! You win!");
            send(new_socket, buffer, strlen(buffer), 0);
            break;
        }
        send(new_socket, buffer, strlen(buffer), 0); // Send response
    }

    close(new_socket);
    close(server_fd);
    return 0;
}
