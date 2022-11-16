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
  cout << "1) display the rules" << endl;
  cout << "2) start the game!" << endl;
  cout << "Selection : ";
}

// If player selects to see the rules then diplay this
void gameRules() {
  cout << endl;
  cout << "My Blackjack game rules: " << endl;
  cout << "   Your goal in blackjack is to beat the dealer hand without going "
          "over 21."
       << endl;
  cout << "   You will receive 2 cards at the beginning of each round, and you "
          "will add up the values of these cards."
       << endl;
  cout << "   Cards 2 - 10 have face value; 'J', 'Q', 'K' are worth 10; 'A' "
          "are either a 1 or an 11"
       << endl;
  cout << "   The dealer also draws two cards.The aim of the game is to have a "
          "higher hand than dealer without going over 21."
       << endl;
  cout << "   If you would like the dealer to deal you another card, you tell "
          "him HIT"
       << endl;
  cout << "   If you do not want to be dealt another card, you STAND." << endl;
  cout << "   BURST is when the sum of your hand is over 21." << endl;
  cout << "   The winner of the round is whoever has the highest hand without "
          "going bust."
       << endl
       << endl;
} // source for these rules : (https://www.blackjack.org/blackjack/how-to-play/)

//score of the card
int cardScore(vector<Card *> cards, int numOfCards) {
  int t = 0; // total
  for (int i = 0; i < numOfCards; i++) {
    if (cards[i]->getRank() >= 10) {
      t += 10;
    } 
    else {
      t += cards[i]->getRank() + 1;
    }
  }

  return t;
}

// function for the player's turn
void playerBet(Player &user) {
  int bet = 0;

  // repeat until they decide to bet within their balance
  do {
    cout << "" << user.name
         << " how much money would you like to bet? (Must be greater than $5 "
            "and less than $"
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
void game(Player &user, Player &dealer) {
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
  vector<Card *> playerCards;
  vector<Card *> dealerCards;

  // randomly create cards for dealer and player
  for (int i = 0; i < 2; i++) {
    playerCards.push_back(new Card(rand() % 52));
    dealerCards.push_back(new Card(rand() % 52));
  }

  cout << endl;

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
    cout << endl;

    // if player choose to hit then give new card
    if (playerSelection == "H" || playerSelection == "h") {
      cout << "Player's new cards: " << endl;
      playerHand++;
      playerCards.push_back(new Card(rand() % 52));

      if (playerHand > 9 && playerHand % 2 == 0) {
        printCardVector(playerCards, playerHand / 2);
      }

      else {
        printCardVector(playerCards, playerHand);
      }
    } 
    else if (playerSelection == "S" || playerSelection == "s") {
      playerCount = cardScore(playerCards, 2); // new count
    }
  }

  int playerTotalHand = cardScore(playerCards, playerHand);
  int dealerTotalHand = cardScore(dealerCards, dealerHand);

  // results
  if (cardScore(playerCards, playerHand) == 21) {
    cout << endl;
    cout << "Congrats, you are the winner!" << endl;
    user.money += user.bet;

    cout << "Your new balance is: $ " << user.money << endl;
  } 
  else if (cardScore(playerCards, playerHand) > 21) {
    cout << endl;
    cout << "Looks like you have busted!" << endl;
    user.money -= user.bet;

    cout << "Your new balance is: $ " << user.money << endl;
  } 
  else {
    cout << endl;
    cout << "Here are your final cards " << user.name << " : " << endl;
    printCardVector(playerCards, playerHand);
    cout << endl << "The dealer's revealed cards: " << endl;
    printCardVector(dealerCards, dealerHand);

    if (dealerTotalHand <= 16 && !(dealerTotalHand >= 21)) {
      dealerHand++;
      dealerCards.push_back(new Card(rand() % 52));
      cout << "Dealer's new hand" << endl;
      printCardVector(dealerCards, dealerHand);
      dealerTotalHand = cardScore(dealerCards, dealerHand);
    }

    if (dealerTotalHand > 21) {
      cout << endl << endl;
      cout << "The dealer busted, you win!" << endl;
      user.money += user.bet;

      cout << "This is your new balance: $ " << user.money << endl;
    }
      
    // if the dealer has more than the player, they win
    else if (dealerTotalHand > playerTotalHand) {
      cout << endl;
      cout << "The dealer won!" << endl;
      user.money -= user.bet;

      cout << "This is your new balance: $ " << user.money << endl;
    }
      
    // if the dealer has the same as the player, they tie
    else if (dealerTotalHand == playerTotalHand) {
      cout << endl;
      cout << "You and the dealer have tied!" << endl;

      cout << "Your final balance is: " << user.money << endl;
    }
      
    // if the player has more than the dealer, they win
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

  // players
  Player user;
  Player dealer;

  dealer.name = "Dealer";

  int selection; // player's selection of what option they choose on the menu
  string keepPlaying; // player's selection to keep playing or stop
  string moreMoney;
  
  system("clear"); //Clear the screen to start the game
  
  cout << endl << "Hello I am Michelle, the host for tonight, welcome to my Blackjack "
          "game!"
       << endl << endl;

  do {
    do{ 
      gameMenu();       // displays the menu
      cin >> selection; // take in the user input
  
      if (selection == 1) {        // if the user wants to read the rules
        system("clear");
        gameRules();               // displays the rules
      } 
      else if (selection == 2) { // if the user wants to play
        system("clear");
        
        cout << endl << "Let the game begin!" << endl << endl;
        cout << "What is your name?" << endl;
        cin >> user.name;
        cout << endl;
  
        cout << "How old are you?" << endl;
        cin >> user.age;
        cout << endl;
  
        if (user.age < 18) {
          cout << "You are too young to be playing this game. Come back in a "
                  "couple years!"
               << endl
               << endl;
        } 
        else {
          cout << "How much money would you like to deposit?" << endl;
          cout << "$";
          cin >> user.money;
          cout << endl;

          game(user, dealer);
  
          if (user.money > 5) {
            system("clear");
            cout << endl;
            cout << "Enter Y to play again or E to exit the game: " << endl;
            cout << "Selection: ";
            cin >> keepPlaying;
  
            cout << endl;
          } 
          else if (user.money <= 5) {
            cout << endl;
            cout << "You are currently out of money. Press A to add money or E "
                    "to exit"
                 << endl;
            cout << "Selection: ";
            cin >> moreMoney;
            cout << endl;
  
            do {
              if (moreMoney == "Y" || moreMoney == "y") { // if they say yes
                cout << "How much would you like to add?" << endl; // how much
                cin >> user.money;                                 // takes it in
              } 
              else if (moreMoney == "N" || moreMoney == "n") {
                cout << "Hope to see you again when you have more money!";
                cout << endl;
              }
            } while (moreMoney != "Y" || moreMoney != "y" 
                    || moreMoney != "N" || moreMoney != "n");
          }
        }
  
      } 
      else { // if the user can't follow directions
        cout << endl;
        cout << "Please start following my rules! Enter 1 or 2" << endl << endl;
  
        selection = 0; // resets menu
        cin.ignore();  // ignores what's in the buffer
      }
    } while (keepPlaying == "Y" || keepPlaying == "y");
  } while (selection != 2);

  cout << endl;
  cout << "Thanks for playing " << user.name << " you have $" << user.money
       << " in your account" << endl;
  cout << "Hope to see you again!" << endl;

  return 0;
}

