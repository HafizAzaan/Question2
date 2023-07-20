
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <arpa/inet.h>

#define PORT 12345

int generate_random_number() {
    return rand() % 900 + 100; // Generates a random number between 100 and 999
}

int main() {
    srand(time(0)); // Seed the random number generator with current time

    int sockfd, new_sock, len;
    struct sockaddr_in server_addr, new_addr;
    char buffer[1024];

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        perror("Error in socket");
        exit(1);
    }
    printf("Server socket created.\n");

    memset(&server_addr, '\0', sizeof(server_addr));

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    server_addr.sin_addr.s_addr = INADDR_ANY;

    if (bind(sockfd, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        perror("Error in binding");
        exit(1);
    }
    printf("Binding success.\n");

    listen(sockfd, 10);

    printf("Server is listening...\n");

    len = sizeof(new_addr);

  new_sock = accept(sockfd, (struct sockaddr*)&new_addr, &len);

    int random_number = generate_random_number();

    sprintf(buffer, "%d", random_number);
    send(new_sock, buffer, strlen(buffer), 0);
    printf("Random number sent to the client: %d\n", random_number);

    close(new_sock);
    close(sockfd);
    printf("Server closed.\n");

    return 0;
}
