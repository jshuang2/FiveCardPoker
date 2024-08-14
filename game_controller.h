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

void distribute_chips(Player* player);
void end_game(Player* winner);
GameController* create_controller();
void deal_starting_cards();
Player* create_player(bool isHuman);
void initialize_game();
void play_betting_round();
void play_exchange_cards();
void play_showdown();
void free_player(Player* player);
void free_game_controller(GameController* controller);
void end_game(Player* winner);
// void determine_winner(GameController* gameController);
// void reset_game(GameController* gameController);

#endif