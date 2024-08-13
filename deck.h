#ifndef DECK_H
#define DECK_H

#include "card.h"

typedef struct Deck {
    Card cards[52];
    int currentSize;
} Deck;

Deck create_deck();
void shuffle(Deck* deck);
Card deal_card(Deck* deck);
void print_deck(Deck* deck);

#endif