#ifndef CARD_HPP
#define CARD_HPP

#include <string>

class Card {
private:
    int id;                  // Unique identifier for the card
    std::string description; // Description of the card
    int value;              // Value associated with the card (can be positive or negative)
    bool isDrawn;           // Flag to indicate if the card has been drawn

public:
    // Constructor
    Card(int cardId, const std::string& desc, int val);

    // Getters
    int getId() const;
    std::string getDescription() const;
    int getValue() const;
    bool getIsDrawn() const;

    // Setters
    void setDrawn(bool drawn); // Set the isDrawn flag
};

#endif // CARD_HPP
