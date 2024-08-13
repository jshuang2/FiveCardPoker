
#include "game_controller.h"
#include <stdio.h>

void initialize_game(GameController* gameController);
void play_betting_round(GameController* gameController);
void play_exchange_cards(GameController* GameController, Player* player);
void play_showdown(GameController* gameController);
void determine_winner(GameController* gameController);