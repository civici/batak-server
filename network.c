#include "network.h"


/** THREAD FUNC DEPRECATED */
void* listener(void* c)
{
    struct client* currentClient = (struct client*) c;
    while (1)
    {
        char* buf = calloc(1024, 1);
        int bytes = recv(currentClient->port, buf, 1024, 0); 
        if (bytes < 1)
        {
            printf("%d exited\n", currentClient->port);
            return NULL;
        }
        printf("packet received %d bytes\n", bytes);
        puts(buf);
        free(buf);
    }
}

int network_openserver()
{
    int serverfd = socket(AF_INET, SOCK_STREAM, 0);
    
    
    int flag = 1;
    setsockopt(serverfd, SOL_SOCKET, SO_REUSEADDR, &flag, sizeof(int));

    setsockopt(serverfd, SOL_SOCKET, SO_REUSEPORT, &flag, sizeof(int));

    assert(serverfd != -1);

    printf("socket opened at %d\n", serverfd);

    struct sockaddr_in address;
    int addrlen = sizeof(address);

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(54322);

    int err = bind(serverfd, (struct sockaddr*)&address, sizeof(address));
    if (err != 0)
    {
        printf("errno %d\n", errno);
        exit(0);
    }

    puts("server bind");

    assert(listen(serverfd, 4) == 0);
    puts("server listening");

    int clientcount = 0;

    struct client* lastConnectedClient = NULL;

    while (clientcount < 2)
    {
        struct client* currentClient = malloc(clientsize);
        currentClient->port = accept(serverfd, (struct sockaddr*)&address, (socklen_t*)&addrlen);
        currentClient->name = client_get_name(currentClient);
        client_wait_for_players(currentClient);
        for (int i = 0; i < 2; i++)
        {
            if (clients[i] == NULL)
            {
                clients[i] = currentClient;
                break;
            }
        }
        clientcount++;
    }
    return serverfd;
}