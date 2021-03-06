#include "client.h"

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
    int bytes = send(c->port, payload_deck, byteiterator, 0);
    printf("client sent deck bytes %d\n", bytes);
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

    int bytes = send(c->port, payload_message, byteiterator, 0);
    printf("client sent string bytes %d\n", bytes);
    
}

/** outgoing paylaod
 *  opcode -> 3
 *  datacount -> 0
 *  
 *  incoming payload
 *  opcode -> 4
 *  datacount -> 1
 *  rest -> deck index of card
 */
int client_get_card_index(struct client* c)
{
    char outgoing[2] = {3, 0};
    send(c->port, outgoing, 2, 0);

    char* buf = calloc(1024, 1);

    recv(c->port, buf, 1024, 0);

    puts("recv buf card index");

    printf("0 == %d 1 == %d 2 == %d\n", buf[0], buf[1], buf[2]);

    if (buf[0] == 4 && buf[1] == 1)
    {
        puts("here");
        int index = buf[2];
        free(buf);
        printf("index recv at %d\n", index);
        return index;
    }

    free(buf);
    return -1;

}

/** OPCODE 5
 *  first byte -> opcode
 *  second byte -> dataCount -> 1
 *  rest -> 2 bytes first one c->koz, second one c->val 
*/
void client_send_card(struct client* c, struct Card* card)
{
    char* payload = calloc(1024, 1);
    *payload = 5;
    *++payload = 1;
    *++payload = card->koz;
    *++payload = card->val;

    send(c->port, payload - 3, 4, 0);

}


/**outgoing payload
 * OPCODE 6
 * first byte -> opcode
 * second byte -> 0
 * 
 * incoming payload
 * OPCODE 7
 * first byte -> opcode
 * second byte -> strlen
 * rest -> string bytes 
 */
char* client_get_name(struct client* c)
{
    char outgoing[2] = {6, 0};
    send(c->port, outgoing, 2, 0);

    char* buf = calloc(1024, 1);
    recv(c->port, buf, 1024, 0);

    int opcode = *buf;
    int strlen = *++buf;

    char* name = calloc(strlen + 1, 1);
    memcpy(name, ++buf, strlen);

    free(buf - 2);
    return name;

}
/** OPCODE 8
 *  first byte -> opcode
 *  second byte -> 0
 */

void client_wait_for_players(struct client* c)
{
    char outgoing[2] = {8, 0};
    send(c->port, outgoing, 2, 0);
}

// OPCODE 9 
void client_wait_for_players_end(struct client* c)
{
    char outgoing[2] = {9, 0};
    send(c->port, outgoing, 2, 0);
}