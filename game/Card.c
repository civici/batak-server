#include "Card.h"

struct Card* card_new(int val, int koz)
{
    struct Card* c = malloc(sizeof(struct Card*));
    c->koz = koz;
    c->val = val;
    return c;
}