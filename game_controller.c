
#include "game_controller.h"
#include "player.c"
#include "deck.c"
#include <stdio.h>
#include <stdbool.h>

const int startingChips = 100;
const int startingPot = 0;
int previousBet = 0;
Player* humanPlayer;
Player* computerPlayer;
GameController* controller;


Player* create_player(bool isHuman) {
    Player* newPlayer;
    newPlayer->isHuman = isHuman;
    newPlayer->numChips = startingChips;

    return newPlayer;
}

GameController* create_controller() {
    GameController* newController;

    newController->currentPot = startingPot;
    newController->lastBet = previousBet;
    newController->deck = create_deck();

    return newController;
}

void initialize_game(GameController* gameController) {
    humanPlayer = create_player(true);
    computerPlayer = create_player(false);

    controller = create_controller();
    controller->players[0] = humanPlayer;
    controller->players[1] = computerPlayer;

    controller->currentTurn = humanPlayer;
    deal_starting_cards();
}

void deal_starting_cards() {

    for (int i = 0; i < 5; i++) {
        humanPlayer->hand->cards[i] = deal_card(controller->deck);
        computerPlayer->hand->cards[i] = deal_card(controller->deck);
    }

}

void play_betting_round(GameController* gameController) {

    // bool call = true;
    // Player currentPlayer = gameController.currentTurn;

    // while (call) {
    //     printf("How many chips would you like to bet? You currently have %d chips.", &currentPlayer.numChips);

    //     int bet;
    //     scanf("%d", &bet);

    //     if (bet)
    // }

    Player* currentPlayer = gameController->currentTurn;
    int action;

    printf("What would you like to do? 1 is bet, 2 is call, 3 is fold.\n");
    scanf("%d", &action);

    if (action == 1) {

        int bet;

        printf("How much would you like to bet? You have %d chips.\n", currentPlayer->numChips);
        scanf("%d", &bet);

        if (bet <= currentPlayer->numChips && bet > previousBet) {
            currentPlayer->numChips -= bet;
            previousBet = bet;
            controller->currentPot += bet;
        }
    }
    else if (action == 2) {
        if (currentPlayer->numChips <= previousBet) {
            controller->currentPot += previousBet;
        }
    }


}

void play_exchange_cards(GameController GameController, Player player);
void play_showdown(GameController gameController);
void determine_winner(GameController gameController);