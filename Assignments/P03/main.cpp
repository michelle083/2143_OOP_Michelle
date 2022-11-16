/*************************************************************************
 *
 *  Author:           Michelle Orru
 *  Label:            P03
 *  Title:            Blackjack Program
 *  Course:           CMPS 2143
 *  Semester:         Fall 2022
 *
 *  Description:
 *        This is my program for the card Game of Blackjack.
 *
 *  Files:
 *       main.cpp        : driver program
 *       colors.h        : header file with colors defintion
 *       blackjack.hpp   : implementations
 *
 *************************************************************************/

#include "blackjack.hpp"
#include <cstdlib>
#include <iomanip>
#include <iostream>
#include <stdio.h>
#include <string>
#include <time.h>
#include <unistd.h>
#include <vector>

using namespace std;

// struct to create the player and assign those variables to it
struct Player {
    string name;
    int age;
    int money;
    int bet;
    // vector<Card> hand;
};

// display at the start of the game for player to choose
void gameMenu() {
    cout << "Please select an option below: " << endl;
    cout << "1) Display the rules" << endl;
    cout << "2) Start the game!" << endl;
    cout << "Selection : ";
}

// If player selects to see the rules then diplay this
void gameRules() {
    cout << "My Blackjack game rules: " << endl;
    cout << "   Your goal in blackjack is to beat the dealer hand without going over 21." << endl;
    cout << "   You will receive 2 cards at the beginning of each round, and you will add up the values of these cards." << endl;
    cout << "   Cards 2 - 10 have face value; 'J', 'Q', 'K' are worth 10; 'A' are either a 1 or an 11" << endl;
    cout << "   The dealer also draws two cards.The aim of the game is to have a higher hand than dealer without going over 21." << endl;
    cout << "   If you would like the dealer to deal you another card, you tell him HIT" << endl;
    cout << "   If you do not want to be dealt another card, you STAND." << endl;
    cout << "   BURST is when the sum of your hand is over 21." << endl;
    cout << "   The winner of the round is whoever has the highest hand without going bust." << endl;
    cout << endl << endl;
} // source for these rules : (https://www.blackjack.org/blackjack/how-to-play/)

// score of the card
int cardScore(vector<Card*> cards, int numOfCards) {
    int t = 0; // total

    for (int i = 0; i < numOfCards; i++) {
        numOfCards == 2;

        if (cards[i]->getRank() >= 10) {
            // add 10 to the total if it's 10, J, Q, K
            t += 10;
        }
        else {
            t += cards[i]->getRank() + 1;
        }
    }

    return t;
}

// function for the player's turn
void playerBet(Player& user) {
    int bet = 0;

    // repeat until they decide to bet within their balance
    do {
        cout << "" << user.name
            << " how much money would you like to bet? (Must be greater than $5 and less than $"
            << user.money << ")" << endl;
        cout << "$";
        cin >> bet;
        cout << endl;

    } while (!(bet >= 5 && bet <= user.money));

    // update their current balance subtracting the bet they just made
    user.money -= bet;
    user.bet = bet;
}

// function for main structure of the game
void game(Player& user, Player& dealer) {
    // dispay the bet and money of the user
    playerBet(user);
    system("clear");

    cout << "Player's money: $" << user.money << endl;
    cout << "Player's Bet: $" << user.bet << endl;

    // create player and dealer's hands
    srand(time(0));
    int playerHand = 2;
    int dealerHand = 2;

    // vector to hold the player and dealer's cards
    vector<Card*> playerCards;
    vector<Card*> dealerCards;

    // randomly create cards for dealer and player
    for (int i = 0; i < 2; i++) {
        playerCards.push_back(new Card(rand() % 52));
        dealerCards.push_back(new Card(rand() % 52));
    }

    cout << endl;
    cout << user.name << " card score: " << cardScore(playerCards, 2) << endl;

    // print the player's cards
    cout << "Player's cards: " << endl << endl;
    printCardVector(playerCards, 2);

    // print dealer's visible card
    cout << "Dealer's visible card: " << endl << endl;
    printSingleCard(dealerCards);

    int playerCount = 0;
    string playerSelection = "H";

    while (playerSelection == "H" && !(user.money < 10)) {
        cout << endl << "Enter H to Hit or S to Stand" << endl;
        cout << "Selection: ";
        cin >> playerSelection;

        // if player choose to hit then give new card
        if (playerSelection == "H" || playerSelection == "h") {
            cout << endl << "Player's new cards: " << endl;
            playerCards.erase(playerCards.begin()); // erases first card from vector
            playerCards.push_back(new Card(rand() % 52)); //create new card
            playerHand--;

            printCardVector(playerCards, playerHand); //print new set of cards
        }
        else if (playerSelection == "S" || playerSelection == "s") {
            playerCount = cardScore(playerCards, 2); // new count
        }
    }

    int playerTotalHand = cardScore(playerCards, playerHand);
    int dealerTotalHand = cardScore(dealerCards, dealerHand);

    // RESULTS
    
    //if the sum of the user's cards is equal to 21 then the user wins
    if (cardScore(playerCards, playerHand) == 21) {
        cout << endl;
        cout << "Congrats, you are the winner!" << endl;
        user.money += user.bet;

        cout << "Your new balance is: $ " << user.money << endl;
    }

    //if the sum of the user's cards is more than 21 then the user's busts
    else if (cardScore(playerCards, playerHand) > 21) {
        cout << endl;
        cout << "Looks like you have busted!" << endl;
        user.money -= user.bet;

        cout << "Your new balance is: $ " << user.money << endl;
    }

    //if the sum of the user's hand is less than 21 then keep going
    else {
        cout << endl;
        // cout << "Here are your final cards " << user.name << " : " << endl;
        // printCardVector(playerCards, playerHand);
        cout << endl << "The dealer's revealed cards: " << endl;
        printCardVector(dealerCards, dealerHand);

        // if (dealerTotalHand <= 16 && !(dealerTotalHand >= 21)) {
        //     dealerHand++;
        //     dealerCards.push_back(new Card(rand() % 52));
        //     cout << "Dealer's new hand" << endl;
        //     printCardVector(dealerCards, dealerHand);
        //     dealerTotalHand = cardScore(dealerCards, dealerHand);
        // }

        //if dealer's card sum is more than 21 then the user wins
        if (dealerTotalHand > 21) {
            cout << endl;
            cout << "The dealer busted, you win!" << endl;
            user.money += user.bet;

            cout << "This is your new balance: $ " << user.money << endl;
        }

        // if the dealer has more than the user, dealer wins
        else if (dealerTotalHand > playerTotalHand) {
            cout << endl;
            cout << "The dealer won!" << endl;
            user.money -= user.bet;

            cout << "This is your new balance: $ " << user.money << endl;
        }

        // if the dealer has the same sum as the player, it's tie
        else if (dealerTotalHand == playerTotalHand) {
            cout << endl;
            cout << "You and the dealer have tied!" << endl;

            cout << "This is your new balance: $ " << user.money << endl;
        }

        // if the player has more than the dealer, user win
        else if (playerTotalHand > dealerTotalHand) {
            cout << endl;
            cout << "Congrats, you won!" << endl;
            user.money += user.bet;

            cout << "This is your new balance: $ " << user.money << endl;
        }
    }
}

int main() {
    srand(time(0));
    string name;
    int age;
    int money = 0;
    int bet = 0;

    // create instance of the user and dealer
    Player user;
    Player dealer;

    //give a name to the dealer
    dealer.name = "Dealer";

    //create variables
    int selection; // player's selection of what option they choose on the menu
    string keepPlaying; // player's selection to keep playing or stop
    string moreMoney;

    system("clear"); // Clear the screen to start the game

    //print the welcome message at the start of the game
    cout << "Hello I am Michelle, the host for tonight, welcome to my Blackjack "
        "game!"
        << endl
        << endl;

    do {

        gameMenu();       // displays the menu
        cin >> selection; // take in the user input

        if (selection == 1) {// if the user wants to read the rules
            system("clear");
            gameRules();// displays the rules
        }
        else if (selection == 2) { // if the user wants to play
            system("clear");

            cout << "Let the game begin!" << endl << endl;
            cout << "What is your name?" << endl; //get name of the user
            cin >> user.name;
            cout << endl;

            cout << "How old are you?" << endl; //age of the user
            cin >> user.age;
            cout << endl;

            //make sure the user is older than 18
            if (user.age < 18) {
                cout << "You are too young to be playing this game. Come back in a "
                    "couple years!" << endl << endl;
            }
            else {
                do {
                    cout << "How much money would you like to deposit?" << endl; //deposit from the user
                    cout << "$";
                    cin >> user.money;

                    cout << endl;
                    //start the game
                    game(user, dealer);

                    //if user has money then keep going with the game
                    if (user.money > 0) {
                        cout << endl;
                        cout << "Enter Y to play again or E to exit the game: " << endl;
                        cout << "Selection: ";
                        cin >> keepPlaying;

                        cout << endl;
                    }

                    //if user does not have enough money then ask if he wants to add funds or exit
                    else if (user.money <= 5) {
                        cout << endl;
                        cout << "You are currently out of money. Press A to add money or E "
                            "to exit"
                            << endl;
                        cout << "Selection: ";
                        cin >> moreMoney;
                        cout << endl;

                        do {
                            if (moreMoney == "A" || moreMoney == "a") {
                                cout << "How much would you like to add?" << endl; //add funds
                                cout << "$ ";
                                cin >> user.money;

                                //restart the game w money
                                game(user, dealer);
                            }
                            else if (moreMoney == "E" || moreMoney == "e") {
                                cout << "Hope to see you again when you have more money!";
                                cout << endl;
                            }
                        } while (moreMoney != "Y" || moreMoney != "y" || moreMoney != "N" ||
                            moreMoney != "n");
                    }
                } while (keepPlaying == "Y" || keepPlaying == "y");
            }
        }

        else { // if the user can't follow directions
            cout << endl;
            cout << "Please start following my rules! Enter 1 or 2" << endl << endl;

            selection = 0; // resets menu
            cin.ignore();
        }
    } while (selection != 2);

    //goodbye message
    cout << "Thanks for playing " << user.name << " you have $" << user.money
        << " in your account" << endl;
    cout << "Hope to see you again!" << endl;

    return 0;
}
