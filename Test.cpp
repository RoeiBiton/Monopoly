#include <iostream>
#include <vector>
#include <cassert>
#include "player.hpp"

#include "board.hpp"
#include "property.hpp"
#include "card.hpp"

void testPlayerClass() {
    // Create a player
    Player player("Roei", 1);

    // Check initial values
    assert(player.getName() == "Roei");
    assert(player.getId() == 1);
    assert(player.getMoneyBalance() == 1500);
    assert(player.getPlaceOnBoard() == 0);
    assert(player.getOwnedProperties().empty());
    assert(player.getActive() == true);

    // Update player's money
    player.collectMoney(500);
    assert(player.getMoneyBalance() == 2000);

    // Test buying a property
    player.buyProperty(1);
    assert(player.getOwnedProperties().size() == 1);
    assert(player.getOwnedProperties()[0] == 1);

    // Test selling a property
    player.sellProperty(1);
    assert(player.getOwnedProperties().empty());

    // Test player going out of the game
    player.setOutOfTheGame();
    assert(player.getActive() == false);

    std::cout << "Player class tests passed." << std::endl;
}



void testPropertyAndBoardClass() {
    Board board;

    // Test: Check if properties are initialized correctly
    Property* property0 = board.getPropertyAtPosition(0);
    assert(property0 != nullptr);
    assert(property0->getName() == "Metulla");
    assert(property0->getId() == 0);
    assert(property0->getColor() == "BROWN");

    Property* property1 = board.getPropertyById(1);
    assert(property1 != nullptr);
    assert(property1->getName() == "Metualla");
    assert(property1->getColor() == "BROWN");

    // Test: Retrieve property that does not exist
    Property* nonexistentProperty = board.getPropertyAtPosition(999);
    assert(nonexistentProperty == nullptr);

    // Test: Draw Chance and Community Chest cards
    Card chanceCard = board.drawChanceCard();
    assert(chanceCard.getId() >= 0);
    assert(chanceCard.getId() <= 4); // Check that we only have 5 Chance cards

    Card communityCard = board.drawCommunityChestCard();    //Same just in community Cards
    assert(communityCard.getId() >= 0);
    assert(communityCard.getId() <= 4); // Check that we only have 5 Community Chest cards

    // Test: Push Chance and Community Chest cards
    board.pushChanceCard(chanceCard); // Push back the drawn Chance card
    board.pushCommunityChestCard(communityCard); // Push back the drawn Community Chest card

    // Test: Check if the cards can be drawn again
    Card newChanceCard = board.drawChanceCard();
    assert(newChanceCard.getId() == chanceCard.getId()); // The same card should be drawn again after pushing back

    Card newCommunityCard = board.drawCommunityChestCard();
    assert(newCommunityCard.getId() == communityCard.getId()); // The same card should be drawn again after pushing back

    // Test: Ownership checks
    Property* property2 = board.getPropertyAtPosition(6);
     Property* property3 = board.getPropertyAtPosition(8);
      Property* property4 = board.getPropertyAtPosition(9);

    property2->setOwner(1); // Set owner for testing
    assert(board.ownTheCity(property2, 1) == false); // Player 1 doesn't own all BLUE properties

    // Assume we mark other properties as owned by player 1
    property3->setOwner(1); // Player 1 owns this property

    property4->setOwner(1); // Player 1 owns this property

    // Now, check again if player 1 owns all BLUE properties
    assert(board.ownTheCity(property2, 1) == true); // Now player 1 owns all BLUE properties

    // Test: Same or less amount of houses
    property2->buildHouse();
    property2->buildHouse();

    property3->buildHouse();
    property3->buildHouse();
    property3->buildHouse();

    property4->buildHouse();
    property4->buildHouse();

    assert(board.sameOrLessAmountOfHouses(property2) == true); // Player 1 has less than 3 on property 3

    assert(board.sameOrLessAmountOfHouses(property3) == false); // All properties now have the same amount of houses

    std::cout << "Board class tests passed." << std::endl;
}




int main() {
    testPlayerClass();
    testPropertyAndBoardClass();


    std::cout << "All tests passed!" << std::endl;
    return 0;
}
