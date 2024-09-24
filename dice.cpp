#include "dice.hpp"
#include <cstdlib>

Dice::Dice(){
    sides = 6;
}

int Dice::rollDice(){

    int roll = 0;
    roll = arc4random_uniform(sides) + 1;

    return roll;
}
