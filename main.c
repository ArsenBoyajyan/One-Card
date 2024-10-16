#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include "./play.c"

int main(int argc, char *argv[]){ 
    
    int players_number = 4, initial_cards = 5, rounds = 1, decks = 12;
    char *filename = "onecard.log";
    int option_index = 0, opt = 0; 
    struct option long_options[] = { 
    {"help", no_argument, NULL, 'h'}, 
    {"log", optional_argument, NULL, 'l'}, 
    {"player-number=", required_argument, NULL, 'n'}, 
    {"initial-cards=", required_argument, NULL, 'c'}, 
    {"rounds=", required_argument, NULL, 'r'},
    {"decks=", required_argument, NULL, 'd'},  
    {NULL, 0, NULL, 0} 
    }; 
    while((opt = getopt_long(argc, argv, "hl:n:c:r:d:",long_options, &option_index)) != -1) { 
    switch (opt) { 
        case 'h': 
            printf("-h|--help print this help message\n" 
                "--log filename write the logs in filename (default: onecard.log)\n" 
                "-n n|--player-number=n n players, n must be larger than 2 (default: 4)\n" 
                "-c c|--initial-cards=c deal c cards per player, c must be at least 2 (default: 5)\n" 
                "-r r|--rounds=r play r rounds, r must be at least 1 (default: 1)\n" 
                "-d d|--decks=d use d decks 52 cards each, d must be at least 2 (default: 2)\n" );
                return 0;
            break; 
        case 'l': 
            filename = optarg; 
            printf("write the logs in: %s (default: onecard.log)\n", optarg); 
            break; 
        case 'n': 
            if(optarg!=NULL) {
                players_number = atoi(optarg); 
            }
            printf("number of players: %d\n", players_number); 
            break; 
        case 'c': 
            initial_cards = atoi(optarg); 
            printf("number of the cards: %d\n", initial_cards);  
            break; 
        case 'd': 
            decks = atoi(optarg); 
            printf("the number of the decks: %d\n", decks); 
            break; 
        case 'r': 
            rounds = atoi(optarg); 
            printf("the number of the rounds: %d\n", rounds); 
            break; 
        default: 
            printf("Wrong argument.\n"); 
            return 0;
        } 
    } 

    FILE *fpo = fopen(filename, "a");
    welcome(fpo);

    play(players_number, initial_cards, rounds, decks, fpo); 
    fclose(fpo);
    return 0;
}