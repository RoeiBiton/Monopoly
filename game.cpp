#include "game.hpp"
#include <QMessageBox>
#include <QString>
#include <iostream>
#include <QInputDialog>

Game::Game(const std::vector<Player>& players)
    : players(players), currentPlayerIndex(0), gameEnded(false) {}

void Game::startGame() {
    while (!gameEnded) {
        playTurn();
    }
}

void Game::playTurn() {
    Player& currentPlayer = players[currentPlayerIndex];
    if(!currentPlayer.isFreeParkedStatus()){
    std::cout << currentPlayer.getName() << "'s turn!\n";
    //check if prisoner and have a card and want to exit

    int roll1 = dice.rollDice();
    int roll2 = dice.rollDice(); // Roll two dice
    std::cout << currentPlayer.getName() << " rolled a " << roll1 << " and " << roll2 << "!\n";


    if(roll1 == roll2){
        currentPlayer.increaseDoubleCounter();
        currentPlayer.setIfPrisoner(false);
        currentPlayer.resetJailTurn();
    }else{
        currentPlayer.resetDoubleCounter();
    }
    // check if prisoner
    if(currentPlayer.isInPrison() && currentPlayer.getJailTurn()<2){
        currentPlayer.increaseJailTurn();
        currentPlayerIndex = (currentPlayerIndex + 1) % players.size(); // Move to the next player
    }
    else{
        int newPosition = (currentPlayer.getPlaceOnBoard() + roll1 + roll2) % 40; // Calculate new position
        /////
        currentPlayer.resetJailTurn();///to not forget in cards that send you to prison
        /////
        if(currentPlayer.getDoubleCounter()==3 || newPosition == 30){
            currentPlayer.resetJailTurn();
            currentPlayer.setPlaceOnBoard(10);//go to jail
            currentPlayer.setIfPrisoner(true);
            currentPlayer.resetDoubleCounter();
            currentPlayerIndex = (currentPlayerIndex + 1) % players.size(); // Move to the next player


        } else{

                if(currentPlayer.getPlaceOnBoard() > newPosition){
                    currentPlayer.collectMoney(200);//add 200 if derech zleha
                }

                currentPlayer.setPlaceOnBoard(newPosition);
                std::cout << currentPlayer.getName() << " moves to " << newPosition << ".\n";

                handleTile(currentPlayer, newPosition, roll1 + roll2);

                if(roll1!=roll2){
                     currentPlayerIndex = (currentPlayerIndex + 1) % players.size(); // Move to the next player
                }
            }
    }
    }else{
        currentPlayerIndex = (currentPlayerIndex + 1) % players.size(); // Move to the next player
        currentPlayer.setFreeParked(false);
    }
}

bool Game::isGameOver() const {
    return gameEnded;
}

void Game::endGame() {
    gameEnded = true;
}

void Game::handleTile(Player& player, int newPosition, int diceResult) {

    Property* property = board.getPropertyAtPosition(newPosition);
    if (property) {


        if (property->getOwner() == -1) { // Property is not owned
            int propertyPrice = property->getPropertyPrice();

            // Create a confirmation dialog
            QMessageBox::StandardButton reply;
            reply = QMessageBox::question(nullptr, "Buy Property",
                                          QString::fromStdString(player.getName()) + " can buy " +
                                              QString::fromStdString(property->getStreet()) +
                                              " for $" + QString::number(propertyPrice) + ".\nDo you want to buy it?",
                                          QMessageBox::Yes | QMessageBox::No);

            if (reply == QMessageBox::Yes) {
                if (player.getMoneyBalance() >= propertyPrice) {
                    // Proceed with buying the property
                    player.payToBank(propertyPrice);
                    property->setOwner(player.getId());
                    player.buyProperty(property->getId());
                    if(newPosition==5 || newPosition==15 || newPosition==25 || newPosition==35){
                        player.incTrainCounter();
                        updateTrainRent(player.getId(), player.getTrainCounter());
                        }


                    QMessageBox::information(nullptr, "Purchase Successful",
                                             QString::fromStdString(player.getName()) + " bought " +
                                                 QString::fromStdString(property->getStreet()) + "!");
                } else {
                    QMessageBox::warning(nullptr, "Insufficient Funds",
                                         QString::fromStdString(player.getName()) + " does not have enough money to buy " +
                                             QString::fromStdString(property->getStreet()) + ".");
                }
            } else {
                QMessageBox::information(nullptr, "Purchase Cancelled",
                                         QString::fromStdString(player.getName()) + " decided not to buy " +
                                             QString::fromStdString(property->getStreet()) + ".");
            }
        }

        else if (property->getOwner() != player.getId()) { // Player pays rent


            bool isPaid=false;
            int ownerId = property->getOwner();
            int rent = property->getRent();
            if(newPosition==12 || newPosition ==28){
                if(board.getPropertyAtPosition(12)->getOwner()==board.getPropertyAtPosition(28)->getOwner()){
                    rent =10 * diceResult;
                }
                else{
                    rent = 4*diceResult;
                }
            }
            while(!isPaid){
                if (player.getMoneyBalance() >= rent) {
                    // Transfer rent
                    ////
                    player.payToPlayer(players[ownerId], rent);///////
                    ////
                    QMessageBox::information(nullptr, "Rent Payment",
                                            QString::fromStdString(player.getName() + " paid $" + std::to_string(rent) +
                                                 " in rent to " + players[ownerId].getName()));
                    isPaid=true;
                } else {
                    if(player.haveNoProperties()){
                        isPaid =true;
                        int money = player.getMoneyBalance();
                        player.payToPlayer(players[ownerId], money);
                        player.setOutOfTheGame();
                    }
                    else{
                    // Not enough money; prompt to mortgage properties
                    QMessageBox::warning(nullptr, "Insufficient Funds",
                                        QString::fromStdString(player.getName() + " does not have enough money to pay rent of $" +
                                             std::to_string(rent) + ". Please mortgage properties."));

                    sellProperties(player);
                }
             }
        }

        }
        else if(property->getOwner() == player.getId()){
            if(newPosition!=5 && newPosition!=15 && newPosition!=25 && newPosition!=35 && newPosition!=12 && newPosition!=28){
                if(board.ownTheCity(property, player.getId())&& board.sameOrLessAmountOfHouses(property)&& player.getMoneyBalance()>=property->getHousePrice()){
                    if(property->getHouseAmount()<4){
                        //ask if want to buy a house
                        buyHouse(property, player);


                    } else if(property->getHouseAmount()==4 && player.getMoneyBalance()>=(4*property->getHousePrice()+100)){
                        //ask if want to buy a hotel
                        buyHotel(property, player);

                    }
                }
            }

        }




    }else{
        bool isPaid = false;
        switch(newPosition){
        case 0:
            player.collectMoney(200);
        case 2: case 17: case 33:
            //draw teivat mazal
        case 7: case 22: case 26:
            //draw chance
        case 20:
            player.setFreeParked(true);
        case 4:
            // pay 200
            isPaid=false;
            while(!isPaid){
                 if(player.getMoneyBalance()>=200){
                    isPaid=true;
                    player.payToBank(200);
                 } else{
                     sellProperties(player);
                 }
            }
        case 38:
            //pay 100
            isPaid=false;
            while(!isPaid){
                if(player.getMoneyBalance()>=100){
                    isPaid=true;
                    player.payToBank(100);
                } else{
                    sellProperties(player);

        }

    }
}
    }
}






void Game::sellProperties(Player& player) {
    QStringList propertiesToMortgage; // List to store property names for dialog
    std::vector<int> ownedProperties = player.getOwnedProperties();

    // Collect property names
    for (int propertyId : ownedProperties) {
        if (!player.getOwnedProperties().empty()) { // Assuming -1 indicates property is not owned
            Property* property = board.getPropertyById(propertyId); // Assume you have a method to get property by ID
            if (property) {
                propertiesToMortgage << QString::fromStdString(property->getCity() + " " + property->getStreet());
            }
        }
    }

    // Ask the player to select properties to mortgage
    bool ok;
    QString selectedProperty = QInputDialog::getItem(nullptr, "Select Property to Mortgage",
                                                     "Select one:",
                                                     propertiesToMortgage, 0, false, &ok);

    if (ok && !selectedProperty.isEmpty()) {
        // Find the property ID based on the selected name
        for (int propertyId : ownedProperties) {
            Property* property = board.getPropertyById(propertyId);
            if (property && selectedProperty == QString::fromStdString(property->getCity() + " " + property->getStreet())) {
                // Mortgage the property
                int mortgageAmount = property->getPropertyMortgage(); // Get mortgage value
                player.collectMoney(mortgageAmount); // Add mortgage amount to player
                player.sellProperty(propertyId); // Mark the property as not owned
                property->resetProperty();
                int propertyPos = property->getPosition();
                if(propertyPos==5 || propertyPos==15 || propertyPos==25 || propertyPos==35){
                    player.decTrainCounter();
                    updateTrainRent(player.getId(), player.getTrainCounter());
                }


                // Inform the player
                QMessageBox::information(nullptr, "Property Mortgaged",
                                         QString::fromStdString(player.getName() + " mortgaged " + property->getCity() + " " + property->getStreet() +
                                                                " for $" + std::to_string(mortgageAmount) + "."));

                break; // Exit loop after finding and mortgaging the property
            }
        }
    }
}

void Game::buyHouse(Property* property, Player& player){
    player.payToBank(property->getHousePrice());
    property->buildHouse();
    ///implement by amount of houses and set actual rent

}
void Game::buyHotel(Property* property, Player& player){
    player.payToBank((property->getHousePrice()*4) + 100);
    property->buildHouse();
    ///implement by amount of houses and set actual rent

}
void Game::updateTrainRent(int playerId, int trainCounter){
    Property* pub1 = board.getPropertyAtPosition(5);
    Property* pub2 = board.getPropertyAtPosition(15);
    Property* pub3 = board.getPropertyAtPosition(25);
    Property* pub4 = board.getPropertyAtPosition(35);
    switch(trainCounter){
    case 1:
        if(pub1->getId()==playerId){pub1->setRent(25);}
        if(pub2->getId()==playerId){pub2->setRent(25);}
        if(pub3->getId()==playerId){pub3->setRent(25);}
        if(pub4->getId()==playerId){pub4->setRent(25);}
    case 2:
        if(pub1->getId()==playerId){pub1->setRent(50);}
        if(pub2->getId()==playerId){pub2->setRent(50);}
        if(pub3->getId()==playerId){pub3->setRent(50);}
        if(pub4->getId()==playerId){pub4->setRent(50);}
    case 3:
        if(pub1->getId()==playerId){pub1->setRent(100);}
        if(pub2->getId()==playerId){pub2->setRent(100);}
        if(pub3->getId()==playerId){pub3->setRent(100);}
        if(pub4->getId()==playerId){pub4->setRent(100);}
    case 4:
        if(pub1->getId()==playerId){pub1->setRent(200);}
        if(pub2->getId()==playerId){pub2->setRent(200);}
        if(pub3->getId()==playerId){pub3->setRent(200);}
        if(pub4->getId()==playerId){pub4->setRent(200);}
    }

}


