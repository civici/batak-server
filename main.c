#include "network.h"
#include <unistd.h>

#include "game/Card.h"
#include "game/Deck.h"

struct Deck* initdeck()
{
    struct Deck* d = deck_new();
    for (int i = 0; i < 6; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            struct Card* c = card_new(i, j);
            deck_push(d, c);
        }
    }
    return d;
}

int main()
{
    struct Deck* d = initdeck();
    int serverfd = network_openserver();

    //client_send_deck(clients[0], d);
    //client_send_deck(clients[1], d);

    client_send_string(clients[0], "you are client 0");
    client_send_string(clients[1], "you are client 1");

    shutdown(clients[0]->port, SHUT_RDWR);
    shutdown(clients[1]->port, SHUT_RDWR);
    close(clients[0]->port);
    close(clients[1]->port);

    shutdown(serverfd, SHUT_RDWR);
    close(serverfd);
    puts("done");
    return 0;
}