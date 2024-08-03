

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "deck.h"
#include "card.h"
#include "hand.h"

/*
TODO next steps: 
    - finalize deal_card & shuffle methods
    - implement more descriptive printing method
    - implement game logic
        - functions for: 
            - making bets/ prompting user input for bets/ adding chips after won hand
            - adding & removing cards from hand
            - ending hand after fold or showdown
    - implement hand grading system
        - helper function that orders hand by rank
        - HOW TO DEAL WITH LOW ACE FOR STRAIGHT?
    - implement computer player algorithm
        - calcualtions for pot odds, equity, expected value
*/ 

// define constants
const int MAX_LENGTH = 52;
const int HAND_SIZE = 5;
// TODO: change SUITS and RANKS to character arrays
const char SUITS[] = {'C', 'D', 'H', 'S'};
const int NUM_SUITS = 4;
const char RANKS[] = {'A', '2', '3', '4', '5', '6', '7', '8',
                       '9', 'T', 'J', 'Q', 'K'};
const int NUM_RANKS = 13;

// define structs
// TODO: add to .h file for player? or is player struct even necessary?
struct player {
    char name[MAX_LENGTH];
    struct Hand hand;
    int num_chips;
};

/*
Potentially add a struct for game?
EX: 

struct game {
    struct player players[2];
    int betting_pot;
    FIELD TO TRACK GAME STATE?
};

*/

//declare functions
struct Deck create_deck();
void print_deck(struct Deck deck);
void shuffle(struct Deck *deck);
struct Card deal_card(struct Deck *deck);
void print_card(struct Card card);


// main method
int main(void) {

    // not part of actual gameplay, just for debugging
    struct Deck new_deck = create_deck();
    print_deck(new_deck);
    struct Card delt_card = deal_card(&new_deck);
    printf("\ndelt card:\n");
    print_card(delt_card);
    print_deck(new_deck);
    return 0;
}

// create a new 52 card deck
struct Deck create_deck(){

    struct Deck new_deck;
    struct Card new_card;
    int card_index = 0;

    for (int i = 0; i < NUM_SUITS; i++) {
        for (int j = 0; j < NUM_RANKS; j++) {
            new_card.suit = SUITS[i];
            new_card.rank = RANKS[j];
            new_deck.cards[card_index] = new_card;
            card_index++;
        }
    }
    new_deck.currentSize = MAX_LENGTH;
    shuffle(&new_deck);
    return new_deck;
}

// print the deck
void print_deck(struct Deck deck) {
    for (int i = 0; i < MAX_LENGTH; i++) {
        printf("Suit: %c, Rank: %c\n", deck.cards[i].suit, deck.cards[i].rank);
    }
}

// print a single card
void print_card(struct Card card) {
    printf("Suit: %c, Rank: %c\n", card.suit, card.rank);
}

// helper method for create_deck, randomizes the order of cards in the deck
void shuffle(struct Deck *deck) {
    srand(time(NULL));  // got this line from chat GPT, was getting a shuffled deck, but the
                        // same deck each time when using the shuffle method w/o this line
                        // chat gpt still says this algorythm does not result in equal probibility for 
                        // all permutations of the deck and advises use of the fischer-yates shuffle
    for (int i = 0; i < MAX_LENGTH; i++) {  // fischer-yates iterates through the deck in reverse order
        int j = rand() % MAX_LENGTH;        // and uses (i + 1) instead of max length
        struct Card temp = deck -> cards[i];
        deck -> cards[i] = deck -> cards[j];
        deck -> cards[j] = temp;
    }
}

// deal a card from the deck & adjust deck size
//**
//TODO: does this result in duplicate cards at the end of the deck?
// Also, should card be added to player hand directly in method instead of returned?
//**
struct Card deal_card(struct Deck *deck) {
    struct Card delt_card = deck -> cards[0];

    for(int i = 1; i < deck -> currentSize; i++) {
        deck -> cards[i - 1] = deck -> cards[i];
    }
    deck -> currentSize --;

    return delt_card;
}