
#include "player.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "game_controller.h"
#include "hand.h"

// prints all cards in a player's hand
void print_player_hand(Player* player){
    for (int i = 0; i < 5; ++i){
        print_card(player -> hand -> cards[i]);
    }
}

// TODO, may need to be moved to game controller or play game
// TODO, may need to check if computer player has more chips than 2x current bet
// handles bet making for computer player
int computer_make_bet(Player* player, int currentBet, GameController* gc) {
    
    int hand_strength = evaluate_hand(player -> hand); // get hand strength

    double pot_odds = (double) currentBet / (gc-> currentPot + currentBet); // get pot odds

    double win_probability = (double) hand_strength / 9;      // get simple win probaility
    double loss_probability = 1 - win_probability;            // get simple loss probability

    // get expected value = (win probability * winnings) - (loss probability * losses aka bet amount)
    double expected_value = (win_probability * gc -> currentPot) - (loss_probability * currentBet);

    //incorporate some level of randomness
    srand(time(0));
    int random_number = (rand() % 3) + 1;  // generate a random number either 1, 2 or 3

    // incorporate expevted value & pot odds to make intelligent computer bet
    // if expected value is negative & pot odds are high fold or call (emphasize fold)
    if (expected_value < 0 && pot_odds >= .67) {
        switch(random_number) {
            case 1: 
                return -1;
                break;
            case 2:
                return currentBet;
                break;
            case 3:
                return -1;
                break;
            default:
                return currentBet;
                break;
        }
    }
    // if expected value is negative & pot odds are moderate use random number to decide b/w call, fold (empahsize call)
    else if (expected_value < 0 && pot_odds > .33 && pot_odds < .67) {
        switch (random_number) {
            case 1:
                return currentBet;
                break;
            case 2: 
                return currentBet;
                break;
            case 3:
                return -1;
                break;
            default:
                return currentBet;
                break;
        }
    // if expected value is negative & pot odds are low use random number to decide b/w raise, call, fold (equal probability)
    } else if (expected_value < 0 && pot_odds <= .33) {
        switch (random_number) {
            case 1:
                return currentBet * 2;
                break;
            case 2:
                return currentBet;
                break;
            case 3:
                return -1;
                break;
            default:
                return currentBet;
                break;
        }
    // if expected value is positive use random number to decide how much to bet (emphasize raise)
    } else if (expected_value >= 0) {
        switch (random_number) {
            case 1: 
                return currentBet * 2;
                break;
            case 2: 
                return currentBet * 2;
                break;
            case 3:
                return currentBet;
                break;
            default:
                return currentBet;
                break;
        }
    } else return currentBet;
}

// exchanges cards for the computer player using hand strength
void  computer_exchange_cards(Player* player, Deck* deck) {

    int hand_strength = evaluate_hand(player -> hand);
    int exchange_indexes[5];
    int num_to_exchange = 0;

    if (hand_strength >= 5) {
        // if straight or better don't exchange cards
        return;
    } else {
        if (hand_strength == 4) {
        // exchange 2 cards not in set
            num_to_exchange = 2;
            for (int i = 0; i < 3; i++) {
                if (player -> hand -> cards[i] -> rank == player -> hand -> cards[i + 1] -> rank
                    && player -> hand -> cards[i + 1] -> rank == player -> hand -> cards[i + 2] -> rank) {
                        if (i == 0) { // if i = 0, first three cards in set, exchange indexes = 3 & 4
                            exchange_indexes[0] = 3;
                            exchange_indexes[1] = 4;
                        } else if (i == 1) { // if i = 1, middle three cards in set, exchange indexes = 0 & 4
                            exchange_indexes[0] = 0;
                            exchange_indexes[1] = 4;
                        } else if (i == 2) { // if i = 2, last three cards in set, exchange indexes = 0 & 1
                            exchange_indexes[0] = 0;
                            exchange_indexes[1] = 1;
                        }
                    break; // end loop after finding set
                }
            }
        } else if (hand_strength == 3) {
        // exchange 1 card not in either pair
            num_to_exchange = 1;
            for (int i = 1; i < 4; i++) { 
                if (!(player -> hand -> cards[i] -> rank == player -> hand -> cards[i - 1] -> rank)
                    && !(player -> hand -> cards[i] -> rank == player -> hand -> cards[i + 1] -> rank)) {
                        // if card @ index i does not match card to either side it's not in either pair
                        exchange_indexes[0] = i;
                    }
            }
        } else if (hand_strength == 2) {
        // exchange 3 cards not in pair
            num_to_exchange = 3; 
            for (int i = 0; i < 4; i++) {
                if (player -> hand -> cards[i] -> rank == player -> hand -> cards[i + 1] -> rank) {
                    if (i == 0) { // if i = 0, pair @ 0 & 1
                        exchange_indexes[0] = 2;
                        exchange_indexes[1] = 3;
                        exchange_indexes[2] = 4;
                    } else if (i == 1) { // if i = 1, pair @ 1 & 2
                        exchange_indexes[0] = 0;
                        exchange_indexes[1] = 3;
                        exchange_indexes[2] = 4;
                    } else if (i == 2) { // if i = 2, pair @ 2 & 3
                        exchange_indexes[0] = 0;
                        exchange_indexes[1] = 1;
                        exchange_indexes[2] = 4;
                    } else if (i == 3) { // if i = 3, pair @ 3 & 4
                        exchange_indexes[0] = 0;
                        exchange_indexes[1] = 1;
                        exchange_indexes[2] = 2;
                    }
                    break;
                }
            }
        } else {
            // exchange all cards except highest card
            num_to_exchange = 4;
            for (int i = 1; i < 5; i++) {
                exchange_indexes[i - 1] = i;
            }
        }
        exchange_cards(player -> hand, deck, exchange_indexes, num_to_exchange);
    }   
}