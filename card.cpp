#include "card.hpp"

// Constructor
Card::Card(int cardId, const std::string& desc, int val)
    : id(cardId), description(desc), value(val), isDrawn(false) {}

// Getters
int Card::getId() const {
    return id;
}

std::string Card::getDescription() const {
    return description;
}

int Card::getValue() const {
    return value;
}

bool Card::getIsDrawn() const {
    return isDrawn;
}

// Setters
void Card::setDrawn(bool drawn) {
    isDrawn = drawn;
}
