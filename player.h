#ifndef PLAYER_H
#define PLAYER_H

#include "hand.h"
#include <stdbool.h>
#include "game_controller.h"

typedef struct Player {
    Hand* hand;
    int numChips;
    bool isHuman;
} Player;

void print_player_hand(Player* player);
int computer_make_bet(Player* player, int currentBet, GameController* gc);
void computer_exchange_cards(Player* player);

#endif
