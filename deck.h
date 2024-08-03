#ifndef DECK_H
#define DECK_H

#include "card.h"

typedef struct Deck {
    Card cards[52];
    int currentSize;
} Deck;

//TODO: do we want to pass a deck as argument or no argument for setupDeck?
    // see create_deck
void setupDeck(Deck* deck);
void shuffleDeck(Deck* deck);

#endif