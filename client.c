#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <netdb.h>
#include <sys/socket.h>
#include <unistd.h>
#include <arpa/inet.h>

int ifEnd(char *str)
{
    if (!strcmp(str, ":exit"))
    {
        printf("\nProgram Exited");
        return 0;
    }
    return 1;
}

int main()
{
    char *ip = "127.0.0.1";
    int port = 10000;
    int sock;
    struct sockaddr_in addr;
    socklen_t addr_size;
    char buffer[1024];
    int n;

    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0)
    {
        perror("[-]Socket error");
        exit(1);
    }
    printf("[+]TCP server socket created.\n");

    memset(&addr, '\0', sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_port = port;
    addr.sin_addr.s_addr = inet_addr(ip);
    connect(sock, (struct sockaddr *)&addr, sizeof(addr));
    printf("Connected to the server.\n");

    while (ifEnd(buffer))
    {
        bzero(buffer, 1024);
        scanf("%[^\n]%*c", buffer);
        printf("Client: %s\n", buffer);
        send(sock, buffer, strlen(buffer), 0);
        if (!ifEnd(buffer))
            break;
        bzero(buffer, 1024);
        recv(sock, buffer, sizeof(buffer), 0);
        printf("Server: %s\n", buffer);
    }

    close(sock);
    printf("Disconnected from the server.\n");
    return 0;
}