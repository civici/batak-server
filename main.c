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

    client_wait_for_players_end(clients[0]);
    client_wait_for_players_end(clients[1]);

    while (d->count > 0)
    {
        client_send_deck(clients[0], d);
        int index = client_get_card_index(clients[0]);
        if (index == 254)
            break;
        free(deck_remove(d, index));
        client_send_deck(clients[1], d);
        index = client_get_card_index(clients[1]);
        if (index == 254)
            break;
        free(deck_remove(d, index));
    }

    shutdown(clients[0]->port, SHUT_RDWR);
    shutdown(clients[1]->port, SHUT_RDWR);
    close(clients[0]->port);
    close(clients[1]->port);

    shutdown(serverfd, 2);
    close(serverfd);
    puts("done");
    return 0;
}