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
    struct client* nextClient;

    pthread_t listenerID;

};

void client_send(struct client* c, char* msg);

char* client_recv(struct client* c, char* msg);

void client_send_deck(struct client* c, struct Deck* d);

void client_send_string(struct client* c, char* msg);