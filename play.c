#include <stdio.h>
#include <stdlib.h>
#include "./methods.c"


int play(int player_number, int initial_cards, int rounds, int deck_number, FILE *fpo) {
    
    time_t t = 0;
    int first_player = 0;
    game this_game;
    srand((unsigned) time(&t));

    if (player_number * initial_cards > 52*deck_number){
        printf("error");
        fprintf(fpo, "error"); // cards are not enough
    }

    players players_arr = createPlayers(player_number);

    deck cards = init(player_number, deck_number, initial_cards, fpo);

    printf("\nDeciding playing order\n\n");
    fprintf(fpo, "\nDeciding playing order\n\n");

    for (int i = 0; i < player_number; i ++) { // dealing order deciding cards
        int last = cards.lastInDeck;
        cards = giveCard(i + 1, cards);
        printf("Player %d: ", i + 1);
        fprintf(fpo, "Player %d: ", i + 1);
        PrintCard(cards.deck[last], fpo);
        players_arr.players[i].decidingCard.rank = cards.deck[last].rank;
        players_arr.players[i].decidingCard.suit = cards.deck[last].suit;
        printf("\n");
        fprintf(fpo, "\n");
        cards.deck[last] = discardCard(cards.deck[last]);
    }

    first_player = findFirstPlayer(players_arr);
    printf("\nPlayer %d will start the game\n\n", first_player);
    fprintf(fpo, "\nPlayer %d will start the game\n\n", first_player);

    printf("********************\n---Starting round 1---\n\n");
    fprintf(fpo, "********************\n---Starting round 1---\n\n");

    this_game = gameRound(cards, players_arr, first_player, fpo);

    cards = this_game.cards; players_arr = this_game.players_arr; first_player = this_game.winner;


    printf("PLAYER %d WON THIS ROUND\n\n", first_player);
    fprintf(fpo, "PLAYER %d WON THIS ROUND\n\n", first_player);

    for (int i = 2; i <= rounds; i++){ // other rounds
        printf("********************\n---Starting round %d---\n", i);
        fprintf(fpo, "********************\n---Starting round %d---\n", i);

        cards = reInit(cards, player_number, initial_cards, fpo);

        this_game = gameRound(cards, players_arr, first_player, fpo);
        players_arr = this_game.players_arr; first_player = this_game.winner;
        printf("___Player %d won this round___\n\n", first_player);
        fprintf(fpo, "___Player %d won this round___\n\n", first_player);
    }

    decideWinner(players_arr, fpo);

    free(cards.deck);
    free(players_arr.players);

    return 0;
}
