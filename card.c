#include "card.h"
#include <stdio.h>

void print_card(Card *card) {
    char* rank;
    switch (card->rank) {
        case 2:  rank = "2"; break;
        case 3:  rank = "3"; break;
        case 4:  rank = "4"; break;
        case 5:  rank = "5"; break;
        case 6:  rank = "6"; break;
        case 7:  rank = "7"; break;
        case 8:  rank = "8"; break;
        case 9:  rank = "9"; break;
        case 10: rank = "10"; break;
        case 11: rank = "J"; break;
        case 12: rank = "Q"; break;
        case 13: rank = "K"; break;
        case 14: rank = "A"; break;
        default: rank = "?"; break;  // Error case
    }
    printf("Suit: %c, Rank: %s\n", card->suit, rank);
}
