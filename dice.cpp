#include "dice.hpp"
#include <cstdlib>


//This class represent the dice, if in some wierd reason you want it not even with 6 numbers
Dice::Dice(){
    sides = 6;
}

//Roll the dice and give you a random number from the sides option
int Dice::rollDice(){

    int roll = 0;
    roll = arc4random_uniform(sides) + 1;

    return roll;
}
