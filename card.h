#ifndef CARD_H
#define CARD_H

typedef struct Card {
    char suit;
    int rank;
} Card;

void print_card(Card* card);

#endif