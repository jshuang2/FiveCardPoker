
#include "game_controller.h"
#include "player.h"
#include "deck.h"
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

const int startingChips = 100;
const int startingPot = 0;
Player* humanPlayer;
Player* computerPlayer;
GameController* controller;


Player* create_player(bool isHuman) {
    Player* newPlayer = (Player*)malloc(sizeof(Player));
    Hand* newHand = (Hand*)malloc(sizeof(Hand));

    newPlayer->hand = newHand;
    newPlayer->isHuman = isHuman;
    newPlayer->numChips = startingChips;
    newPlayer->called = false;

    return newPlayer;
}


GameController* create_controller() {
    GameController* newController = (GameController*)malloc(sizeof(GameController));

    newController->currentPot = startingPot;
    newController->lastBet = 0;
    newController->bettingRound = 1;
    newController->deck = create_deck();

    return newController;
}

void initialize_game() {
    humanPlayer = create_player(true);
    computerPlayer = create_player(false);

    controller = create_controller();
    controller->players[0] = humanPlayer;
    controller->players[1] = computerPlayer;

    controller->currentPlayer = humanPlayer;
    deal_starting_cards();
}

void deal_starting_cards() {

    for (int i = 0; i < 5; ++i) {
        humanPlayer->hand->cards[i] = deal_card(controller->deck);
        computerPlayer->hand->cards[i] = deal_card(controller->deck);
    }
    print_hand(humanPlayer -> hand);
    play_betting_round();
}

void play_betting_round() {
    bool roundOver = false;
    int currentBet = 0;

    // Reset the called flags at the beginning of the round
    humanPlayer->called = false;
    computerPlayer->called = false;

    while (!roundOver) {
        Player* currentPlayer = controller->currentPlayer;
        int action;

        if (currentPlayer->isHuman) {
            printf("It's your turn. You have %d chips.\n", currentPlayer->numChips);
            printf("What would you like to do? 1 is bet, 2 is call, 3 is fold.\n");
            scanf("%d", &action);

            switch (action) {
                case 1: {
                    int bet;
                    printf("How much would you like to bet? You have %d chips.\n", currentPlayer->numChips);
                    scanf("%d", &bet);

                    if (bet > currentPlayer->numChips || bet <= currentBet || bet > computerPlayer -> numChips) {
                        printf("Invalid bet. You must bet more than the current bet of %d and within your chips.\n", currentBet);
                    } else {
                        currentPlayer->numChips -= bet;
                        currentBet = bet;
                        controller->currentPot += bet;
                        controller->lastBet = currentBet;

                        // Reset called status because a new bet was made
                        humanPlayer->called = false;
                        computerPlayer->called = false;
                    }
                    break;
                } 
                case 2: {  // TODO: could be problematic, may need to implement logic to limit bet size to other player's number of chips
                    if (currentPlayer->numChips >= currentBet) {
                        currentPlayer->numChips -= currentBet;
                        controller->currentPot += currentBet;
                        humanPlayer->called = true;
                    } else {
                        printf("You don't have enough chips to call.\n");   
                        continue;
                    }
                    break;
                }
                case 3: {
                    printf("You fold.\n");
                    distribute_chips(controller->players[1]);  // The other player wins the pot
                    currentBet = 0;
                    roundOver = true;
                    return;  // End the round early since one player folded
                }
                default:
                    printf("Invalid action. Try again.\n");
                    continue;
            }
        } else {  //TODO: implement computer player methods
            // Computer player's turn

            
            printf("Computer player's turn.\n");
            // adjust game as necessary given computers bet
            if (computerPlayer -> numChips >= currentBet) {
                int computer_bet = computer_make_bet(currentPlayer, currentBet, controller->currentPot);
                if (computer_bet > humanPlayer -> numChips) {
                    computer_bet = currentBet;
                }
                if (computer_bet == -1) {  // if computer folds print message, distribute chips, end round
                    printf("Computer player folded\n");
                    distribute_chips(controller -> players[0]);
                    currentBet = 0;
                    roundOver = true;
                    return;
                } else if (computer_bet < -1) {
                    computer_bet = currentBet;
                }
                else if (computer_bet == controller -> lastBet) {  // if computer calls
                    (computerPlayer -> numChips) -= computer_bet;
                    (controller -> currentPot) += computer_bet;
                    computerPlayer -> called = true;
                    printf("Computer player called\n");
                    roundOver = true;
                }
                else {  // if computer raises
                    printf("the computer player raised by %d chips\n", computer_bet - (controller -> lastBet));
                    (computerPlayer -> numChips) -= computer_bet;
                    currentBet = computer_bet;
                    (controller -> currentPot) += computer_bet;
                    controller -> lastBet = computer_bet;
                    // Reset called status because a new bet was made
                    humanPlayer->called = false;
                    computerPlayer->called = false;
                }
            }

            
            /*
            printf("Computer player's turn.\n");
            if (currentPlayer->numChips >= currentBet) {
                printf("Computer calls.\n");
                currentPlayer->numChips -= currentBet;
                controller->currentPot += currentBet;
                computerPlayer->called = true;
            } else {
                printf("Computer folds.\n");
                distribute_chips(controller->players[0]);  // The human player wins the pot
                roundOver = true;
                currentBet = 0;
                return;  // End the round early since one player folded
            }
            */
        }

        // Check if both players have called
        if (humanPlayer->called && computerPlayer->called) {
            roundOver = true;
            printf("Both players have called. The betting round is over.\n");
        }

        // Switch turns
        controller->currentPlayer = (controller->currentPlayer == controller->players[0]) ? controller->players[1] : controller->players[0];
    }

    printf("Betting round over. The pot is now %d chips.\n", controller->currentPot);

    if (controller->bettingRound == 2) {
        play_showdown();
    }
    else {  //TODO: add logic to incorporate computer exchanging cards in this sectino or play_exchange_cards
        controller->bettingRound = 2;
        print_hand(humanPlayer -> hand);
        play_exchange_cards();
        print_hand(humanPlayer -> hand);
        computer_exchange_cards(computerPlayer, controller->deck);
        play_betting_round();
    }
}


void distribute_chips(Player* player) {
    player->numChips += controller->currentPot;

    if (player->isHuman) {
        printf("You have won the hand. %d chips have been added to your stack. You have %d chips.\n", controller->currentPot, humanPlayer->numChips);
    }
    else {
        printf("The AI has won the hand. %d chips have been added to their stack. You have %d chips.\n", controller->currentPot, humanPlayer->numChips);
        printf("AI hand: ");
        print_hand(computerPlayer -> hand);
    }

    controller->currentPot = 0;
}

void play_exchange_cards() {

    int indexes[5];
    int numberOfCards = 0;
    bool flag = true;
    char* yesOrNo = NULL;
    bool exchanged = false;
    yesOrNo = malloc(4 * sizeof(char));

    while (flag) {

        printf("Would you like to exchange a card? Enter 'yes' or 'no'.\n");
        scanf("%s", yesOrNo);

        if (strcmp(yesOrNo, "yes") != 0) {
            flag = false;
            break;
        }

        printf("Enter the card number from left to right [1-5] or type '0' if you're done.\n");

        int index = 0;
        scanf("%d", &index);

        if (index == 0) break;
        if (index >= 1 && index <= 5) {
            indexes[numberOfCards++] = --index;
            exchanged = true;
        }
    }

    if (exchanged) {
        exchange_cards(humanPlayer->hand, controller->deck, indexes, numberOfCards);
    }

    free(yesOrNo);
};

void play_showdown() {

    int humanHandEval = evaluate_hand(humanPlayer->hand);
    int computerHandEval = evaluate_hand(computerPlayer->hand);

    if (humanHandEval > computerHandEval) {
        distribute_chips(humanPlayer);
    }
    else if (computerHandEval > humanHandEval) {
        distribute_chips(computerPlayer);
    }
    else {  //TODO: this is not be ideal logic, but probably works for now
        if (humanPlayer->hand->cards[0]->rank > computerPlayer->hand->cards[0]->rank) {
            distribute_chips(humanPlayer);
        }
        else {
            distribute_chips(computerPlayer);
        }
    }

    if (humanPlayer->numChips == 0) {
        end_game(computerPlayer);
    }
    else if (computerPlayer->numChips == 0) {
        end_game(humanPlayer);
    }
    else {
        controller -> deck = create_deck();
        deal_starting_cards();
    }

}

void free_player(Player* player) {
    if (player != NULL) {
        free(player -> hand);
        free(player);
    }
}

void free_game_controller(GameController* controller) {
    if (controller != NULL) {
        free(controller);
    }
}

void end_game(Player* winner) {
    if (winner->isHuman) {
        printf("You have won the game! Your total chip count is: %d\n", winner->numChips);
    } else {
        printf("The AI has won the game! Their total chip count is: %d\n", winner->numChips);
    }

    free_player(humanPlayer);
    free_player(computerPlayer);
    free_game_controller(controller);
}
