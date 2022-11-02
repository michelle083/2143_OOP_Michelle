#include "colors.h"
#include <algorithm> // std::random_shuffle
#include <fstream>
#include <iostream>
#include <stdio.h>
#include <string>
// #include <sys/ioctl.h>
// #include <unistd.h>
#include <vector>

using namespace std;

const string spade = "♠";
const string diamond = "♦";
const string heart = "♥";
const string club = "♣";

const string suits[4] = { "♠", "♥", "♦", "♣" };

string Black = "0";
string Red = "1";
string Green = "2";
string Yellow = "3";
string Blue = "4";
string Purple = "5";
string Cyan = "6";
string White = "7";
string Default = "9";

void printColor(string out, int fg, int bg = 9) {
	cout << "\033[0;3" << fg << ";4" << bg << "m" << out << "\033[0;39;49m";
}

// Card labels
const string ranks[13] =
{ "A", "2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K" };

/*
   ____    _    ____  ____
  / ___|  / \  |  _ \|  _ \
 | |     / _ \ | |_) | | | |
 | |___ / ___ \|  _ <| |_| |
  \____/_/   \_\_| \_\____/

*/

class CardContainer;
class Hand;

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

public:
	friend class Hand;
	Card();
	Card(int);
	string Repr();
	bool operator<(const Card&);
	bool operator>(const Card&);
	bool operator==(const Card&);
	bool operator!=(const Card&);

	friend ostream& operator<<(ostream& os, const Card& card);
	friend class CardContainer;
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
};

/**
 * Public : operator <<
 *
 * Description:
 *      Overload ostream and send the string representation "Repr"
 *      of the card.
 *
 *      We don't need the scope resolution operator (Card::) since
 *      this is a "friend" of card.
 *
 * Params:
 *      [ostream&] : os
 *      [Card]     : obj
 *
 * Returns:
 *      [ostream&]
 */
ostream& operator<<(ostream& os, const Card& card) {
	os << "\033[0;3" << card.fcolor << ";4" << card.bcolor << "m";
	os << "┌────┐\n";
	os << "│";
	// rank 9 is really 10
	if (card.rank != 9) {
		os << " ";
	}
	os << card.rankChar << " " << card.suitChar << "│\n";
	os << "└────┘";
	os << "\033[0;39;49m";

	return os;
}

string PrintCard(Card* card) {
	string c = "";
	c += "\033[0;3" + card->getfColor() + ";4" + card->getbColor() + "m";
	c += "┌────┐\n";
	c += "│";
	// rank 9 is really 10
	if (card->getRank() != 9) {
		c += " ";
	}
	c += to_string(card->getRank()) + " " + card->getSuitChar() + "│\n";
	c += "└────┘";
	c += "\033[0;39;49m";

	return c;
}

Card::Card() {
	// fcolor = to_string(1+ rand() % 7);
	fcolor = to_string(0);
	bcolor = "7";
}

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
	number = num;
	suitNum = number / 13;
	suitChar = suits[suitNum];
	// fcolor = to_string(1+ rand() % 7);
	fcolor = to_string(suitNum + 2);
	bcolor = "9";
	rank = number % 13;
	rankChar = ranks[rank];
}

bool Card::operator<(const Card& rhs) {
	return this->rank < rhs.rank;
}

bool Card::operator>(const Card& rhs) {
	return this->rank > rhs.rank;
}

bool Card::operator==(const Card& rhs) {
	return this->rank == rhs.rank;
}

bool Card::operator!=(const Card& rhs) {
	return this->rank != rhs.rank;
}

/*
   ____    _    ____  ____   ____ ___  _   _ _____  _    ___ _   _ _____ ____
  / ___|  / \  |  _ \|  _ \ / ___/ _ \| \ | |_   _|/ \  |_ _| \ | | ____|  _ \
 | |     / _ \ | |_) | | | | |  | | | |  \| | | | / _ \  | ||  \| |  _| | |_) |
 | |___ / ___ \|  _ <| |_| | |__| |_| | |\  | | |/ ___ \ | || |\  | |___|  _ <
  \____/_/   \_\_| \_\____/ \____\___/|_| \_| |_/_/   \_\___|_| \_|_____|_| \_\
*/

class CardContainer {
protected:
	vector<Card*> Cards;
	vector<Card*>::iterator it;

public:
	CardContainer();
	CardContainer(int);
	void Add(Card*);
	bool isEmpty();
	void Order();
	Card* Remove();
	void Reset();
	void Shuffle();
	int Size();
	vector<Card*>::iterator Next();
	friend ostream& operator<<(ostream& os, const CardContainer& cards);
};

ostream& operator<<(ostream& os, const CardContainer& c) {
	for (int i = 0; i < c.Cards.size(); i++) {
		os << "\033[0;3" << c.Cards[i]->getfColor() << ";4"
			<< c.Cards[i]->getbColor() << "m";
		os << "┌────┐";
		os << "\033[0;39;49m";
	}
	os << endl;
	for (int i = 0; i < c.Cards.size(); i++) {
		os << "\033[0;3" << c.Cards[i]->getfColor() << ";4"
			<< c.Cards[i]->getbColor() << "m";
		os << "│";
		if (c.Cards[i]->getRank() != 9) {
			os << " ";
		}
		os << c.Cards[i]->getRankChar() << " " << c.Cards[i]->getSuitChar()
			<< "│";
		os << "\033[0;39;49m";
	}
	os << endl;
	for (int i = 0; i < c.Cards.size(); i++) {
		os << "\033[0;3" << c.Cards[i]->getfColor() << ";4"
			<< c.Cards[i]->getbColor() << "m";
		os << "└────┘";
		os << "\033[0;39;49m";
	}
	os << endl;

	return os;
}

CardContainer::CardContainer() {
	it = Cards.begin();
}

void CardContainer::Add(Card* C) {
	Cards.push_back(C);
}

vector<Card*>::iterator CardContainer::Next() {
	if (it == Cards.end()) {
		it = Cards.begin();
	}
	return it++;
}

/*
  ____  _____ ____ _  __
 |  _ \| ____/ ___| |/ /
 | | | |  _|| |   | ' /
 | |_| | |__| |___| . \
 |____/|_____\____|_|\_\
*/

class Deck : public CardContainer {
protected:
	int deckSize;

public:
	Deck();
	Deck(int);
	Card* Draw();
	
	friend ostream& operator<<(ostream & os, Deck & cards) {
		for (int i = 0; i < cards.deckSize + 1; i++) {
			os << PrintCard(*cards.Next());
		}
		return os;
	}
	
};

Deck::Deck() {
	deckSize = 52;
	for (int i = 0; i < deckSize; i++) {
		Add(new Card(i));
	}
}

/*
  _   _    _    _   _ ____
 | | | |  / \  | \ | |  _ \
 | |_| | / _ \ |  \| | | | |
 |  _  |/ ___ \| |\  | |_| |
 |_| |_/_/   \_\_| \_|____/
*/
class Hand : public CardContainer {
protected:
public:
	Hand();
	void Print();
	int Size() {
		return Cards.size();
	}
	void Sort();
};

class Player {
protected:
	string name;
	Hand* hand;
	double bank;
	double bet;

public:
	Player() {
		hand = new Hand();
	}
	double getBet() {
		return bet;
	}
};
