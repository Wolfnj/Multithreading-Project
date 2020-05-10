//
// Created by Nwolf on 2/10/2020.
//

#include <iostream>
#include "Knight.h"

int Knight::numOfKnights=0;

/**
 * No arg knight constructor
 * Set all name to empty string and rest to 0
 */
Knight::Knight() {
    setKnightName("");
    setKnightHp(0);
    setKnightBravery(0);
    setKnightAttackRate(0);
    setKnightDamage(0);
}

/**
 * Parameterized knight constructor
 * @param name - knight name
 * @param hp - knight health
 * @param bravery - knight Bravery
 * @param attackRate - knight rate of attack
 * @param damage - Kngiht damage
 */
Knight::Knight(string name, int hp, int bravery, int attackRate, int damage) {
    setKnightName(name);
    setKnightHp(hp);
    setKnightBravery(bravery);
    setKnightAttackRate(attackRate);
    setKnightDamage(damage);
}






Knight::Knight(const Knight &knight) {
    this->name = knight.getKnightName();
    this->hp = knight.getKnightHp();
    this->bravery = knight.getKnightBravery();
    this->attackRate = knight.getKnightAttackRate();
    this->damage = knight.getKnightDamage();
}






/**
 * Sets the knight's name
 * @param name
 */
void Knight::setKnightName(string name) {
    this -> name = name;
}

/**
 * Sets the knight's health
 * @param hp
 */
void Knight::setKnightHp(int hp) {
    this ->hp = hp;
}

/**
 * Sets the knight's bravery
 * @param bravery
 */
void Knight::setKnightBravery(int bravery) {
    if(bravery>=0){
        this -> bravery = bravery;
    } else{
        //cout << "Bravery cannot be less than zero, Will be set to 0 \n" ;
        this -> bravery = 0;
    }
}

/**
 * Sets the knight's attack rate
 * @param attackRate
 */
void Knight::setKnightAttackRate(int attackRate) {
    if(attackRate>=0){
        this -> attackRate = attackRate;
    } else{
        //cout << "Attack rate cannot be less than zero, Will be set to 0 \n" ;
        this -> attackRate = 0;
    }
}

/**
 * Set the knight's damage
 * @param damage
 */
void Knight::setKnightDamage(int damage) {
    if(damage>=0){
        this -> damage = damage;
    } else{
        //cout << "Damage cannot be less than zero, Will be set to 0 \n" ;
        this -> damage = 0;
    }
}

/**
 * Gets the knight's name
 * @return - knight name
 */
string Knight::getKnightName() const {
    return this -> name;
}

/**
 * Gets the knight's health
 * @return - knight health
 */
int Knight::getKnightHp() const  {
    return this -> hp;
}

/**
 * Gets the knight's bravery
 * @return - knight bravery
 */
int Knight::getKnightBravery() const  {
    return this -> bravery;
}

/**
 * Gets the knight's attack rate
 * @return - knight attack rate
 */
int Knight::getKnightAttackRate() const  {
    return this -> attackRate;
}

int Knight::getKnightDamage() const {
    return this -> damage;
}



int Knight::getKnightDamage()  {
    return this -> damage;
}


void Knight::incNumKnight() {
    numOfKnights += 1;
}


void Knight::decNumKnight() {
    numOfKnights -= 1;
}

void Knight::rabbitAttack(int rabbitAttackDamage) {
    setKnightHp(getKnightHp() - rabbitAttackDamage);

}





