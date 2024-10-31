#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8080

int main() {
    int sock = 0;
    struct sockaddr_in serv_addr;
    char buffer[1024] = {0};
    int guess;

    // Create socket
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        printf("Socket creation error\n");
        return -1;
    }

    // Configure server address
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);

    // Convert IPv4 and IPv6 addresses from text to binary form
    if (inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) <= 0) {
        printf("Invalid address/ Address not supported\n");
        return -1;
    }

    // Connect to the server
    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        printf("Connection Failed\n");
        return -1;
    }
    printf("Connected to the game server!\n");

    // Game loop
    while (1) {
        printf("Enter your guess (1-100): ");
        scanf("%d", &guess);

        sprintf(buffer, "%d", guess);
        send(sock, buffer, strlen(buffer), 0); // Send guess to server
        read(sock, buffer, 1024); // Receive response from server

        printf("Server: %s\n", buffer);

        if (strcmp(buffer, "Correct! You win!") == 0) {
            break;
        }
    }

    close(sock);
    return 0;
}
