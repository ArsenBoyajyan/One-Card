#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "./structs.c"

deck createDeck(int d);
deck shuffle(deck cards);
deck giveCard(int player, deck cards); // same as drawCard, witout printing
deck drawCard(int player, deck cards, FILE *fpo);
deck init(int players_number, int deck_number, int initial_cards, FILE *fpo); // initializes cards
deck reInit(deck cards, int players_number, int , FILE *fpo);
deck sort(deck cards, FILE *fpo); // brings cards of discard pile in front of the array, changes their status into stock pile. uses bubble sort
card dropCard(card droppingCard, FILE *fpo);
card discardCard(card droppingCard); // same as dropCard, without printing
void PrintCard(card card_sample, FILE *fpo);
void printCardsByPlayer(int player, deck cards, FILE *fpo);
void decideWinner(players players_arr, FILE *fpo); 
void welcome(FILE *fpo);
int compareCards(card a, card b);
int doMatch(card card1, card card2);
int findFirstPlayer(players players_arr);
int decideNext(int current, int total, int direction);
players createPlayers(int n);
game gameRound(deck Cards, players playersArr, int starter, FILE *fpo); // this is the main part of the game
points checkForWinner(deck cards, players players_arr); // if any player's cards are over

deck createDeck(int d){
    deck res;
    res.number_of_decks = d;
    res.deck = calloc((unsigned int)d*52,sizeof(deck));
    if(res.deck==NULL){ 
        free(res.deck); 
        return res; 
    }
    res.lastInDeck = 52*d;
    int deck_pointer = 0;
    for (int k = 0; k < d; k++){
        for (int i = 0; i < 4; i++){
            for (int j = 0; j < (13); j++, deck_pointer++) {
                res.deck[deck_pointer].suit = i+1;
                res.deck[deck_pointer].rank = j+2;
                res.deck[deck_pointer].status = 0;
            }
        }
    }
    return res;
}

deck shuffle(deck cards){
    int n = 52*cards.number_of_decks;
    for (int i = 0; i < n - 1; i++) 
    {
        int j = i + rand() / (RAND_MAX / (n - i) + 1);
        card t = cards.deck[j];
        cards.deck[j] = cards.deck[i];
        cards.deck[i] = t;
    }
    return cards;
}

deck giveCard(int player, deck cards){
    cards.deck[cards.lastInDeck].status = player;
    cards.lastInDeck--;
    return cards;
}

deck drawCard(int player, deck cards, FILE *fpo){
    printf("Player %d plays: drawed ", player);
    fprintf(fpo, "Player %d plays: drawed ", player);
    PrintCard(cards.deck[cards.lastInDeck], fpo);
    printf("\n");
    fprintf(fpo, "\n");
    cards.deck[cards.lastInDeck].status = player;
    cards.lastInDeck--;
    printCardsByPlayer(player, cards, fpo);
    return cards;
}

card dropCard(card droppingCard, FILE *fpo){
    printf("Player %d plays: dropped ", droppingCard.status);
    fprintf(fpo, "Player %d plays: dropped ", droppingCard.status);
    PrintCard(droppingCard, fpo);
    printf("\n");
    fprintf(fpo, "\n");
    droppingCard.status = -1;
    return droppingCard;
}

card discardCard(card droppingCard){
    droppingCard.status = -1;
    return droppingCard;
}

void PrintCard(card card_sample, FILE *fpo){
    switch(card_sample.suit){
        case 1:
            printf("Spades ");
            fprintf(fpo, "Spades ");
            break;
        case 2:
            printf("Hearts ");
            fprintf(fpo, "Hearts ");
            break;
        case 3:
            printf("Diamonds ");
            fprintf(fpo, "Diamonds ");
            break;
        case 4:
            printf("Clubs ");
            fprintf(fpo, "Clubs ");
            break;
    }
    switch(card_sample.rank){
        case 11:
            printf("Jack ");
            fprintf(fpo, "Jack ");
            break;
        case 12:
            printf("Queen ");
            fprintf(fpo, "Queen ");
            break;
        case 13:
            printf("King ");
            fprintf(fpo, "King ");
            break;
        case 14:
            printf("Ace ");
            fprintf(fpo, "Ace ");
            break;
        default:
            printf("%d ", card_sample.rank);
            fprintf(fpo, "%d ", card_sample.rank);
            break;
    }
}

void printCardsByPlayer(int player, deck cards, FILE *fpo){
    int n = cards.number_of_decks;
    printf("Player %d cards: ", player);
    fprintf(fpo, "Player %d cards: ", player);
    for (int i = 0; i < 52*n; i++){
        if (cards.deck[i].status == player){
            
            PrintCard(cards.deck[i], fpo);
            printf(", ");
            fprintf(fpo, ", ");
        }
    }   
    printf("\n");
    fprintf(fpo, "\n");
}

void welcome(FILE *fpo){
    printf("\n########################");
    printf("\n#                      #");
    printf("\n# Welcome to One Card! #");
    printf("\n#                      #");
    printf("\n########################\n\n");
    fprintf(fpo, "\n\n########\nNEW GAME\n########\n\n");
}

int compareCards(card a, card b){
    if (a.suit > b.suit) {
        return 1;
    }
    if ((a.suit == b.suit) && (a.rank > b.rank)){ 
        return 1;
    }
    return 0;
}

deck sort(deck cards, FILE *fpo){
    printf("\n\n**********\nshuffling discard pile\n");
    fprintf(fpo, "\n\n**********\nshuffling discard pile\n");
    cards = shuffle(cards);
    int n = cards.number_of_decks;
    int rank = 0, suit = 0, status = 0;
    for (int c = 0; c < (n*52); c++){
        for (int i = 0; i < (52*n) - 1; i++){
            if (cards.deck[i + 1].status == -1){
                rank = cards.deck[i].rank;
                suit = cards.deck[i].suit;
                status = cards.deck[i].status;
                cards.deck[i].rank = cards.deck[i + 1].rank;
                cards.deck[i].suit = cards.deck[i + 1].suit;
                cards.deck[i].status = cards.deck[i + 1].status;
                cards.deck[i + 1].rank = rank;
                cards.deck[i + 1].suit = suit;
                cards.deck[i + 1].status = status;
            }
        }
    }

    for (int i = 0; i <  52*n; i++){
        if (cards.deck[i].status == -1){
            cards.lastInDeck = i;
            cards.deck[i].status = 0;
        } else break;
    }

    printf("%d cards in pile\n**********\n\n", cards.lastInDeck);
    fprintf(fpo, "%d cards in pile\n**********\n\n", cards.lastInDeck);

    return cards;
}

int doMatch(card card1, card card2){
    int res = 0;
    if (card1.suit == card2.suit){
        res = 1;
    }
    if (card1.rank == card2.rank){
        res = 1;
    }
    return res;
}

deck init(int players_number, int deck_number, int initial_cards, FILE *fpo){
    deck res = createDeck(deck_number);
    printf("\nShuffling cards...\n");
    fprintf(fpo, "\nShuffling cards...\n");
    res = shuffle(res);
    printf(" \n");
    fprintf(fpo, " \n");

    printf("Dealing cards...\n");
    fprintf(fpo, "Dealing cards...\n");

    for (int i = 0; i < players_number; i ++){
        for (int j = 0; j < initial_cards; j++){
            res = giveCard( i + 1, res);
        }
    }

    printf("\nDealing results:\n");
    fprintf(fpo, "\nDealing results:\n");
    for (int i = 0; i < players_number; i++){
        printCardsByPlayer(i + 1, res, fpo);
    }

    return res;
}

deck reInit(deck cards, int players_number, int initial_cards, FILE *fpo){
    deck res = cards;
    res.lastInDeck = res.number_of_decks*52;
    for (int i = 0; i < res.number_of_decks*52; i ++){
        cards.deck[i].status = 0;
    }

    printf("\nShuffling cards...\n");
    fprintf(fpo, "\nShuffling cards...\n");
    res = shuffle(res);
    printf(" \n");
    fprintf(fpo, " \n");
    
    printf("Dealing cards...\n");
    fprintf(fpo, "Dealing cards...\n");
    for (int i = 0; i < players_number; i ++){
        for (int j = 0; j < initial_cards; j++){
            res = giveCard( i + 1, res);
        }
    }
    printf("\nDealing results:\n");
    fprintf(fpo, "\nDealing results:\n");
    for (int i = 0; i < players_number; i++){
        printCardsByPlayer(i + 1, res, fpo);
    }

    printf("\n");
    fprintf(fpo, "\n");

    return res;
}

void decideWinner(players players_arr, FILE *fpo) {
    int min_index = 1;
    int min_score = players_arr.players[0].score;
    printf("\n\nTotal points are:\n");
    fprintf(fpo, "\n\nTotal points are:\n");
    for (int i = 0; i < players_arr.players_number; i++) {
        printf("Player %d: %d\n", i + 1, -players_arr.players[i].score);
        fprintf(fpo, "Player %d: %d\n", i + 1, -players_arr.players[i].score);
    }

    for (int i = 1; i < players_arr.players_number; i++) {
        if (players_arr.players[i].score <= min_score){
            min_score = players_arr.players[i].score;
            min_index = i + 1;
        }
    }

    printf("\n\n*****PLAYER %d won!*****\n\n", min_index);
    fprintf(fpo, "\n\n*****PLAYER %d won!*****\n\n", min_index);
}

int findFirstPlayer(players players_arr) {
    card min;
    int index_of_min = 0;
    min.rank = players_arr.players[0].decidingCard.rank;
    min.suit = players_arr.players[0].decidingCard.suit;
    min.status = 0;

    for (int i = 0; i < players_arr.players_number; i ++){
        if (compareCards(min, players_arr.players[i].decidingCard) == 1){
            index_of_min = i;
            min.rank = players_arr.players[i].decidingCard.rank;
            min.suit = players_arr.players[i].decidingCard.suit;
        }
    }

    return index_of_min + 1;
}

game gameRound(deck Cards, players playersArr, int starter, FILE *fpo){
    game res;
    res.cards = Cards;
    res.players_arr = playersArr;
    card prev_card; prev_card.rank = -1; prev_card.suit = -1; prev_card.status = 0;
    int i = starter, direction = 1, current_winner = 0, drawing_cards = 0, attack_status = 0;
    points winningStatus;

    for (int j = 0; j <= Cards.number_of_decks*52; j++){ //first player's
        if (res.cards.deck[j].status == i){
            res.cards.deck[j] = dropCard(res.cards.deck[j], fpo);
            printCardsByPlayer(i, res.cards, fpo);
            prev_card.suit = res.cards.deck[j].suit;
            prev_card.rank = res.cards.deck[j].rank;
            if (prev_card.rank == 12){
                direction *= -1;
            }
            if (prev_card.rank == 11){
                i = decideNext(i, res.players_arr.players_number, direction);
            }
            if (prev_card.rank == 2 || prev_card.rank == 3){
                drawing_cards = prev_card.rank;
            }
            break;
        }
    }

    i = decideNext(i, res.players_arr.players_number, direction);

    while (1 == 1) { //each iteration is one player's step
        if (res.cards.lastInDeck < 0) { // stock pile is over
            res.cards = sort(res.cards, fpo);
            if (res.cards.lastInDeck == 0) break;
        }
        winningStatus = checkForWinner(res.cards, res.players_arr);
        current_winner = winningStatus.winner;
        res.players_arr = winningStatus.players_arr;
        if (current_winner != 0){
            res.winner = current_winner;
            break;
        }

        if (drawing_cards > 0){ // attacked
            attack_status = 1;
            for (int j = 0; j < Cards.number_of_decks*52; j++){
                if (res.cards.deck[j].suit == prev_card.suit && res.cards.deck[j].rank == 7 && res.cards.deck[j].status == i){
                    drawing_cards = 0; // canceled attack
                    res.cards.deck[j] = dropCard(res.cards.deck[j], fpo);
                    printCardsByPlayer(i, res.cards, fpo);
                    prev_card.suit = res.cards.deck[j].suit;
                    prev_card.rank = res.cards.deck[j].rank;
                    i = decideNext(i, res.players_arr.players_number, direction);
                    attack_status = 0;
                    break;
                }
                if (res.cards.deck[j].rank == prev_card.rank && res.cards.deck[j].status == i){
                    drawing_cards += prev_card.rank; // added attack
                    res.cards.deck[j] = dropCard(res.cards.deck[j], fpo);
                    printCardsByPlayer(i, res.cards, fpo);
                    prev_card.suit = res.cards.deck[j].suit;
                    prev_card.rank = res.cards.deck[j].rank;
                    i = decideNext(i, res.players_arr.players_number, direction);
                    attack_status = 0;
                    break;
                }
            }
            if (attack_status == 1){ // no deffence of re-attack
                for (int j = 0; j < drawing_cards; j++){
                    res.cards = drawCard(i, res.cards, fpo);
                }
                drawing_cards = 0;
                i = decideNext(i, res.players_arr.players_number, direction);
            }
        } else {    
            for (int j = 0; j <= Cards.number_of_decks*52; j++){
                if (j == Cards.number_of_decks*52){ //none of cards matched
                    res.cards = drawCard(i, res.cards, fpo);
                    if (doMatch(res.cards.deck[res.cards.lastInDeck + 1], prev_card) == 1){ //drawed card matched
                        res.cards.deck[res.cards.lastInDeck + 1] = dropCard(res.cards.deck[res.cards.lastInDeck + 1], fpo);
                        printCardsByPlayer(i, res.cards, fpo);
                        prev_card.suit = res.cards.deck[res.cards.lastInDeck + 1].suit;
                        prev_card.rank = res.cards.deck[res.cards.lastInDeck + 1].rank;
                        if (prev_card.rank == 12){ // Queen
                            direction *= -1;
                        }
                        if (prev_card.rank == 11){ // Jack
                            i = decideNext(i, res.players_arr.players_number, direction);
                        }
                        if (prev_card.rank == 2 || prev_card.rank == 3){
                            drawing_cards = prev_card.rank;
                        }
                        i = decideNext(i, res.players_arr.players_number, direction);
                        i = decideNext(i, res.players_arr.players_number, direction);
                        break;
                    }
                    i = decideNext(i, res.players_arr.players_number, direction);
                    break;
                }
                if (res.cards.deck[j].status == i){
                    if (doMatch(res.cards.deck[j], prev_card) == 1){
                        res.cards.deck[j] = dropCard(res.cards.deck[j], fpo);
                        printCardsByPlayer(i, res.cards, fpo);
                        i = decideNext(i, res.players_arr.players_number, direction);
                        prev_card.suit = res.cards.deck[j].suit;
                        prev_card.rank = res.cards.deck[j].rank;
                        if (prev_card.rank == 12){ // Queen
                            direction *= -1;
                        }
                        if (prev_card.rank == 11){ // Jack
                            i = decideNext(i, res.players_arr.players_number, direction);
                        }
                        if (prev_card.rank == 2 || prev_card.rank == 3){
                            drawing_cards = prev_card.rank;
                        }
                        break;
                    }
                }
            }
        }
    }

    return res;
} 

players createPlayers(int n) {
    players res;
    res.players_number = n;
    res.players = calloc((unsigned int)n,sizeof(player));
    if(res.players==NULL){ 
        free(res.players); 
        return res; 
    }
    
    for (int i = 0; i < n; i++){
        res.players[i].score = 0;
    }
    
    return res;
}

points checkForWinner(deck cards, players player_arr) {
    points res;
    res.winner = 0;
    int cards_count[100];
    for (int i = 1; i <= player_arr.players_number; i++){
        cards_count[i] = 0;
    }
    for (int i = 0; i < cards.number_of_decks*52; i++){
        if (cards.deck[i].status > 0)
        cards_count[cards.deck[i].status] ++;
    }
    for (int i = 1; i <= player_arr.players_number; i++){
        if (cards_count[i] == 0){
            res.winner = i;
            for (int j = 1; j <= player_arr.players_number; j++){
                player_arr.players[j - 1].score += cards_count[j];
            }
            break;
        }
    }

    res.players_arr = player_arr;

    return res;
 }

int decideNext(int current, int total, int direction){
    // -1 direction means backwards
    int res = current + direction;
    if (res > total){
        res = 1;
    }
    if (res < 1){
        res = total;
    }
    return res;
}