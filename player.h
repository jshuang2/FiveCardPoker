#ifndef PLAYER_H
#define PLAYER_H

#include "hand.h"
#include <stdbool.h>

typedef struct Player {
    char name[50];
    Hand hand;
    int numChips;
    bool isHuman;
} Player;

void initialize_player(Player* player, char* name, int numChips, bool isHuman);
void print_player_hand(Player* player);
int make_bet(Player* player, int currentBet);

#endif
