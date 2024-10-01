#ifndef CARD_HPP
#define CARD_HPP

#include <string>

class Card {
private:
    int id;                  // Unique identifier for the card
    std::string description; // Description of the card
    int value;              // Value associated with the card (can be positive or negative)
    char cardType;
public:
    // Constructor
    Card(int cardId, const std::string& desc, int val, const char type );

    // Getters
    int getId() const;
    std::string getDescription() const;
    int getValue() const;
    char getType() const;
};

#endif // CARD_HPP
