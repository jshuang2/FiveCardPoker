#ifndef PLAYER_H
#define PLAYER_H

#include "hand.h"
#include <stdbool.h>

typedef struct Player {
    Hand* hand;
    int numChips;
    bool isHuman;
    bool called;
} Player;

void print_player_hand(Player* player);
int computer_make_bet(Player* player, int currentBet, int currentPot);
void computer_exchange_cards(Player* player, Deck* deck);

#endif
