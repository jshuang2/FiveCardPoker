# Five Card Poker

## Description:
Five Card Poker game implemented in C. The user is able to play in the terminal against an intelligent AI that makes decisions according to a custom hand-evaluation algorithm that we developed.

Rules of Five Card Poker can be found here: https://www.wikihow.com/Play-Five-Card-Draw

## Features:
- Betting
- Exchange cards with the deck
- Deck shuffle
- Hand sorting
- AI opponent
- Hand evaluation/scoring algorithm

## Technologies Used:
- C
- MakeFile

## Challenges:

One of our biggest challenges was the implementation of the hand-grading algorithm. We wanted the AI opponent to make intelligent decisions when deciding if they should exchange cards, so we integrated various variables into the algorithm such as pot odds, equity, and expected value.

Another challenge we faced was ensuring that all game components worked together seamlessly. We encountered multiple bugs that were sometimes difficult to track down.


## How to Use:

If the program is not already compiled, execute the Makefile by entering 'make' into the command line. If you have a Windows machine, you may have to install Makefile before using it.

If the program is compiled, enter ./poker_game into the terminal to begin the game.

## Conclusion and Future Considerations:

We learned a lot about how to create a complex program in C. We learned how to organize and include various file types in our project. We also learned how to utilize a robust compilation library (Makefile) to allow for seamless program execution.

In the future, we hope to give the user the ability to play against multiple, potentially more intelligent, opponents as is the case in a real-life Five Card Poker match. 
