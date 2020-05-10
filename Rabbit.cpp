//
// Created by Nwolf on 2/10/2020.
//

#include <iostream>
#include "Rabbit.h"

/**
 * No arg Rabbit Constructor
 * Just set all params to zero
 */
Rabbit::Rabbit() {
    setRabbitHp(0);
    setRabbitAttackRate(0);

    setRabbitBite(0);
    setRabbitQuick(0);
    setRabbitThroat(0);

    setRabbitWeak(0);
    setRabbitStrong(0);


    setRabbitEvasion(0);
}

/**
 * Parameterized Rabbits Constructor
 * @param hp - Health
 * @param attackRate - Rate of attack by rabbit
 * @param attackChance - Chance to hit per attack
 * @param damage - Damage per attack (weak or strong)
 * @param evasionChance -Chance the rabbit will evade the attack
 */
Rabbit::Rabbit(int hp, int attackRate, int attackChance, int damage, int evasionChance) {
    setRabbitHp(hp);
    setRabbitAttackRate(attackRate);

    setRabbitEvasion(evasionChance);
}

/**
 * Sets the Rabbit's Health
 * @param hp - Health
 */
void Rabbit::setRabbitHp(int hp) {
        this -> hp = hp;
}

/**
 * Sets the Rabbit's rate of attack
 * @param attackRate
 */
void Rabbit::setRabbitAttackRate(int attackRate) {
    if(attackRate>=0){
        this -> attackRate = attackRate;
    } else{
        cout << "attack rate cannot be less than zero, Will be set to 0 \n" ;
        this -> attackRate = 0;
    }
}


/**
 * Sets the Rabbit's bite
 * @param bite
 */
void Rabbit::setRabbitBite(int bite) {
    if(bite>=0){
        this -> bite = bite;
    } else{
        cout << "attack chance cannot be less than zero, Will be set to 0 \n" ;
        this -> bite = 0;
    }
}


/**
 * Sets the Rabbit's quick
 * @param bite
 */
void Rabbit::setRabbitQuick(int quick) {
    if(quick>=0){
        this -> quick = quick;
    } else{
        cout << "attack chance cannot be less than zero, Will be set to 0 \n" ;
        this -> quick = 0;
    }
}


/**
 * Sets the Rabbit's throat
 * @param throat
 */
void Rabbit::setRabbitThroat(int throat) {
    if(throat>=0){
        this -> throat = throat;
    } else{
        cout << "attack chance cannot be less than zero, Will be set to 0 \n" ;
        this -> throat = 0;
    }
}


/**
 * Sets the Rabbit's weak
 * @param bite
 */
void Rabbit::setRabbitWeak(int weak) {
    if(weak>=0){
        this -> weak = weak;
    } else{
        cout << "attack chance cannot be less than zero, Will be set to 0 \n" ;
        this -> weak = 0;
    }
}



/**
 * Sets the Rabbit's strong
 * @param bite
 */
void Rabbit::setRabbitStrong(int strong) {
    if(strong>=0){
        this -> strong = strong;
    } else{
        cout << "attack chance cannot be less than zero, Will be set to 0 \n" ;
        this -> strong = 0;
    }
}




/**
 * Sets Rabbit's chance of evasion of attack
 * @param evasionChance
 */
void Rabbit::setRabbitEvasion(int evasionChance) {
    if(evasionChance>=0){
        this -> evasionChance = evasionChance;
    } else{
        cout << "evasionDamage cannot be less than zero, Will be set to 0 \n" ;
        this -> evasionChance = 0;
    }
}

/**
 * Gets the Rabbit's HP
 * @return Rabbit Health
 */
int Rabbit::getRabbitHp() {
    return this -> hp;
}

/**
 * Gets Rabbit's attack rate
 * @return Rabbit attack rate
 */
int Rabbit::getRabbitAttackRate() {
    return this -> attackRate;
}



/**
 * Gets Rabbit's evasion chance
 * @return Rabbit evasion chance
 */
int Rabbit::getRabbitEvasion() {
    return this -> evasionChance;
}

int Rabbit::getRabbitBite() {
    return this-> bite;
}

int Rabbit::getRabbitQuick() {
    return this-> quick;
}

int Rabbit::getRabbitThroat() {
    return this-> throat;
}



int Rabbit::getRabbitStrong(){
    return this-> strong;
}

int Rabbit::getRabbitWeak(){
    return this-> weak;
}

void Rabbit::knightAttack(int Damage) {

    setRabbitHp(getRabbitHp() - Damage);

}
