#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <netdb.h>
#include <arpa/inet.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s hostname\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    const char *hostname = argv[1];

    struct addrinfo hints, *result, *rp;
    memset(&hints, 0, sizeof(struct addrinfo));
    hints.ai_family = AF_INET; // Utilisez AF_INET6 si vous voulez également IPv6
    hints.ai_socktype = SOCK_STREAM;

    if (getaddrinfo(hostname, NULL, &hints, &result) != 0) {
        fprintf(stderr, "Erreur lors de la résolution de l'adresse du serveur\n");
        exit(EXIT_FAILURE);
    }

    for (rp = result; rp != NULL; rp = rp->ai_next) {
        struct sockaddr_in *addr = (struct sockaddr_in *)rp->ai_addr;
        char ip[INET_ADDRSTRLEN];
        inet_ntop(AF_INET, &(addr->sin_addr), ip, INET_ADDRSTRLEN);
        printf("Adresse IP de %s: %s\n", hostname, ip);
    }

    freeaddrinfo(result);

    return 0;
}