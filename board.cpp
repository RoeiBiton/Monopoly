#include "board.hpp"
#include "property.hpp"
#include <cstdlib>

// Define the properties based on the standard Monopoly board
Board::Board() {
    properties.push_back(Property(0, "Metulla", "Harishonim", 1, 2, 60, 50, "BROWN"));
    properties.push_back(Property(1, "Metualla", "Har Zfia", 3, 4, 60, 50, "BROWN"));

    properties.push_back(Property(2, "Kfar Yuval", "Harimon", 6, 6, 100, 50, "BLUE"));
    properties.push_back(Property(3, "Kfar Yuval", "Hashaked", 8, 6, 100, 50, "BLUE"));
    properties.push_back(Property(4, "Kfar Yuval", "Hazait", 9, 8, 100, 50, "BLUE"));

    properties.push_back(Property(5, "Kfar Blum", "Derech Rakefet", 11, 10, 140, 100, "PINK"));
    properties.push_back(Property(6, "Kfar Blum", "Derech Hermon", 13, 10, 140, 100, "PINK"));
    properties.push_back(Property(7, "Kfar Blum", "Derech Snir", 14, 12, 160, 100, "PINK"));

    properties.push_back(Property(8, "Dafna", "Derech Hazeitim", 16, 14, 180, 100, "ORANGE"));
    properties.push_back(Property(9, "Dafna", "Derech Hapardes", 18, 14, 180, 100, "ORANGE"));
    properties.push_back(Property(10, "Dafna", "Tayelet Hanahal", 19, 16, 200, 100, "ORANGE"));

    properties.push_back(Property(11, "Shaar Yeshuv", "Pilgey Maim", 21, 18, 220, 150, "RED"));
    properties.push_back(Property(12, "Shaar Yeshuv", "Tal", 23, 18, 220, 150, "RED"));
    properties.push_back(Property(13, "Shaar Yeshuv", "Nehalim", 24, 20, 240, 150, "RED"));

    properties.push_back(Property(14, "Beit Hillel", "Hadolev", 26, 22, 260, 150, "YELLOW"));
    properties.push_back(Property(15, "Beit Hillel", "Hazeitim", 27, 22, 260, 150, "YELLOW"));
    properties.push_back(Property(16, "Beit Hillel", "Hahadarim", 29, 24, 280, 150, "YELLOW"));

    properties.push_back(Property(17, "Kiryat Shemona", "Havradim", 31, 26, 300, 200, "GREEN"));
    properties.push_back(Property(18, "Kiryat Shemona", "Bimat Tel-Hai", 32, 26, 300, 200, "GREEN"));
    properties.push_back(Property(19, "Kiryat Shemona", "Yuvalim", 34, 28, 320, 200, "GREEN"));

    properties.push_back(Property(20, "Hagoshrim", "Erez", 37, 35, 350, 200, "NAVY"));
    properties.push_back(Property(21, "Hagoshrim", "Yarden", 39, 50, 400, 200, "NAVY"));

    properties.push_back(Property(22, "Pub", "Hakura", 5, 25, 200, -1, "BLACK"));
    properties.push_back(Property(23, "Pub", "Pubos", 15, 25, 200, -1, "BLACK"));
    properties.push_back(Property(24, "Pub", "Hapitriya", 25, 25, 200, -1, "BLACK"));
    properties.push_back(Property(25, "Pub", "Darma", 35, 25, 200, -1, "BLACK"));

    properties.push_back(Property(26, "Hevrat", "Hahashmal", 12, 0, 150, -1, "SILVER"));
    properties.push_back(Property(27, "Hevrat", "Hamaim", 28, 0, 150, -1, "SILVER"));


    // Initialize Chance cards
    chanceCards.push_back(Card(1, "Advance to Go (Collect $200)", 200));
    chanceCards.push_back(Card(2, "Go to Jail", -1));
    // ... (other Chance cards)

    // Initialize Community Chest cards
    communityChestCards.push_back(Card(1, "Advance to Go (Collect $200)", 200));
    communityChestCards.push_back(Card(2, "Get Out of Jail Free", 0));
    // ... (other Community Chest cards)
}

Property* Board::getPropertyAtPosition(int position) {
    for (Property& property : properties) {
        if (property.getPosition() == position) {
            return &property;
        }
    }
    return nullptr; // No property at this position
}

Property* Board::getPropertyById(int id) {
    for (Property& property : properties) {
        if (property.getId() == id) {
            return &property;
        }
    }
    return nullptr; // No property at this position
}

Card Board::drawChanceCard() {
    // Implement logic to draw a Chance card (randomly, for example)
    int index = arc4random() % chanceCards.size();
    Card card = chanceCards[index];
    chanceCards.erase(chanceCards.begin() + index); // Remove drawn card from deck
    return card;
}

Card Board::drawCommunityChestCard() {
    // Implement logic to draw a Community Chest card (randomly, for example)
    int index = arc4random() % communityChestCards.size();
    Card card = communityChestCards[index];
    communityChestCards.erase(communityChestCards.begin() + index); // Remove drawn card from deck
    return card;
}

bool Board::ownTheCity(Property* currentProperty, int ownerId){
    for(Property& property : properties){
        if(property.getColor()==currentProperty->getColor() && property.getOwner()!=ownerId){
            return false;
        }
    }
    return true;
}

bool Board::sameOrLessAmountOfHouses(Property* currentProperty){
    int amount = currentProperty->getHouseAmount();
    for(Property& property : properties){
        if(property.getColor()==currentProperty->getColor() && property.getHouseAmount()<amount){
            return false;
        }
    }
    return true;
}
