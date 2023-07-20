
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>

#define PORT 12345

int main() {
    int sockfd, n;
    struct sockaddr_in server_addr;
    char buffer[1024];

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        perror("Error in socket");
        exit(1);
    }
    printf("Client socket created.\n");

    memset(&server_addr, '\0', sizeof(server_addr));

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    server_addr.sin_addr.s_addr = inet_addr("192.168.0.16");

    if (connect(sockfd, (struct sockaddr*)&server_addr, sizeof(server_addr)) == -1) {
        perror("Error in connect");
        exit(1);
    }
    printf("Connected to server.\n");
    recv(sockfd, buffer, sizeof(buffer), 0);
    int random_number = atoi(buffer);

    printf("Random number received from server: %d\n", random_number);

    close(sockfd);
    printf("Client closed.\n");

    return 0;
}
