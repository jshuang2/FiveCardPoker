#ifndef PLAYER_H
#define PLAYER_H

#include "hand.h"
#include <stdbool.h>

typedef struct Player {
    Hand* hand;
    int numChips;
    bool isHuman;
} Player;

void print_player_hand(Player* player);
int make_bet(Player* player, int currentBet);

#endif
