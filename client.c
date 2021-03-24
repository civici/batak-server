#include "client.h"

void client_send(struct client* c, char* msg)
{
    send(c->port, msg, strlen(msg), 0);
}

char* client_recv(struct client* c, char* msg)
{

    char* buffer = calloc(1024, 1);
    recv(c->port, buffer, 1024, 0);
    return buffer;
}


/** OPCODE 1 payload structure
 *  first  byte -> opcode
 *  second byte -> deck count
 *  odd    byte -> card koz
 *  even   byte -> card val
 */
void client_send_deck(struct client* c, struct Deck* d)
{
    unsigned char* payload_deck = calloc(1024, 1);
    
    payload_deck[0] = 1;
    payload_deck[1] = d->count;

    unsigned int byteiterator = 2;

    for (int i = 0; i < d->count; i++)
    {
        struct Card* currentCard = d->data[i];
        payload_deck[byteiterator] = currentCard->koz;
        byteiterator++;
        payload_deck[byteiterator] = currentCard->val;
        byteiterator++;
    }
    send(c->port, payload_deck, byteiterator, 0);
    free(payload_deck);
}

/** OPCODE 2
 *  first byte -> opcode
 *  second byte -> strlen(msg) ! without null-termination !
 *  rest -> msg data ! without null-termination !
*/

void client_send_string(struct client* c, char* msg)
{

    char* payload_message = calloc(1024, 1);

    payload_message[0] = 2;
    payload_message[1] = strlen(msg);

    unsigned int byteiterator = 2;
    for (int i = 0; i < strlen(msg); i++)
    {
        payload_message[byteiterator] = msg[i];
        byteiterator++;
    }

    send(c->port, payload_message, byteiterator, 0);
    
}