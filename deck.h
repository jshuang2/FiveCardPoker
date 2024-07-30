#ifndef DECK_H
#define DECK_H

#include "card.h"

typedef struct Deck {
    Card cards[52];
    int currentSize;
} Deck;

void setupDeck(Deck* deck);
void shuffleDeck(Deck* deck);

#endif