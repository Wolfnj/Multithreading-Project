//
// Created by Nwolf on 2/17/2020.
//

#ifndef HW2_KNIGHT_H
#define HW2_KNIGHT_H

#endif //HW2_KNIGHT_H

// Uses C++ strings for convenience
#include <string>
// For the log file output
#include <fstream>
using namespace std;


class Knight {

private:

    string name;    //Name of knight

    int hp;     //hit points (Health) of knight

    int bravery; //bravery threshold of knight. when hp<=bravery knight will run away
    //bravery threshold must be less than starting hp

    int attackRate;    //rate of attack, whole number of microseconds


    int damage;      //damage per attack


public:

    //Current number of knights
    static int numOfKnights;

    void incNumKnight();

    void decNumKnight();

    // Constructors
    // Default constructor:
    Knight();

    Knight(const Knight &knight);

    // Overloaded knight class constructor
    Knight(string name, int hp, int bravery, int attackRate, int damage);

    // Setters

    // Set knight name
    void setKnightName(string name);

    // Set hp
    void setKnightHp(int hp);

    // Set bravery
    void setKnightBravery(int bravery);

    // Set attack rate
    void setKnightAttackRate(int attackRate);


    // Set damage
    void setKnightDamage(int damage);




    //Getters

    // Get knight name
    string getKnightName() const;

    // Get hp
    int getKnightHp() const;

    // Get bravery
    int getKnightBravery() const;

    // Get attack rate
    int getKnightAttackRate() const;

    int getKnightDamage() const;



    // Rabbit Attack
    void rabbitAttack(int rabbitAttackDamage);


    // Get damage
    int getKnightDamage();


    void setKnightAttackChance(int chance);
};


