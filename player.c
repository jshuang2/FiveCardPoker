
#include "player.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "game_controller.h"

// prints all cards in a player's hand
void print_player_hand(Player* player){
    for (int i = 0; i < 5; ++i){
        print_card(player -> hand -> cards[i]);
    }
}

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
                return -1;
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
        }
    } else return currentBet;
}