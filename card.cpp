/**
 * Created by Roei Biton
 * Gmail: roei.biton33@gmail.com
 * */
#include "card.hpp"

// Constructor
Card::Card(int cardId, const std::string& desc, int val, char type)
    : id(cardId), description(desc), value(val), cardType(type) {}

// Getters
int Card::getId() const {
    return id;
}

std::string Card::getDescription() const {
    return description;
}

char Card::getType() const {
    return cardType;
}

int Card::getValue() const {
    return value;
}



