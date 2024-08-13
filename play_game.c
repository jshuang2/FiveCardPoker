#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "deck.h"
#include "card.h"
#include "hand.h"

int main(void) {
    Deck* new_deck = create_deck();
    print_deck(&new_deck);  // Pass pointer to print_deck

    Card* dealt_card = deal_card(&new_deck);
    printf("\nDealt card:\n");
    print_card(&dealt_card);  // Corrected to pass pointer

    print_deck(&new_deck);
    return 0;
}



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


// TODO: add to .h file for player? or is player struct even necessary?
// struct player {
//     char name[MAX_LENGTH];
//     struct Hand hand;
//     int num_chips;
// };

/*
Potentially add a struct for game?
EX: 

struct game {
    struct player players[2];
    int betting_pot;
    FIELD TO TRACK GAME STATE?
};
*/