## ONE CARD

# Author
Arsen Boyajyan 522370990025
# created at
30.11.2022

# working principals
I keep one deck of card, each card holds status, which is info about which player it belongs or is it in discard/stock pile
drawing and dropping card changes the status of card

whenever a player draws a card, the last card that belongs to stock pile changes the status.
Also, the deck keeps a variable indicating which is the last card that belongs to stock pile.

If the stock pile is over, I shuffle all the deck and then sort bringing cards from discard pile into front. 
Then, I change thir status.