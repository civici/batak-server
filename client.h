#pragma once

#include <pthread.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sys/socket.h>
#include "game/Deck.h"

struct client{

    int port;
    unsigned char index;
    char* name;

    struct client* nextClient;

};

void client_send(struct client* c, char* msg);

char* client_recv(struct client* c, char* msg);

void client_send_deck(struct client* c, struct Deck* d);

void client_send_string(struct client* c, char* msg);

int client_get_card_index(struct client* c);

void client_send_card(struct client* c, struct Card* card);

char* client_get_name(struct client* c);

void client_wait_for_players(struct client* c);