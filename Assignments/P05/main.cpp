/*************************************************************************
 *
 *  Author:           Michelle Orru
 *  Label:            P05
 *  Title:            BolNiverse Fight Club Program
 *  Course:           CMPS 2143
 *  Semester:         Fall 2022
 *
 *  Description:
 *        This program creates the appropriate number of characters 
 *        based on the input file, and proceeds to manage battles between 
 *        attackers and defenders choosing the appropriate character to 
 *        fight based on the given rules.
 *
 *  Files:
 *       main.cpp       
 *       dice.hpp        
 *       fighter.hpp        
 *       helpers.hpp
 *       weaapon.hpp
 *
 *************************************************************************/

#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>
#include <unistd.h>
#include <vector>

#include "dice.hpp"
#include "fighter.hpp"
#include "helpers.hpp"
#include "weapon.hpp"

using namespace std;

//function to get the percentage value 
int Percentages(int total, int n) {
    double value = (double)n / total;
    return value * 100;
}


int main() {
    srand(time(0));

    //variables for input file
    ifstream infile;
    string infileName;

    //asking the users for the name of the input file
    cout << "Please enter name of the input file that contains the attackers: ";
    cin >> infileName;
    infile.open(infileName);
    // clear the screen
    system("clear");

    //create variables
    int totalRounds = 0;
    int attackerWins = 0;
    int defenderWins = 0;
    BaseFighter* currentAttacker;
    BaseFighter* currentDefender;
    int attackerTotal;
    int defenderTotal;
    int value;

    // create attackers and defenders
    Attacker attack(infile);
    Defender defend(attack.Size());
    attackerTotal = attack.Size();
    defenderTotal = defend.Size();

    while ((attack.Size() > 0) && (defend.Size() > 0)) {
        int count = 0;

        currentAttacker = &attack[0];
        currentDefender = &defend[0];
        value = 0;
        // finding matching defender to fight attacker
        while ((currentDefender->getname() != currentAttacker->getname()) &&
            (value < defend.Size())) {
            value++;
            if (value < defend.Size()) {
                currentDefender = &defend[value];
            }
        }
        // lets the leading defender fight if there is no matching fighter
        if (value == (defend.Size())) {
            value = 0;
            currentDefender = &defend[value];
        }

        cout << "There are " << attack.Size() << " Attackers, and " << defend.Size()
            << " Defenders" << endl;
        cout << "Attacker: " << *currentAttacker << endl;
        cout << " against " << endl;
        cout << "Defender:" << *currentDefender << endl;

        //start of the fight
        while (currentAttacker->playerAlive() && currentDefender->playerAlive()) {

            if (currentDefender->getMaxHP() >= currentAttacker->getMaxHP()) {
                // defender going first
                currentAttacker->setHP(currentAttacker->getHP() -
                    currentDefender->attack());

                // if attacker doesnt die then the attacker get to attack
                if (currentAttacker->playerAlive() == true) {
                    currentDefender->setHP(currentDefender->getHP() -
                        currentAttacker->attack());
                }
            }
            else {
                // attacker attacks first
                currentDefender->setHP(currentDefender->getHP() -
                    currentAttacker->attack());

                // if the defender dies then the defender attacks
                if (currentDefender->playerAlive() == true) {
                    currentAttacker->setHP(currentAttacker->getHP() -
                        currentDefender->attack());
                }
            }

            //heal their health
            attack.heal();
            defend.heal();

            //increment the total rounds fought
            totalRounds++;
        }

        //delete players from list based on whoever's winning
        if (currentAttacker->playerAlive() == false) {
            cout << "The attacker died!";
            system("clear");
            attack.deletePlayer();

            defenderWins++;
        }
        if (currentDefender->playerAlive() == false) {
            cout << "The defender died!";
            system("clear");
            defend.deletePlayer(value);

            value = 0;
            attackerWins++;
        }
    }

    //determine the overall winner and cout the stats
    if (attack.Size() == 0) {
        cout << endl;
        cout << "The Defenders win!" << endl;
        cout << "The initial number of attackers was: " << attackerTotal << endl;
        cout << "The initial number of defenders was: " << defenderTotal << endl;
        cout << "Total rounds fought were: " << totalRounds << endl;
        cout << endl;

        cout << attackerWins << " attackers won with a winning percentage of " << Percentages(totalRounds, attackerWins) << " %" << endl;
        cout << defenderWins << " defenders won with a winning percentage of " << Percentages(totalRounds, defenderWins) << " %" << endl;
    }

    if (defend.Size() == 0) {
        cout << endl;
        cout << "The Attackers win!" << endl;
        cout << "The initial number of attackers was: " << attackerTotal << endl;
        cout << "The initial number of defenders was: " << defenderTotal << endl;
        cout << "Total rounds fought were: " << totalRounds << endl;
        cout << endl;

        cout << attackerWins << " attackers won with a winning percentage of " << Percentages(totalRounds, attackerWins) << " %" << endl;
        cout << defenderWins << " defenders won with a winning percentage of " << Percentages(totalRounds, defenderWins) << " %" << endl;
    }

    infile.close();
}



// exmple output

/* 
The defender died!
The Attackers win!
The initial number of attackers was : 1699
The initial number of defenders was : 16
Total rounds fought were : 55

16 attackers won with a winning percentage of 29 %
25 defenders won with a winning percentage of 45 %
*/
