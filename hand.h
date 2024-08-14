#ifndef HAND_H
#define HAND_H

#include "card.h"
#include "deck.h"

typedef struct Hand {
    Card* cards[5];
} Hand;

void sort_hand(Hand* hand);
void exchange_cards(Hand* hand, Deck* deck, int indexes[], int num_cards);
int evaluate_hand(Hand* hand);
void print_hand(Hand* hand);

#endif