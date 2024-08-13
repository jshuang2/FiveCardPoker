
#include "player.h"
#include <stdio.h>

void initialize_player(Player* player, char* name, int numChips, bool isHuman);
void print_player_hand(Player* player);
int make_bet(Player* player, int currentBet);