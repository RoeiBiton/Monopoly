// Board.hpp
#ifndef BOARD_HPP
#define BOARD_HPP

#include <vector>
#include "property.hpp"
#include "card.hpp"

class Board {
private:
    std::vector<Property> properties;           // All properties on the board
    std::vector<Card> chanceCards;              // Chance cards
    std::vector<Card> communityChestCards;      // Community Chest cards

public:
    Board(); // Constructor
    Property* getPropertyAtPosition(int position); // Get property by position
    Property* getPropertyById(int id);
    Card drawChanceCard();                        // Draw a Chance card
    Card drawCommunityChestCard();                // Draw a Community Chest card
    bool ownTheCity(Property* currentProperty, int ownerId);
    bool sameOrLessAmountOfHouses(Property* currentProperty);
};

#endif // BOARD_HPP
