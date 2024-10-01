#include "game.hpp"
#include <QMessageBox>
#include <QString>
#include <iostream>
#include <QInputDialog>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include "card.hpp"

/**
 * Constructs a Game instance with the provided players and graphics scene.
 *
 * @param players A vector of Player objects participating in the game.
 * @param scene The QGraphicsScene where the game will be displayed.
 */
Game::Game(const std::vector<Player>& players, QGraphicsScene* scene)
    : players(players), currentPlayerIndex(0), gameEnded(false), houseIcons(200, nullptr), scene(scene) {

    const int MAX_LOGO_WIDTH = 30;
    const int MAX_LOGO_HEIGHT = 30;



    for (size_t i = 0; i < players.size(); ++i) {
        // Load logos for each player
        QString logoPath = "/Users/roeibiton/QtProjects/Monopoly/player" + QString::number(i + 1) + "_logo.png";
        QPixmap logoPixmap(logoPath);

        if (logoPixmap.isNull()) {
            QMessageBox::warning(nullptr, "Error", "Failed to load logo for Player " + QString::number(i + 1));
            return; // Exit if a logo fails to load
        } else {
            qDebug() << "Loaded logo for Player" << i + 1; // Debug message
        }

        // Scale the logo
        logoPixmap = logoPixmap.scaled(MAX_LOGO_WIDTH, MAX_LOGO_HEIGHT, Qt::KeepAspectRatio, Qt::SmoothTransformation);

        // Create a QGraphicsPixmapItem for the player logo and add it to the scene
        QGraphicsPixmapItem* playerIcon = scene->addPixmap(logoPixmap);
        playerIcon->setZValue(1); // Ensure logos are on top
        playerIcons.push_back(playerIcon); // Store the icon in the vector

        // Set the position for the player logo on the board
        playerIcon->setPos(720 + (i * 2), 728 + (i*2));
    }
}


/**
 * Starts the game loop, allowing players to take turns until the game ends.
 */
void Game::startGame() {
    while (!gameEnded) {
        playTurn();
        isGameOver();
    }
}

/**
 * Manages a single turn for the current player, including rolling dice,
 * moving, and handling various game events.
 */
void Game::playTurn() {
    Player& currentPlayer = players[currentPlayerIndex];
    if(currentPlayer.getActive()){
        GUIShowMessage("Its " + currentPlayer.getName() + " turn!");

        buildHouseOnProperty(currentPlayer);
        if(!currentPlayer.isFreeParkedStatus()){
        std::cout << currentPlayer.getName() << "'s turn!\n";



         handleJailCard(currentPlayer);     //check if prisoner and have a card and want to exit

        GUIShowMessage(currentPlayer.getName() + ", Please throw the dices.");

        int roll1 = dice.rollDice();
        int roll2 = dice.rollDice(); // Roll two dice
        std::cout << currentPlayer.getName() << " rolled a " << roll1 << " and " << roll2 << "!\n";



        if(roll1 == roll2){
            GUIShowMessage("Double ! You got " + std::to_string(roll1) + " and " + std::to_string(roll2) + "!");
            currentPlayer.increaseDoubleCounter();
            currentPlayer.setIfPrisoner(false);
            currentPlayer.resetJailTurn();
        }else{
            GUIShowMessage("You got " + std::to_string(roll1) + " and " + std::to_string(roll2) + "!");
            currentPlayer.resetDoubleCounter();
        }
        // check if prisoner
        if(currentPlayer.isInPrison() && currentPlayer.getJailTurn()<2){
            GUIShowMessage("No double, you staying another turn in the jail ! this is your " + std::to_string(currentPlayer.getJailTurn()+1) + "/3");
            currentPlayer.increaseJailTurn();
            currentPlayerIndex = (currentPlayerIndex + 1) % players.size(); // Move to the next player
        }
        else{
            int newPosition = (currentPlayer.getPlaceOnBoard() + roll1 + roll2) % 40; // Calculate new position

            if(currentPlayer.getDoubleCounter()==3 || newPosition == 30){
                if(newPosition==30){
                    GUIShowMessage("Go to jail ! And dont get 200 Shekels !");
                }
                if(currentPlayer.getDoubleCounter()==3){
                    GUIShowMessage("Its your third double in a row ! Go to jail and dont get 200 Shekels !");
                }
                currentPlayer.resetJailTurn();
                currentPlayer.setPlaceOnBoard(10);//go to jail
                GUIupdatePlayerPosition(currentPlayer);
                currentPlayer.setIfPrisoner(true);
                currentPlayer.resetDoubleCounter();
                currentPlayerIndex = (currentPlayerIndex + 1) % players.size(); // Move to the next player


            } else{


                    handleTile(currentPlayer, newPosition, roll1 + roll2);

                    if(roll1!=roll2){
                         currentPlayerIndex = (currentPlayerIndex + 1) % players.size(); // Move to the next player
                    }
                    if(roll1==roll2){
                         GUIShowMessage("Remember your double? because you have got another turn !");
                    }
                }
        }
        }else{
            currentPlayerIndex = (currentPlayerIndex + 1) % players.size(); // Move to the next player
            GUIShowMessage(currentPlayer.getName() + " is in Free Parking, turn move on !");
            currentPlayer.setFreeParked(false);
        }
    }
    else{
    currentPlayerIndex = (currentPlayerIndex + 1) % players.size(); // Move to the next player
    }
}

/**
 * Checks if the game is over, meaning only one player remains active.
 *
 * @return True if the game has ended; otherwise, false.
 */
bool Game::isGameOver() {
    int counter = 0;
    for (Player& player : this->players){
        if(player.getMoneyBalance()>=4000){
            GUIShowMessage(player.getName() + " Won the game !");
             gameEnded=true;
        }
        if(player.getActive()){
            counter++;
        }
    }
    if(counter==1){
        for (Player& wonPlayer : this->players){
            if(wonPlayer.getActive()){
               GUIShowMessage(wonPlayer.getName() + " Won the game !");
            }
        }
        gameEnded=true;
    }
    return gameEnded;
}

/**
 * Ends the game.
 */
void Game::endGame() {
    gameEnded = true;
}

/**
 * Handles a player landing on a tile, including passing Derech Zleha, purchasing properties,
 * paying rent, or drawing cards.
 *
 * @param player The player who has landed on the tile.
 * @param newPosition The new position of the player on the board.
 * @param diceResult The total result of the dice roll.
 */
void Game::handleTile(Player& player, int newPosition, int diceResult) {

    if(player.getPlaceOnBoard() > newPosition){
        player.collectMoney(200);//add 200 if derech zleha
        GUIShowMessage("You passed through Derech Zleha. You deserve 200 Shekels !");
    }

    player.setPlaceOnBoard(newPosition);
    GUIupdatePlayerPosition(player);
    std::cout << player.getName() << " moves to " << newPosition << ".\n";


    Property* property = board.getPropertyAtPosition(newPosition);
    if (property) {
        GUIShowMessage(player.getName() + ", You have landed on " + board.getPropertyAtPosition(newPosition)->getName());


        if (property->getOwner() == -1) { // Property is not owned
            handlePropertyPurchase(player, property, newPosition);
        }

        else if (property->getOwner() != player.getId()) { // Player pays rent

            handleRentPayment(player, property, diceResult); //handle the tile case
        }
        else if(property->getOwner() == player.getId()) {
            handlePropertyDevelopement(player, property, newPosition);
        }






    }else{

        switch(newPosition){
        case 0:
            GUIShowMessage("You have landed exactly on Derech zleha ! get 400 Shekels !");
            player.collectMoney(200);
            break;
        case 2: case 17: case 33:
            GUIShowMessage("You have landed on Community Chest Card !");
            takeCommunityChestCard(player, newPosition, diceResult);
            break;

        case 7: case 22: case 26:
            GUIShowMessage("You have landed on Chance Card !");
            takeChanceCard(player, newPosition, diceResult);

             break;
        case 20:
            GUIShowMessage("You have landed on Free Parking, you might wanna rest the next turn, Enjoy your Coffee !");
            player.setFreeParked(true);
             break;
        case 4:
            // pay 200
            GUIShowMessage("You have landed on Mas Hahnasa ! Please pay 200 Shekels.");
            chargeTax(player, 200);
             break;
        case 38:
            //pay 100
            GUIShowMessage("You have landed on Mas Hahnasa ! Please pay 100 Shekels.");
            chargeTax(player, 100);
             break;
        case 10:
            GUIShowMessage("Stay calm ! you have landed on free pass, not jail.");
            break;
    }
}
}

/**
 * Allows a player to sell (mortgage) properties they own to raise money.
 * Displays a dialog for the player to select which property to mortgage.
 *
 * @param player The player who wants to mortgage their properties.
 */
void Game::sellProperties(Player& player) {
    QStringList propertiesToMortgage; // List to store property names for dialog
    std::vector<int> ownedProperties = player.getOwnedProperties();

    // Collect property names
    for (int propertyId : ownedProperties) {
        if (!player.getOwnedProperties().empty()) { // Check if the player has properties
            Property* property = board.getPropertyById(propertyId); // Get property by ID
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
                /////////
                GUIdeleteHouses(propertyPos);
                //////////////
                if (propertyPos == 5 || propertyPos == 15 || propertyPos == 25 || propertyPos == 35) {
                    player.decTrainCounter();
                    updateAllTrainRent(player.getId(), player.getTrainCounter());
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

/**
 * Allows a player to buy a house for a property, deducting the cost from their balance.
 *
 * @param property The property for which the house is being purchased.
 * @param player The player who is buying the house.
 */
void Game::buyHouse(Property* property, Player& player) {
    player.payToBank(property->getHousePrice());
    property->buildHouse();
}

/**
 * Allows a player to buy a hotel for a property, deducting the cost from their balance.
 *
 * @param property The property for which the hotel is being purchased.
 * @param player The player who is buying the hotel.
 */
void Game::buyHotel(Property* property, Player& player) {
    player.payToBank((property->getHousePrice() * 4) + 100);
    property->buildHouse();
    /// Implement by amount of houses and set actual rent
}

/**
 * Updates the rent values for all train properties owned by a player.
 *
 * @param playerId The ID of the player whose train properties are being updated.
 * @param trainCounter The number of train properties owned by the player.
 */
void Game::updateAllTrainRent(int playerId, int trainCounter) {
    board.getPropertyAtPosition(5)->updateTrainRent(playerId, trainCounter);
    board.getPropertyAtPosition(15)->updateTrainRent(playerId, trainCounter);
    board.getPropertyAtPosition(25)->updateTrainRent(playerId, trainCounter);
    board.getPropertyAtPosition(35)->updateTrainRent(playerId, trainCounter);
}

/**
 * Handles the payment of rent when a player lands on a property owned by another player.
 *
 * @param player The player who is paying rent.
 * @param property The property for which rent is being paid.
 * @param diceResult The result of the dice roll used to determine rent calculation to Hevrat Hashmal and Hevrat Hamaim.
 */
void Game::handleRentPayment(Player& player, Property* property, int diceResult) {
    int ownerId = property->getOwner();
    int rent = property->getRent();

    if (property->getPosition() == 12 || property->getPosition() == 28) {
        if (board.getPropertyAtPosition(12)->getOwner() == board.getPropertyAtPosition(28)->getOwner()) {
            rent = 10 * diceResult;
        } else {
            rent = 4 * diceResult;
        }
    }

    bool isPaid = false;
    while (!isPaid) {
        if (player.getMoneyBalance() >= rent) {
            player.payToPlayer(players[ownerId], rent);
            QMessageBox::information(nullptr, "Rent Payment",
                                     QString::fromStdString(player.getName() + " paid $" + std::to_string(rent) +
                                                            " in rent to " + players[ownerId].getName() + " \n his money balance now is: " + std::to_string(player.getMoneyBalance())));
            isPaid = true;
        } else {
            if (player.haveNoProperties()) {
                player.payToPlayer(players[ownerId], player.getMoneyBalance());
                player.setOutOfTheGame();
                QGraphicsPixmapItem* playerIcon = playerIcons[player.getId()];
                playerIcon->setPos(400 + player.getId() * 5, 400);
                GUIShowMessage("You have no more properties to sell and not enough money to pay. You are out of the game.");
                isPaid = true;
            } else {
                QMessageBox::warning(nullptr, "Insufficient Funds",
                                     QString::fromStdString(player.getName() + " does not have enough money to pay rent of $" +
                                                            std::to_string(rent) + ". Please mortgage properties."));
                sellProperties(player);
            }
        }
    }
}

/**
 * Handles the purchase of a property by a player, confirming the purchase through a dialog.
 *
 * @param player The player who wants to buy the property.
 * @param property The property being purchased.
 * @param newPosition The position of the property on the board.
 */
void Game::handlePropertyPurchase(Player& player, Property* property, int newPosition) {
    int propertyPrice = property->getPropertyPrice();
    if (player.getMoneyBalance() >= propertyPrice) {
        // Create a confirmation dialog
        QMessageBox::StandardButton reply;
        reply = QMessageBox::question(nullptr, "Buy Property",
                                      QString::fromStdString(player.getName()) + " can buy " +
                                          QString::fromStdString(property->getCity() + " " + property->getStreet()) +
                                          " for $" + QString::number(propertyPrice) + ".\nDo you want to buy it? \nYour money balance now is: " + QString::number(player.getMoneyBalance()),
                                      QMessageBox::Yes | QMessageBox::No);

        if (reply == QMessageBox::Yes) {
            if (player.getMoneyBalance() >= propertyPrice) {
                // Proceed with buying the property
                player.payToBank(propertyPrice);
                property->setOwner(player.getId());
                player.buyProperty(property->getId());
                if (newPosition == 5 || newPosition == 15 || newPosition == 25 || newPosition == 35) {
                    player.incTrainCounter();
                    updateAllTrainRent(player.getId(), player.getTrainCounter());
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
}

/**
 * Handles the development of a property by allowing a player to buy houses or hotels.
 *
 * @param player The player who wants to develop the property.
 * @param property The property being developed.
 * @param newPosition The position of the property on the board.
 */
void Game::handlePropertyDevelopement(Player& player, Property* property, int newPosition) {
    if (newPosition != 5 && newPosition != 15 && newPosition != 25 && newPosition != 35 && newPosition != 12 && newPosition != 28) {
        if (board.ownTheCity(property, player.getId()) && board.sameOrLessAmountOfHouses(property) && player.getMoneyBalance() >= property->getHousePrice()) {
            if (property->getHouseAmount() < 4) {
                // Ask if the player wants to buy a house
                QMessageBox::StandardButton reply;
                reply = QMessageBox::question(nullptr, "Buy House",
                                              QString("%1 Do you want to buy a house on %2, %3 for %4? your money balance now is: %5")
                                                  .arg(QString::fromStdString(player.getName()),
                                                       QString::fromStdString(property->getCity()),
                                                       QString::fromStdString(property->getStreet()),
                                                       QString::number(property->getHousePrice()),
                                                       QString::number(player.getMoneyBalance())),
                                              QMessageBox::Yes | QMessageBox::No);

                if (reply == QMessageBox::Yes) {
                    buyHouse(property, player);
                    GUIhouseCreate(newPosition, property->getHouseAmount());
                }

            } else if (property->getHouseAmount() == 4 && player.getMoneyBalance() >= (4 * property->getHousePrice() + 100)) {
                // Ask if the player wants to buy a hotel
                QMessageBox::StandardButton reply;
                reply = QMessageBox::question(nullptr, "Buy Hotel",
                                              QString("Do you want to buy a hotel on %1, %2 for %4? your money balance now is: %3")
                                                  .arg(QString::fromStdString(property->getCity()),
                                                       QString::fromStdString(property->getStreet()),
                                                       QString::number(player.getMoneyBalance()),
                                                       QString::number(4 * property->getHousePrice() + 100)),
                                              QMessageBox::Yes | QMessageBox::No);

                if (reply == QMessageBox::Yes) {
                    buyHotel(property, player);
                    GUIhouseCreate(newPosition, property->getHouseAmount());
                }
            }
        }else if(!board.ownTheCity(property, player.getId())){
            GUIShowMessage("You must own all the city first !");
        }else if(board.sameOrLessAmountOfHouses(property)){
            GUIShowMessage("You must have a same or less amount of houses than the rest of the city streets !");
        }
    } else{
        GUIShowMessage("You can build houses only in streets !");
    }
}
/**
 * Charges a tax amount to a player. The player pays the tax if they have enough money;
 * otherwise, they may need to mortgage properties or declare bankruptcy if they have none.
 *
 * @param player The player who is paying the tax.
 * @param amount The amount of tax to be paid.
 */
void Game::chargeTax(Player& player, int amount) {
    bool isPaid = false;
    while (!isPaid) {
        if (player.getMoneyBalance() >= amount) {
            player.payToBank(amount);
            QMessageBox::information(nullptr, "Tax Payment",
                                     QString::fromStdString(player.getName() + " paid $" + std::to_string(amount) +
                                                            " in Tax to the bank, your balance now is: " + std::to_string(player.getMoneyBalance())));
            isPaid = true;
        } else {
            if (player.haveNoProperties()) {
                player.payToBank(player.getMoneyBalance());
                player.setOutOfTheGame();
                QGraphicsPixmapItem* playerIcon = playerIcons[player.getId()];
                playerIcon->setPos(400 + player.getId() * 5, 400);
                GUIShowMessage("You have no more properties to sell and not enough money to pay. You are out of the game.");
                isPaid = true;
            } else {
                QMessageBox::warning(nullptr, "Insufficient Funds",
                                     QString::fromStdString(player.getName() + " does not have enough money to pay tax of $" +
                                                            std::to_string(amount) + ". Please mortgage properties."));
                sellProperties(player);
            }
        }
    }
}

/**
 * Displays a message to the user using a message box.
 *
 * @param message The message to be displayed.
 */
void Game::GUIShowMessage(std::string message) {
    QMessageBox::information(nullptr, "Message",
                             QString::fromStdString(message));
}

/**
 * Handles drawing a Chance card for a player, performing the appropriate action based on the card type.
 *
 * @param player The player drawing the Chance card.
 * @param newPosition The new position of the player after drawing the card.
 * @param diceResult The result of the dice roll that led to this action.
 */
void Game::takeChanceCard(Player& player, int newPosition, int diceResult) {
    Card card = board.drawChanceCard();
    GUIShowMessage(card.getDescription());
    switch (card.getType()) {
    case 'c':
        player.collectMoney(card.getValue());
        board.pushChanceCard(card);
        break;

    case 'p':
        chargeTax(player, card.getValue());
        board.pushChanceCard(card);
        break;

    case 'g':
        handleTile(player, card.getValue(), diceResult);
        board.pushChanceCard(card);
        break;

    case 'j':
        player.setJailCard(true);
        break;
    }
}

/**
 * Handles drawing a Community Chest card for a player, performing the appropriate action based on the card type.
 *
 * @param player The player drawing the Community Chest card.
 * @param newPosition The new position of the player after drawing the card.
 * @param diceResult The result of the dice roll that led to this action.
 */
void Game::takeCommunityChestCard(Player& player, int newPosition, int diceResult) {
    Card card = board.drawCommunityChestCard();
    GUIShowMessage(card.getDescription());
    switch (card.getType()) {
    case 'c':
        player.collectMoney(card.getValue());
        board.pushCommunityChestCard(card);
        break;

    case 'p':
        chargeTax(player, card.getValue());
        board.pushCommunityChestCard(card);
        break;

    case 'g':
        handleTile(player, card.getValue(), diceResult);
        board.pushCommunityChestCard(card);
        break;
    }
}

/**
 * Handles the use of a Jail card for a player, allowing them to exit jail if they have a Jail card.
 *
 * @param player The player considering using their Jail card.
 */
void Game::handleJailCard(Player& player) {
    if (player.isInPrison() && player.hasExitJailCard()) {
        QMessageBox::StandardButton reply;
        reply = QMessageBox::question(nullptr, "Jail Card",
                                      QString("%1 Do you want to use your Jail Card and exit from the jail?")
                                          .arg(QString::fromStdString(player.getName())),
                                      QMessageBox::Yes | QMessageBox::No);

        if (reply == QMessageBox::Yes) {
            player.setJailCard(false);
            player.setIfPrisoner(false);
            player.resetJailTurn();
            Card card(4, "Get out of the jail ticket, keep it for when you will need it!", 0, 'j');
            board.pushChanceCard(card);
        }
    }
}

/**
 * Updates the GUI to reflect a player's new position on the board.
 *
 * @param player The player whose position is being updated.
 */
void Game::GUIupdatePlayerPosition(const Player& player) {
    QGraphicsPixmapItem* playerIcon = playerIcons[player.getId()];
    // Calculate the new position on the board based on player.getPlaceOnBoard()
    int x = calculateXPosition(player.getId(), player.getPlaceOnBoard());
    int y = calculateYPosition(player.getId(), player.getPlaceOnBoard());

    playerIcon->setPos(x, y);
}
/**
 * Calculates the X position on the GUI for a player based on their ID and current position on the board.
 * The first tile is at the bottom right (position 0).
 *
 * @param playerId The ID of the player.
 * @param position The current position of the player on the board.
 * @return The calculated X coordinate for the player on the GUI.
 */
int Game::calculateXPosition(int playerId, int position) {
    if (position < 10) {  // Bottom row (0-9)
        return 707 - (position * 65) - ((playerId - 1) * 2); // Moving left from the bottom right
    } else if (position < 20) {  // Left column (10-19)
        return 10; // Fixed X for the left column
    } else if (position < 30) {  // Top row (20-29)
        return 65 + (position - 20) * 65 + ((playerId - 1) * 2); // Moving right from the top left
    } else {  // Right column (30-39)
        return 760; // Fixed X for the right column
    }
}

/**
 * Calculates the Y position on the GUI for a player based on their ID and current position on the board.
 * The first tile is at the bottom right (position 0).
 *
 * @param playerId The ID of the player.
 * @param position The current position of the player on the board.
 * @return The calculated Y coordinate for the player on the GUI.
 */
int Game::calculateYPosition(int playerId, int position) {
    if (position < 10) {  // Bottom row (0-9)
        return 780; // Fixed Y for the bottom row
    } else if (position < 20) {  // Left column (10-19)
        return 716 - ((position - 10) * 65) - ((playerId - 1) * 2); // Moving up from the bottom right
    } else if (position < 30) {  // Top row (20-29)
        return 10; // Fixed Y for the top row
    } else {  // Left column (30-39)
        return 60 + (position - 30) * 65 + ((playerId - 1) * 2); // Moving down from the top right
    }
}

/**
 * Creates a house icon on the GUI for a specific property position.
 * It loads the appropriate logo based on the number of houses (or a hotel), scales it, and adds it to the scene.
 *
 * @param position The position on the board where the house is being created.
 * @param houseNum The number of houses (1-4) or 5 for a hotel.
 */
void Game::GUIhouseCreate(int position, int houseNum) {
    QString logoPath = "/Users/roeibiton/QtProjects/Monopoly/house_logo.png"; // Default house logo path
    if (houseNum == 5) {
        logoPath = "/Users/roeibiton/QtProjects/Monopoly/hotel_logo.png"; // Path to hotel logo if 5 houses
    }
    QPixmap logoPixmap(logoPath);

    if (logoPixmap.isNull()) {
        QMessageBox::warning(nullptr, "Error", "Failed to load logo for House");
        return; // Exit if a logo fails to load
    } else {
        qDebug() << "Loaded logo for House"; // Debug message
    }
    const int MAX_HOUSE_LOGO_WIDTH = 15;
    const int MAX_HOUSE_LOGO_HEIGHT = 15;
    // Scale the logo
    logoPixmap = logoPixmap.scaled(MAX_HOUSE_LOGO_WIDTH, MAX_HOUSE_LOGO_HEIGHT, Qt::KeepAspectRatio, Qt::SmoothTransformation);

    // Create a QGraphicsPixmapItem for the player logo and add it to the scene
    QGraphicsPixmapItem* houseIcon = scene->addPixmap(logoPixmap);
    houseIcon->setZValue(1); // Ensure logos are on top
    houseIcons[(position * 5) + houseNum - 1] = houseIcon; // Store the icon in the vector
    int x = calculateHouseXPosition(position, houseNum);
    int y = calculateHouseYPosition(position, houseNum);
    // Set the position for the player logo on the board
    houseIcon->setPos(x, y);
}

/**
 * Deletes house icons from the GUI for a specific property position.
 * It removes and frees memory for up to five house icons at the given position.
 *
 * @param position The position on the board where the houses are being deleted.
 */
void Game::GUIdeleteHouses(int position) {
    int startIndex = position * 5;

    for (int index = startIndex; index < startIndex + 5; ++index) {
        QGraphicsPixmapItem* houseIcon = houseIcons[index];

        if (houseIcon) {
            scene->removeItem(houseIcon);  // Remove from the scene
            delete houseIcon;  // Free memory
            houseIcons[index] = nullptr;  // Mark the icon as deleted in the vector
        }
    }
}

/**
 * Calculates the X position on the GUI for a house based on the property position and house number.
 * The first tile is at the bottom right (position 0).
 *
 * @param position The position of the property on the board.
 * @param houseNum The number of the house (1-5).
 * @return The calculated X coordinate for the house on the GUI.
 */
int Game::calculateHouseXPosition(int position, int houseNum) {
    if (position < 10) {  // Bottom row (0-9)
        return 697 - (position * 65) + ((houseNum - 1) * 8); // Moving left from the bottom right
    } else if (position < 20) {  // Left column (10-19)
        return 22; // Fixed X for the left column
    } else if (position < 30) {  // Top row (20-29)
        return 48 + (position - 20) * 65 + ((houseNum - 1) * 8); // Moving right from the top left
    } else {  // Right column (30-39)
        return 770; // Fixed X for the right column
    }
}

/**
 * Calculates the Y position on the GUI for a house based on the property position and house number.
 * The first tile is at the bottom right (position 0).
 *
 * @param position The position of the property on the board.
 * @param houseNum The number of the house (1-5).
 * @return The calculated Y coordinate for the house on the GUI.
 */
int Game::calculateHouseYPosition(int position, int houseNum) {
    // The first tile is at the bottom right (position 0).
    if (position < 10) {  // Bottom row (0-9)
        return 755; // Fixed Y for the bottom row
    } else if (position < 20) {  // Left column (10-19)
        return 701 - ((position - 10) * 65) + ((houseNum-1)*8); // Moving up from the bottom right
    } else if (position < 30) {  // Top row (20-29)
        return 20; // Fixed Y for the top row
    } else {  // Left column (30-39)
        return 50 + (position - 30) * 65 + ((houseNum-1)*8); // Moving down from the top right
    }
}

/**
 * Prompts the player to build a house on one of their owned properties.
 * Displays a list of owned properties for the player to choose from.
 *
 * @param player The player who wants to build a house.
 */
void Game::buildHouseOnProperty(Player& player) {

    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(nullptr, "Buy House",
                                  QString("%1 Do you want to buy a house?")
                                          .arg(QString::fromStdString(player.getName())),
                                  QMessageBox::Yes | QMessageBox::No);

    if (reply == QMessageBox::Yes) {


    QStringList propertiesToBuild; // List to store property names for dialog
    std::vector<int> ownedProperties = player.getOwnedProperties();

    // Collect property names
    for (int propertyId : ownedProperties) {
        Property* property = board.getPropertyById(propertyId); // Get property by ID
        if (property && property->getHouseAmount() < 5) { // Check if the player can build a house
            propertiesToBuild << QString::fromStdString(property->getCity() + " " + property->getStreet());
        }
    }

    if (propertiesToBuild.isEmpty()) {
        GUIShowMessage("You have no properties !");
        return;
    }

    // Ask the player to select a property to build a house on
    bool ok;
    QString selectedProperty = QInputDialog::getItem(nullptr, "Select Property to Build House",
                                                     "Select one:",
                                                     propertiesToBuild, 0, false, &ok);

    if (ok && !selectedProperty.isEmpty()) {
        // Find the property ID based on the selected name
        for (int propertyId : ownedProperties) {
            Property* property = board.getPropertyById(propertyId);
            if (property && selectedProperty == QString::fromStdString(property->getCity() + " " + property->getStreet())) {
              handlePropertyDevelopement(player, property, property->getPosition());
                break; // Exit loop after finding and building the house
            }
        }
    }
    }
}



