//
// Created by Nwolf on 2/17/2020.
//

#ifndef HW2_RABBIT_H
#define HW2_RABBIT_H

#endif //HW2_RABBIT_H

// Uses C++ strings for convenience
#include <string>
// For the log file output
#include <fstream>
using namespace std;

class Rabbit {


private:
    Rabbit(int hp, int attackRate, int attackChance, int damage, int evasionChance);

    int hp;     //health as a whole number

    int attackRate;     //rate of attack as whole number of microseconds



    int bite;

    int quick;

    int throat;

    int weak;

    int strong;

    int damage;      //Damage for attack (weak and strong)


    int evasionChance;  //Chance of evasion

public:

    // Constructors
    // Default constructor
    Rabbit();

    // Overloaded Rabbit class  constructor
    Rabbit(int hp, int attackRate, int attackChance, int damage, double evasionChance);

    // Setters

    // Set health (hp)
    void setRabbitHp(int hp);

    // Set attack rate
    void setRabbitAttackRate(int attackRate);

    // Set attack chance
    void setRabbitBite(int bite);

    void setRabbitQuick(int quick);

    void setRabbitThroat(int throat);



    void setRabbitWeak(int weak);

    void setRabbitStrong(int strong);


    // Set evasion chance
    void setRabbitEvasion(int evasionChance);


    //Getters

    // Get health (hp)
    int getRabbitHp();

    // Get attack rate
    int getRabbitAttackRate();

    // Set attack chance
    int getRabbitBite();

    int getRabbitQuick();

    int getRabbitThroat();


    // Get damage
    int getRabbitStrong();

    int getRabbitWeak();

    // Get evasion chance
    int getRabbitEvasion();


    // knight attack
    void knightAttack(int Damage);



};