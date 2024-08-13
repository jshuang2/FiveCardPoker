#include "deck.h"
#include <stdlib.h>
#include <time.h>
#include <stdio.h>

static const int MAX_DECK_SIZE = 52;
static const int NUM_SUITS = 4;
static const int NUM_RANKS = 13;
static const char SUITS[] = {'C', 'D', 'H', 'S'};
static const int RANKS[] = {2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14};


Deck create_deck() {
    Deck new_deck;
    int card_index = 0;

    for (int i = 0; i < NUM_SUITS; i++) {
        for (int j = 0; j < NUM_RANKS; j++) {
            new_deck.cards[card_index].suit = SUITS[i];
            new_deck.cards[card_index].rank = RANKS[j];
            card_index++;
        }
    }
    new_deck.currentSize = MAX_DECK_SIZE;
    shuffle(&new_deck);
    return new_deck;
}

void shuffle(Deck *deck) {
    srand(time(NULL));
    for (int i = 0; i < deck->currentSize; i++) {
        int j = i + rand() % (deck->currentSize - i);
        Card temp = deck->cards[i];
        deck->cards[i] = deck->cards[j];
        deck->cards[j] = temp;
    }
}

Card deal_card(Deck *deck) {
    Card dealt_card = deck->cards[0];

    for (int i = 1; i < deck->currentSize; i++) {
        deck->cards[i - 1] = deck->cards[i];
    }
    deck->currentSize--;

    return dealt_card;
}

void print_deck(Deck *deck) {
    for (int i = 0; i < deck->currentSize; i++) {
        print_card(&deck->cards[i]);
    }
}
