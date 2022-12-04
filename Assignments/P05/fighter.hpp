#include <iostream>
#include <random>
#include <string>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <fstream>

#include "weapon.hpp"
#include "helpers.hpp"

//using namespace standard
using namespace std;

#pragma once

//function to generate a random number as a double 
//source: https://www.codegrepper.com/tpc/c%2B%2B+random+double 
double fRand(double fMin, double fMax) {
    double f = (double)rand() / RAND_MAX;
    return fMin + f * (fMax - fMin);
}

//class for the base fighter 
class BaseFighter {
protected:
    string name;
    Weapon* weapon;

    //HP (random from 3 - 8)
    int HP;
    //RR (random from 0.15 - 0.75)
    double RR;

    int MaxHP;
public:

    BaseFighter() {
        name = "None";
        weapon = new Weapon;
    }

    virtual double attack() {
        return weapon->use();
    }
    
    virtual int getHP() {
        return HP;
    }
    
    virtual void setHP(int h) {
        HP = h;
    }
    
    virtual void setHP(double h) {
        HP = h;
    }
    
    virtual double getRR() {
        return RR;
    }
    
    virtual string getname() {
        return name;
    }

    virtual bool playerAlive() {
        if (HP <= 0) {
            return false;
        }
        else {
            return true;
        }
    }
    
    virtual int getMaxHP() {
        return MaxHP;
    }

    //defined outside of class 
    friend double fRand(double, double);
    
    virtual string Print() {
        string temp = "";
        temp += "[";
        temp += name;
        temp += " , ";
        temp += "[";
        temp += weapon->getName();
        temp += " , ";
        temp += weapon->getDamage();
        temp += "]";
        temp += "]";
        return temp;
    }
    friend ostream& operator<<(ostream& os, BaseFighter& f) {
        return os << f.Print();
    }
};

//warrior class
class Warrior : public BaseFighter {
private:
    int HP;
    double RR;
public:
   
    Warrior() {
        name = "Warrior";
        HP = (rand() % 8 + 3);
        MaxHP = HP;
        RR = fRand(0.15, 0.75);

        int weaponType = (rand() % 2 + 1);
        if (weaponType == 1) {
            weapon = new Weapon("Sword", "1.d.4");
        }
        else {
            weapon = new Weapon("Sword", "1.d.6");
        }
    }
    // All overriden from the BaseFighter Class
    double attack() {
        return weapon->use();
    }
    int getHP() {
        return HP;
    }
    void setHP(int h) {
        HP = h;
    }
    void setHP(double h) {
        HP = h;
    }
    double getRR() {
        return RR;
    }
    string getname() {
        return name;
    }
    bool playerAlive() {
        if (HP <= 0) {
            return false;
        }
        else {
            return true;
        }
    }
   
    int getMaxHP() {
        return MaxHP;
    }
    friend double fRand(double, double);
};

class Wizard : public BaseFighter {
private:
    int HP;
    double RR;
public:
   
    Wizard() {
        name = "Wizard";
        HP = (rand() % 8 + 3);
        MaxHP = HP;
        RR = fRand(0.15, 0.75);

        int weaponType = (rand() % 4 + 1);
        if (weaponType == 1) {
            weapon = new Weapon("Magic", "1.d.20");
        }
        else if (weaponType == 2) {
            weapon = new Weapon("Magic", "2.d.10");
        }
        else if (weaponType == 3) {
            weapon = new Weapon("Magic", "3.d.6");
        }
        else {
            weapon = new Weapon("Magic", "5.d.4");
        }
    }

    // all overriden methods from the BaseFighter Class
    double attack() {
        return weapon->use();
    }

    int getHP() {
        return HP;
    }

    void setHP(int h) {
        HP = h;
    }

    void setHP(double h) {
        HP = h;
    }

    double getRR() {
        return RR;
    }

    bool playerAlive() {
        if (HP <= 0) {
            return false;
        }
        else {
            return true;
        }
    }

    int getMaxHP() {
        return MaxHP;
    }

    friend double fRand(double, double);
};

class Archer : public BaseFighter {
private:
    int HP;
    double RR;
public:
    
    Archer() {
        srand(time(0));
        name = "Archer";
        HP = (rand() % 8 + 3);
        MaxHP = HP;
        RR = fRand(0.15, 0.75);

        int weaponType = (rand() % 3 + 1);

        if (weaponType == 1) {
            weapon = new Weapon("Bow", "1.d.8");
        }
        else if (weaponType == 2) {
            weapon = new Weapon("Bow", "2.d.4");
        }
        else {
            weapon = new Weapon("Bow", "1.d.10");
        }
    }

    // overridden methods of the Base Fighter
    double attack() {
        return weapon->use();
    }

    int getHP() {
        return HP;
    }

    void setHP(int h) {
        HP = h;
    }

    void setHP(double h) {
        HP = h;
    }

    double getRR() {
        return RR;
    }

    bool playerAlive() {
        if (HP <= 0) {
            return false;
        }
        else {
            return true;
        }
    }

    int getMaxHP() {
        return MaxHP;
    }

    friend double fRand(double, double);
};

class Elf : public BaseFighter {
private:
    int HP;
    double RR;
    Weapon* weapon2;
public:

    Elf() {
        name = "Elf";
        HP = (rand() % 8 + 3);
        MaxHP = HP;
        RR = RR = fRand(0.15, 0.75);

        int weaponType = (rand() % 4 + 1);
        if (weaponType == 1) {
            weapon = new Weapon("Magic", "1.d.20");
        }
        else if (weaponType == 2) {
            weapon = new Weapon("Magic", "2.d.10");
        }
        else if (weaponType == 3) {
            weapon = new Weapon("Magic", "3.d.6");
        }
        else {
            weapon = new Weapon("Magic", "5.d.4");
        }

        int weaponType2 = (rand() % 2 + 1);
        if (weaponType2 == 1) {
            weapon2 = new Weapon("Sword", "1.d.4");
        }
        else {
            weapon2 = new Weapon("Sword", "1.d.6");
        }

    }
   
    double attack() {
        return (weapon->use() + weapon2->use());
    }

    //overridden methods from BaseFighter clsss
    int getHP() {
        return HP;
    }

    void setHP(double h) {
        HP = h;
    }

    void setHP(int h) {
        HP = h;
    }

    double getRR() {
        return RR;
    }

    bool playerAlive() {
        if (HP <= 0) {
            return false;
        }
        else {
            return true;
        }
    }

    int getMaxHP() {
        return MaxHP;
    }

    friend double fRand(double, double);
    
    string Print() {
        string temp = "";
        temp += "[";
        temp += name;
        temp += " , ";
        temp += "[";
        temp += weapon->getName();
        temp += " , ";
        temp += weapon->getDamage();
        temp += "]";
        temp += "[";
        temp += weapon2->getName();
        temp += " , ";
        temp += weapon2->getDamage();
        temp += "]";
        temp += "]";
        return temp;
    }
};

//draginborn class
class Dragonborn : public BaseFighter {
private:
    int HP;
    double RR;
    Weapon* weapon2;
public:
    
    Dragonborn() {
        name = "DragonBorn";
        HP = (rand() % 8 + 3);
        MaxHP = HP;
        RR = fRand(0.15, 0.75);

        int weaponType = (rand() % 4 + 1);
        if (weaponType == 1) {
            weapon = new Weapon("Magic", "1.d.20");
        }
        else if (weaponType == 2) {
            weapon = new Weapon("Magic", "2.d.10");
        }
        else if (weaponType == 3) {
            weapon = new Weapon("Magic", "3.d.6");
        }
        else {
            weapon = new Weapon("Magic", "5.d.4");
        }

        int weaponType2 = (rand() % 2 + 1);
        if (weaponType2 == 1) {
            weapon2 = new Weapon("Fire", "1.d.6");
        }
        else {
            weapon2 = new Weapon("Fire", "1.d.8");
        }

    }

    //overridden method from BaseFighter
    bool playerAlive() {
        if (HP <= 0) {
            return false;
        }
        else {
            return true;
        }
    }

    double attack() {
        return (weapon->use() + weapon2->use());
    }\

    int getHP() {
        return HP;
    }

    void setHP(int h) {
        HP = h;
    }

    void setHP(double h) {
        HP = h;
    }

    double getRR() {
        return RR;
    }

    int getMaxHP() {
        return MaxHP;
    }

    friend double fRand(double, double);
   
    string Print() {
        string temp = "";
        temp += "[";
        temp += name;
        temp += " , ";
        temp += "[";
        temp += weapon->getName();
        temp += " , ";
        temp += weapon->getDamage();
        temp += "]";
        temp += "[";
        temp += weapon2->getName();
        temp += " , ";
        temp += weapon2->getDamage();
        temp += "]";
        temp += "]";
        return temp;
    }
};

class Attacker {
private:
    vector<BaseFighter*> attacker;
    int size;
    int warrior_count;
    int wizard_count;
    int archer_count;
    int elf_count;
    int dragonball_count;

public:
    
    Attacker() {
        srand(time(0));

        warrior_count = 1000 * 0.35;
        wizard_count = 1000 * 0.35;
        archer_count = 1000 * 0.20;
        elf_count = 1000 * 0.05;
        dragonball_count = 1000 * 0.05;

        for (int i = 0; i < warrior_count; i++) {
            attacker.push_back(new Warrior);
        }
        for (int i = 0; i < archer_count; i++) {
            attacker.push_back(new Archer);
        }
        for (int i = 0; i < wizard_count; i++) {
            attacker.push_back(new Wizard);
        }
        for (int i = 0; i < elf_count; i++) {
            attacker.push_back(new Elf);
        }
        for (int i = 0; i < dragonball_count; i++) {
            attacker.push_back(new Dragonborn);
        }

        size = attacker.size();
        random_shuffle(attacker.begin(), attacker.end());
    }
    
    Attacker(int s) {
        srand(time(0));

        warrior_count = s * 0.35;
        wizard_count = s * 0.35;
        archer_count = s * 0.20;
        elf_count = s * 0.05;
        dragonball_count = s * 0.05;

        for (int i = 0; i < warrior_count; i++) {
            attacker.push_back(new Warrior);
        }
        for (int i = 0; i < archer_count; i++) {
            attacker.push_back(new Archer);
        }
        for (int i = 0; i < wizard_count; i++) {
            attacker.push_back(new Wizard);
        }
        for (int i = 0; i < elf_count; i++) {
            attacker.push_back(new Elf);
        }
        for (int i = 0; i < dragonball_count; i++) {
            attacker.push_back(new Dragonborn);
        }

        size = attacker.size();
        random_shuffle(attacker.begin(), attacker.end());
    }
    
    Attacker(ifstream& infile) {
        string fighter;
        infile >> fighter;

        while (!infile.eof()) {
            if (fighter == "Warrior") {
                warrior_count++;
            }
            else if (fighter == "Archer") {
                archer_count++;
            }
            else if (fighter == "Wizard") {
                wizard_count++;
            }
            else if (fighter == "Elf") {
                elf_count++;
            }
            else {
                dragonball_count++;
            }
            infile >> fighter;
        }

        for (int i = 0; i < warrior_count; i++) {
            attacker.push_back(new Warrior);
        }
        for (int i = 0; i < archer_count; i++) {
            attacker.push_back(new Archer);
        }
        for (int i = 0; i < wizard_count; i++) {
            attacker.push_back(new Wizard);
        }
        for (int i = 0; i < elf_count; i++) {
            attacker.push_back(new Elf);
        }
        for (int i = 0; i < dragonball_count; i++) {
            attacker.push_back(new Dragonborn);
        }

        size = attacker.size();
        random_shuffle(attacker.begin(), attacker.end());

    }
    
    BaseFighter& operator[](int index) {

        if (index > attacker.size()) {
            cout << "invalid index";
            return *attacker[0];

        }
        else {

            return *attacker[index];
        }
    }
    
    int Size() {
        return attacker.size();
    }
   
    void deletePlayer() {
        if (attacker.size() == 1) {
            attacker.pop_back();
        }
        else {
            attacker.erase(attacker.begin());
        }
    }
    
    void heal() {
        if (attacker.front()->getHP() < attacker.front()->getMaxHP()) {
            attacker.front()->setHP((int)(attacker.front()->getHP() + (attacker.front()->getHP() * attacker.front()->getRR())));
            if (attacker.front()->getHP() > attacker.front()->getMaxHP()) {
                attacker.front()->setHP(attacker.front()->getMaxHP());
            }
        }
    }
};

class Defender {
private:
    vector <BaseFighter*> defender;
    int size;

public:
   
    Defender() {
        size = 1000 / 100;
        int choice;

        for (int i = 0; i < size; i++) {
            choice = rand() % 5 + 1;

            if (choice == 1) {
                defender.push_back(new Warrior);
            }
            else if (choice == 2) {
                defender.push_back(new Wizard);
            }
            else if (choice == 3) {
                defender.push_back(new Archer);
            }
            else if (choice == 4) {
                defender.push_back(new Elf);
            }
            else {
                defender.push_back(new Dragonborn);
            }
        }

        size = defender.size();
        random_shuffle(defender.begin(), defender.end());
    }
    
    Defender(int n) {
        size = n / 100;
        int choice;

        for (int i = 0; i < size; i++) {
            choice = rand() % 5 + 1;

            if (choice == 1) {
                defender.push_back(new Warrior);
            }
            else if (choice == 2) {
                defender.push_back(new Wizard);
            }
            else if (choice == 3) {
                defender.push_back(new Archer);
            }
            else if (choice == 4) {
                defender.push_back(new Elf);
            }
            else {
                defender.push_back(new Dragonborn);
            }
        }

        size = defender.size();
        random_shuffle(defender.begin(), defender.end());
    }
    
    BaseFighter& operator[](int index) {

        if (index > defender.size()) {
            cout << "invalid index";
            return *defender[0];

        }
        else {

            return *defender[index];
        }
    }
   
    int Size() {
        return defender.size();
    }
    
    void deletePlayer(int i) {
        if (defender.size() == 1) {
            defender.pop_back();
        }
        else {
            if (i <= 0) {
                defender.erase(defender.begin());
            }
            else {
                defender.erase(defender.begin() + i);
            }

        }
    }
    
    void heal() {
        for (int i = 0; i < defender.size(); i++) {
            if (defender[i]->getHP() < defender[i]->getMaxHP()) {
                defender[i]->setHP((int)(defender[i]->getHP() + (defender[i]->getHP() * defender[i]->getRR())));
                if (defender[i]->getHP() > defender[i]->getMaxHP()) {
                    defender[i]->setHP(defender[i]->getMaxHP());
                }
            }
        }
    }
};

