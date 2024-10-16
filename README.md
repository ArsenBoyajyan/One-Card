# ONE CARD

## Author
Arsen Boyajyan 522370990025
## created at
30.11.2022

# Game Rules

**Objective:** Be the first player to discard all your cards.

**Setup:**

*   Use 1-2 decks of standard playing cards (Jokers removed).  The number of decks and cards per player are adjustable.
*   Each player receives a starting hand of cards (usually 5).
*   An extra card is dealt to each player to determine the starting player (lowest rank goes first). This card is then discarded.


**Gameplay:**

1.  The first card from the stock pile is placed face up to begin the game. Play proceeds counter-clockwise.
2.  On your turn, play a card that matches the rank *or* suit of the previous card played.
3.  If you cannot play a card, draw from the stock pile.
4.  If the stock pile is empty, shuffle the discard pile to create a new stock pile.
5.  Played cards are added to the discard pile.


**Special Cards:**

*   **2:** Forces the next player to draw two cards.
*   **3:** Forces the next player to draw three cards.
*   **7:** Cancels the effect of a preceding 2 or 3.
*   **Queen:** Reverses the direction of play.
*   **Jack:** Skips the next player's turn.
*   Effects of special cards are cumulative.  A Queen or Jack of the same suit as the previous card can redirect an attack.


**Scoring:**

*   A round ends when a player discards all their cards.
*   Players who have cards remaining at the end of the round receive a penalty equal to the number of cards left in their hand.
*   The player who won the round starts the next round.


**Winning:**

*   The game continues for a set number of rounds (adjustable).
*   After the final round, the player with the highest penalty score is the winner. Ties are possible.

# How to Run

1.  **Compile:**  Navigate to the directory containing your source code (`main.c`, `play.c`, etc.) and compile using a C compiler (like GCC):

    ```bash
    gcc main.c play.c -o onecard -Wall -Wextra -Werror -pedantic -std=c11
    ```

2.  **Run:** Execute the compiled program (`onecard`) from your terminal:

    *   `./onecard -h` or `./onecard --help`: Displays the help message showing available options.
    *   `./onecard -n 3 -c 7 -r 2 -d 1 -l mygame.log`: Starts a game with 3 players, 7 initial cards each, 2 rounds, 1 deck, and logs to `mygame.log`.  (Adjust options as needed)



# working principals
I keep one deck of card, each card holds status, which is info about which player it belongs or is it in discard/stock pile
drawing and dropping card changes the status of card

whenever a player draws a card, the last card that belongs to stock pile changes the status.
Also, the deck keeps a variable indicating which is the last card that belongs to stock pile.

If the stock pile is over, I shuffle all the deck and then sort bringing cards from discard pile into front. 
Then, I change thir status.