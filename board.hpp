// Board.hpp
#ifndef BOARD_HPP
#define BOARD_HPP

#include <vector>
#include <queue>
#include "property.hpp"
#include "card.hpp"

// Class representing the game board
class Board {
private:
    std::vector<Property> properties;           // All properties on the board
    std::queue<Card> chanceCards;               // Queue for Chance cards
    std::queue<Card> communityChestCards;       // Queue for Community Chest cards

public:
    Board(); // Constructor to initialize the board

    // Method to get a property by its position on the board
    Property* getPropertyAtPosition(int position);

    // Method to get a property by its ID
    Property* getPropertyById(int id);

    // Method to draw a Chance card
    Card drawChanceCard();

    // Method to draw a Community Chest card
    Card drawCommunityChestCard();

    // Method to check if a player owns all properties of a specific color
    bool ownTheCity(Property* currentProperty, int ownerId);

    // Method to check if a player has the same or fewer houses than other properties of the same color
    bool sameOrLessAmountOfHouses(Property* currentProperty);

    // Method to push a Chance card back into the deck
    void pushChanceCard(Card& card);

    // Method to push a Community Chest card back into the deck
    void pushCommunityChestCard(Card& card);
};

#endif // BOARD_HPP
