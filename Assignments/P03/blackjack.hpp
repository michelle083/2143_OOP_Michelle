#include <algorithm> // std::random_shuffle
#include <fstream>
#include <iostream>
#include <stdio.h>
#include <string>
#include <sys/ioctl.h>
#include <unistd.h>
#include <vector>
#include <map>
#include "colors.h"

using namespace std;

typedef map<string, string> printableCard;

const string spade = "♠";
const string diamond = "♦";
const string heart = "♥";
const string club = "♣";

const string suits[4] = { "♠", "♥", "♦", "♣" };

// Card labels (could be "Iron Man" or "Charmander" or "Elf" ... anything)
const string ranks[13] =
{ "A", "2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K" };

map<string, string> colorMap{	{"♠", BBLACK},
								{"♥", BRED},
								{"♦", BRED},
								{"♣", BBLACK } };


/*
   ____    _    ____  ____
  / ___|  / \  |  _ \|  _ \
 | |     / _ \ | |_) | | | |
 | |___ / ___ \|  _ <| |_| |
  \____/_/   \_\_| \_\____/

*/

class Card {
protected:
	int suitNum;	 // value 0-3 : num index of suit
	int rank;		 // 0-13      : num value of rank
	int number;		 // 1-52      : unique value determines card
	int value;		 // 1-14      : numeric value used for comparison

	string suitChar; // "♠", "♦", "♣", "♥"
	string rankChar; // Ace, 1 ,2 ,3 ... Q, K
	string fcolor;   // Spade=blue, Diamond=red, etc.
	string bcolor;
	void Init(int, string, string);

public:

	Card(int);
	Card(int, string, string);

	string Repr();

	bool operator<(const Card&);
	bool operator>(const Card&);
	bool operator==(const Card&);
	bool operator!=(const Card&);
	bool operator()(const Card&);

	friend ostream& operator<<(ostream& os, const Card& card);

	int getRank() {
		return rank;
	}
	string getRankChar() {
		return rankChar;
	}
	string getSuitChar() {
		return suitChar;
	}
	string getfColor() {
		return fcolor;
	}
	string getbColor() {
		return bcolor;
	}

	printableCard cardMap() {
		string content;

		// only 2 digit rank
		if (rankChar != "10") {
			content = " " + suitChar + " " + rankChar;
		}
		else {
			content = " " + suitChar + rankChar;
		}

		printableCard p{	{"TOP", fcolor + bcolor + "┌────┐"},
							{"MID", fcolor + bcolor + "│" + content + "│"},
							{"BOT", fcolor + bcolor + "└────┘" + OFF} };

		return p;
	}
};

/**
 * Public : Card
 *
 * Description:
 *      Represents a single card in a deck of cards to include a
 *      value along with rank and suit. We are assuming a standard
 *      card type in a deck of playing cards.
 *
 * Params:
 *      int :  value from 0 - 51 that represents a card in a deck.
 *
 * Returns:
 *      None
 */
Card::Card(int num) {
	int color = num / 13;
	Init(num, colorMap[suits[color]], ON_WHITE);
}

Card::Card(int num, string fgc, string bgc) {
	Init(num, fgc, bgc);
}

void Card::Init(int num, string fgc, string bgc) {
	number = num;
	suitNum = number / 13;
	suitChar = suits[suitNum];
	// fcolor = to_string(1+ rand() % 7);
	fcolor = fgc;
	bcolor = bgc;
	rank = number % 13;
	rankChar = ranks[rank];
}

void printSingleCard(vector<Card*> cards)
{
	printableCard c;
	int index = 0;

	//only runs once, as only one cards needs printed
	while (index < 1) {
		for (int i = index; i < index + 1; i++) {
			c = cards[i]->cardMap();
			cout << c["TOP"] << OFF;
		}
		cout << endl;
		for (int i = index; i < index + 1; i++) {
			c = cards[i]->cardMap();
			cout << c["MID"] << OFF;
		}
		cout << endl;
		for (int i = index; i < index + 1; i++) {
			c = cards[i]->cardMap();
			cout << c["BOT"] << OFF;
		}
		cout << endl;
		index++;
	}
	cout << endl;
}


void printCardVector(vector<Card*> cards, int cols = 2)
{
	printableCard c;
	int index = 0;

	while (index < cards.size()) {
		for (int i = index; i < index + cols; i++) {
			c = cards[i]->cardMap();
			cout << c["TOP"] << OFF;
		}
		cout << endl;
		for (int i = index; i < index + cols; i++) {
			c = cards[i]->cardMap();
			cout << c["MID"] << OFF;
		}
		cout << endl;
		for (int i = index; i < index + cols; i++) {
			c = cards[i]->cardMap();
			cout << c["BOT"] << OFF;
		}
		cout << endl;
		index += cols;
		if (index + cols >= 52) {
			cols = 52 % cols;
		}
	}

	cout << endl;
}
