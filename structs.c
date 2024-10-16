#include <stdio.h>

typedef struct _card {
    int suit; 
    int rank; 
    int status; //to any player, in discard(-1)/stock(0) pile
} card;

typedef struct _deck {
    card *deck; //array of all the cards
    int number_of_decks;
    int lastInDeck; //last card in stock pile
} deck;

typedef struct _player {
    int score;
    card decidingCard; //card which decides who will strt
} player;

typedef struct _players {
    int players_number;
    player *players; //array of players
} players;

// The following structs are used for returning values from one funtion to another
typedef struct _game{
    int winner;
    deck cards;
    players players_arr;
} game;


typedef struct _points{
    int winner;
    players players_arr;
} points;