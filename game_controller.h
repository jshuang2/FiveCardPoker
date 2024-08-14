#ifndef GAME_CONTROLLER_H
#define GAME_CONTROLLER_H

#include "player.h"
#include "deck.h"

typedef struct GameController {
    Player* players[2];
    Deck* deck;
    int currentPot;
    int lastBet;
    int bettingRound;
    Player* currentPlayer;
    Player* nextPlayer;
} GameController;

void initialize_game(GameController* gameController);
void play_betting_round();
void play_exchange_cards();
void play_showdown();
// void determine_winner(GameController* gameController);
// void reset_game(GameController* gameController);

#endif