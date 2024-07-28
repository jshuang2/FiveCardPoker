#ifndef HAND_H
#define HAND_H

#include "card.h"
#include "deck.h"

typedef struct Hand {
    Card hand[5];
} Hand;

void sortHand(Hand* hand);
void exchangeCards(Hand* hand, Card cardsToExchange[], Deck* deck);
void evaluateHand(Hand* hand);

#endif