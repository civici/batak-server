#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Card.h"

struct Deck{

    struct Card** data;
    int count;

};

struct Deck* deck_new();

struct Card* deck_remove(struct Deck* deck, unsigned int index);

void deck_push(struct Deck* deck, struct Card* card);