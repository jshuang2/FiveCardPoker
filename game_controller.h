#ifndef GAME_CONTROLLER_H
#define GAME_CONTROLLER_H

#include "player.h"
#include "deck.h"

typedef struct GameController {
    Player* players[2];
    Deck* deck;
    int currentPot;
    int lastBet;
    Player* currentTurn;
} GameController;

void initialize_game(GameController* gameController);
void play_betting_round(GameController* gameController);
void play_exchange_cards(GameController* GameController, Player* player);
void play_showdown(GameController* gameController);
void determine_winner(GameController* gameController);
// void reset_game(GameController* gameController);

#endif