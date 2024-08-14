#include "hand.h"
#include <stdio.h>
#include <stdlib.h>

// define struct map for finding pairs
struct Map {
    int key;
    int count;
};

// helper function prototypes
int isFlush(Hand *hand);
int isStraight(Hand * hand);
int findPairs(Hand * hand);

// sorts hand by rank using bubble sort
void sort_hand(Hand *hand) {
    for (int i = 0; i < 5; ++i) {
        for (int j = 0; i < 4; ++j) {
            if (hand -> cards[j] > hand -> cards[j + 1]) {
                struct Card* temp = hand -> cards[j];
                hand -> cards[j] = hand -> cards[j + 1];
                hand -> cards[j + 1] = temp;
            }
        }
    }
}


// returns an integer value representing the hands strength
int evaluate_hand(Hand *hand) {

    sort_hand(hand);

    if (isFlush(hand) && isStraight(hand))
        return 9;
    else {
        int pair_value = findPairs(hand);
        if (pair_value >= 7) 
            return pair_value;
        else if (isFlush(hand))
            return 6;
        else if (isStraight(hand))
            return 5;
        return pair_value;
    }
}

// helper function for evaluate hand
// determines if a hand is a flush
int isFlush(Hand *hand) {
    int matches = 1;
    for(int i = 1; i < 5; ++i) {
        if (hand -> cards[0] -> suit == hand -> cards[i] -> suit) {
            ++matches;
        }
    }
    return matches == 5 ? 1 : 0;
}

// helper method for evaluate hand
// determines if a hand is a straight
int isStraight(Hand * hand) {
    int consecutive = 1;
    for(int i = 0; i < 4; ++i) {
        if ((hand -> cards[i] -> rank) - (hand -> cards[i + 1] -> rank  == 1)) {
            ++consecutive; 
        }
    }
    return consecutive == 5 ? 1 : 0;
}

// helper method for evaluate hand
// determines if a hand contains: a single pair, two pair, full house, or 4 of a kind
int findPairs(Hand * hand) {
    struct Map rank_map[13] = {0};

    // add ranks to map w/ count of how many of each rank in hand
    for (int i = 0; i < 5; ++i) {
        int rank = hand -> cards[i] -> rank;
        rank_map[rank - 1].key = rank;
        (rank_map[rank - 1].count)++;
    }

    // vars for tracking how many pairs, three of a kind, four of a kind
    int num_pairs = 0;
    int num_sets = 0;
    int num_quads = 0;

    // add count to pairs, sets & quads as applicable
    for (int i = 0; i < 14; ++i){
        if (rank_map[i].count == 2) {
            num_pairs++;
        } else if (rank_map[i].count == 3) {
            num_sets++;
        } else if (rank_map[i].count == 4) {
            num_quads++;
        }
    }
    
    if (num_quads == 1) 
        return 8;
    if (num_sets == 1 && num_pairs == 1) 
        return 7;
    if (num_sets == 1)
        return 4;
    if (num_pairs == 2)
        return 3;
    if (num_pairs == 1) 
        return 2;
    return 1; // if no matches found return 1
}


// exchanges a specified number of player cards at specified indexes in the hand
void exchange_cards(Hand *hand, Deck *deck, int indexes[], int num_cards) {
    for (int i = 0; i < num_cards; ++i) {
        hand -> cards[indexes[i]] = deal_card(deck);
    }
}