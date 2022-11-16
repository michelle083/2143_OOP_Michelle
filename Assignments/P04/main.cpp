/*************************************************************************
 *
 *  Author:           Michelle Orru
 *  Label:            P04
 *  Title:            RPSLS Program
 *  Course:           CMPS 2143
 *  Semester:         Fall 2022
 *
 *  Description:
 *        This is my program for the RPSLS game. 
 *
 *  Files:
 *       main.cpp        : driver program
 *       emojis.h        : header file with EMOJI defintion
 *
 *************************************************************************/

//#include "emoji.h"    //https://github.com/99x/emojicpp
#include <functional> // needed for `bind`
#include <iostream>
#include <list>
#include <map>
#include <random>
#include <stdio.h>
#include <string>
#include <unistd.h>

using namespace std;

#define ROCK u8"\U0000270A"
#define PAPER u8"\U0000270B"
#define SCISSORS u8"\U0001F44C"
#define LIZARD u8"\U0001F918"
#define SPOCK u8"\U0001F596"

#define ROCK2 u8"\U0001F5FB"
#define PAPER2 u8"\U0001F4C3"
#define SCISSORS2 u8"\U0001F52A"
#define LIZARD2 u8"\U0001F438"
#define SPOCK2 u8"\U0001F596"

/**
 * This class is used to test the random number generators by creating an
 * array with the same sides as some die. Then counting the values generated
 * between 1 and die size. There should be an equal number in every slot, which
 * for a 20 sided die is about .05 or 5 percent in each.
 *
 */
class Tester {
  int *arr;
  int size;

public:
  Tester() : size{20} {
    arr = new int[size + 1];
    initArr();
  }

  Tester(int size) : size{size} {
    arr = new int[size + 1];
    initArr();
  }

  void initArr() {
    for (int i = 0; i < size + 1; i++) {
      arr[i] = 0;
    }
  }

  // add random value to distribution table
  void load(int i) { arr[i]++; }

  // generate  the distribution table
  void distro(double res[], double total) {
    for (int i = 0; i < size + 1; i++) {
      res[i] = (double)arr[i] / total;
    }
  }
};

/**
 * RandRoll
 * @description: A class to implement roll playing dice rolls.
 * @methods:
 * private:
 *      int Random(Max) : returns a value between 0 and max.
 *      int Random(Min , Max) : returns a value between min and max
 *      void init(int , int)  : initialize class
 * public:
 *      DieRoll()
 *      DieRoll(int)
 *      DieRoll(int,int)
 *      void setDie(int)    : set sides
 *      int Roll(int,int)   :  NEEDS FIXING!!!!!!
 */
class DieRoll {
  int sides;

  int Random(int max) { return 1 + (rand() % max); }

  // min = 40 max = 100
  int Random(int min, int max) { return 1 + min + (rand() % (max - min)); }

  void init(int _seed, int _sides) {
    sides = _sides;
    srand(_seed);
  }

public:
  DieRoll() {
    // cout << "default base" << endl;
    init(time(0), 6);
  }
  DieRoll(int _seed) {
    // cout << "overloaded const" << endl;
    init(_seed, 6);
  }
  DieRoll(int _seed, int _sides) {
    // cout << "overloaded const" << endl;
    init(_seed, _sides);
  }

  void setDie(int _sides) { sides = _sides; }

  // rolls of a die and return a value
  int Roll(int sides, int times) {
    int sum = 0;
    while (times--) {
      sum += Random(sides);
    }
    return sum;
  }
};

/**
 * RandRoll
 * @description: A random die roller using a "better" random
 *      number generator. Docs: https://www.cplusplus.com/reference/random/
 *
 * @methods:
 *     int Roll(int)    : give the "sides" will return an int between 1 and
 * sides inclusive.
 *
 */
class RandRoll {
  default_random_engine generator;
  uniform_int_distribution<int> dieMap[21];

public:
  /**
   * Constructor
   *
   * @description: Create an stl array that has the common dice values
   *              loaded as uniform distribution types.
   *
   *  Wasteful, as not every array location has a uniform distribution
   *  associated with it. Could you make it less wasteful?
   */
  RandRoll() {
    dieMap[4] = uniform_int_distribution<int>(1, 4);
    dieMap[6] = uniform_int_distribution<int>(1, 6);
    dieMap[8] = uniform_int_distribution<int>(1, 8);
    dieMap[10] = uniform_int_distribution<int>(1, 10);
    dieMap[12] = uniform_int_distribution<int>(1, 12);
    dieMap[20] = uniform_int_distribution<int>(1, 20);
  }

  /**
   * Generate a random number depending on the "sides" of the dice.
   */
  int Roll(int sides) {
    int diceRoll = dieMap[sides](generator);
    return diceRoll;
  };
};

/**
 * Hands
 *
 * @description: A static class that only has references to
 *      emojis for printing out Rock Paper Scissors Lizard Spock
 *
 * @methods:
 *      string RandHand()   : returns a random hand (emoji)
 *      string Rock()       : returns the emoji for "rock"
 *      string Paper()      : returns the emoji for "paper"
 *      string Scissors()   : returns the emoji for "scissors"
 *      string Lizard()     : returns the emoji for "lizard"
 *      string Spock()      : returns the emoji for "spock"
 */
struct Hands {
  const string rock = ROCK2;
  const string paper = PAPER2;
  const string scissors = SCISSORS2;
  const string lizard = LIZARD2;
  const string spock = SPOCK2;

  static map<string, string> Emojis; // stl map
  //         name  , emoji

  static map<string, string> Names; // stl map
  //         emoji  , name

  static string RandHand() {
    auto it = Emojis.begin(); // iterator to front of map

    advance(it, rand() % Emojis.size()); // advance some random amnt
    //   of steps

    string random_hand = it->second; // grab emoji from map

    return random_hand; // return rand emoji
  }

  static string Rock() { return Emojis["rock"]; }
  static string Paper() { return Emojis["paper"]; }
  static string Scissors() { return Emojis["scissors"]; }
  static string Lizard() { return Emojis["lizard"]; }
  static string Spock() { return Emojis["spock"]; }
};

// initialize static data member for
// hands struct (class)
map<string, string> Hands::Emojis = {{"rock", ROCK2},
                                     {"paper", PAPER2},
                                     {"scissors", SCISSORS2},
                                     {"lizard", LIZARD2},
                                     {"spock", SPOCK2}};
// initialize static data member for
// hands struct (class)
map<string, string> Hands::Names = {{ROCK2, "rock"},
                                    {PAPER2, "paper"},
                                    {SCISSORS2, "scissors"},
                                    {LIZARD2, "lizard"},
                                    {SPOCK2, "spock"}};

// class player: public hands
class Player : public Hands {
private:
  string hand;

public:
  Player() { hand = RandHand(); }

  void changehand() { hand = RandHand(); }

  string getCname() { return Hands::Names[hand]; }

  void sethand(string a) { hand = Hands::Emojis[a]; }

  friend ostream &operator<<(ostream &os, const Player &P) {
    return os << P.hand;
  }
};

/**
 * Rock Paper Scissors Lizard Spock
 *
 */
class RPSLS : public DieRoll, public Hands {
private:
  map<string, map<string, int>> winnerMap;
  string characters[5] = {"rock", "paper", "scissors", "lizard", "spock"};

public:
  RPSLS() {
    //hardcoded table
    int choice[][5] = {{0, -1, 1, 1, -1},
                       {1, 0, -1, -1, 1},
                       {-1, 1, 0, 1, -1},
                       {-1, 1, -1, 0, 1},
                       {1, -1, 1, -1, 0}};

    for (int i = 0; i < 5; i++) {
      for (int j = 0; j < 5; j++) {
        winnerMap[characters[i]][characters[j]] = choice[i][j];
      }
    }
  }

  //display the weapons of the players
  void gameDisplay(Player P1, Player P2) {
    cout << "Player 1 weapon: " << P1 << '\t' << '\t';
    cout << "Player 2 weapon: " << P2 << endl;
  }

  int getWinner(string a, string b) { 
    return winnerMap[a][b]; 
  }
};

// display at the start of the game for player to choose
void gameMenu() {
  cout << "Please select an option below: " << endl << endl;
  cout << "1) Display the rules used to determine the winner" << endl;
  cout << "2) Start the game!" << endl;
  cout << "Selection : ";
}

// If player selects to see the rules then diplay this
void rpslsRules() {
  cout << "RPSLS rules to determine the winner: " << endl;
  cout << "   Scissors cuts Paper " << endl;
  cout << "   Paper covers Rock " << endl;
  cout << "   Rock crushes Lizard " << endl;
  cout << "   Lizard poisons Spock " << endl;
  cout << "   Spock smashes Scissors " << endl;
  cout << "   Scissors decapitates Lizard " << endl;
  cout << "   Lizard eats Paper " << endl;
  cout << "   Paper disproves Spock " << endl;
  cout << "   Spock vaporizes Rock " << endl;
  cout << "   Rock crushes Scissors " << endl;
  cout << endl << endl;
}

int main() {
  srand(time(0));
  int selection; // player's selection of what option they choose on the menu
  int rounds;

  Player P1;
  Player P2;
  RPSLS cpuGame;

  int winner;
  system("clear");
  cout << "WELCOME TO MY RPSLS GAME!" << endl << endl;
  do {

    gameMenu();       // displays the menu
    cin >> selection; // take in the user input

    if (selection == 1) { // if the user wants to read the rules
      system("clear");
      rpslsRules();              // displays the rules
    } 
    else if (selection == 2) { // if the user wants to play
      system("clear");
      cout << "How many rounds would you like to play?"
           << endl;  // ask the user how many rounds they wanna see
      cin >> rounds; // in puts the number of rounds
      cout << endl;

      system("clear");
      for (int i = 0; i < rounds; i++) {

        cout << "ROUND NUMBER " << i + 1 << " :" << endl;
        // display the weapons of the players
        cpuGame.gameDisplay(P1, P2);

        // get results
        winner = cpuGame.getWinner(P1.getCname(), P2.getCname());

        // check results and display winner
        if (winner == -1) {
          cout << endl << endl;
          cout << "Player 2 is the winner!" << endl << endl << endl;
        }

        else if (winner == 1) {
          cout << endl << endl;
          cout << "Player 1 is the winner!" << endl << endl << endl;
        }

        // tie
        else {
          cout << endl << endl;
          cout << "It's a tie, let's run a rematch!" << endl << endl << endl;

          P1.changehand();
          P2.changehand();
        }

        P1.changehand();
        P2.changehand();
      }
    } 
    else { // if the user can't follow directions
      cout << endl;
      cout << "Please start following my rules! Enter 1 or 2" << endl << endl;

      selection = 0; // resets menu
      cin.ignore();
    }
  } while (selection != 2);

  cout << endl << "Thank you for playing, hope you enjoyed it! " << endl;
  return 0;
}
