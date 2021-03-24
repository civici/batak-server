#include "Deck.h"

struct Deck* deck_new()
{
    struct Deck* deck = malloc(sizeof(struct Deck));
    deck->count = 0;
    return deck;
}

void deck_push(struct Deck* deck, struct Card* card)
{

    struct Card** tempdata = malloc(sizeof(struct Card*) * (deck->count + 1));
    
    for (int i = 0; i < deck->count; i++)
    {
        tempdata[i] = deck->data[i];
    }

    tempdata[deck->count] = card;
    if (deck->count > 0)
        free(deck->data);
    deck->data = tempdata;
    deck->count++;
}

struct Card* deck_remove(struct Deck* deck, unsigned int index)
{

    if (deck->count == 1)
    {
        struct Card* c = deck->data[0];
        free(deck->data);
        deck->data = NULL;
        deck->count--;
        return c;
    }

    struct Card** tempdata = malloc(sizeof(struct Card*) * (deck->count - 1));
    int counter = 0;

    for (int i = 0; i < deck->count; i++)
    {
        if (i == index)
            continue;
        tempdata[counter] = deck->data[i];
        counter++;
    }

    struct Card* c = deck->data[index];
    free(deck->data);
    deck->data = tempdata;
    deck->count--;
    return c;

}
