/**
 * Created by Roei Biton
 * Gmail: roei.biton33@gmail.com
 * */

// Game.hpp
#ifndef GAME_HPP
#define GAME_HPP

#include <vector>
#include "player.hpp"
#include "board.hpp"
#include "dice.hpp"
#include <QGraphicsScene>

// The Game class represents the Monopoly game, managing players, the game board,
// and game mechanics such as turns and property management.
class Game {
private:
    std::vector<Player> players; // List of players
    Board board; // The game board
    Dice dice; // The dice for the game
    int currentPlayerIndex; // Index of the current player
    bool gameEnded; // Flag to indicate if the game has ended
    QGraphicsScene* scene; // Pointer to the graphical scene for GUI representation
    std::vector<QGraphicsPixmapItem*> playerIcons; // Icons representing players on the GUI
    std::vector<QGraphicsPixmapItem*> houseIcons; // Icons representing houses on the GUI

    // Handles the current player's turn, including movement and actions
    void playTurn();

    // Checks if the game is over, returning true if it is
    bool isGameOver();

    // Actions taken when a player draws a Chance card
    void takeChanceCard(Player& player, int newPosition, int diceResult);

    // Actions taken when a player draws a Community Chest card
    void takeCommunityChestCard(Player& player, int newPosition, int diceResult);

    // Handles special actions associated with jail cards
    void handleJailCard(Player& player);

    // Handles actions taken when landing on a tile
    void handleTile(Player& player, int newPosition, int diceResult);

    // Manages rent payments when a player lands on a property
    void handleRentPayment(Player& player, Property* property, int diceResult);

    // Handles property purchase actions when a player lands on a property
    void handlePropertyPurchase(Player& player, Property* property, int newPosition);

    // Handles property development actions (buying houses or hotels)
    void handlePropertyDevelopement(Player& player, Property* property, int newPosition);

    // Allows a player to sell their properties
    void sellProperties(Player& player);

    // Manages the process of buying a house for a property
    void buyHouse(Property* property, Player& player);

    // Manages the process of buying a hotel for a property
    void buyHotel(Property* property, Player& player);

    // Updates the rent for all trains owned by a player
    void updateAllTrainRent(int playerId, int trainCounter);

    // Charges a player a specific amount for tax
    void chargeTax(Player& player, int amount);

    // GUI-related methods for displaying messages and updating positions
    void GUIShowMessage(std::string message);
    void GUIupdatePlayerPosition(const Player& player);

    // Calculates the X position for a player's icon on the GUI
    int calculateXPosition(int playerId, int position);

    // Calculates the Y position for a player's icon on the GUI
    int calculateYPosition(int playerId, int position);

    // Creates house icons on the GUI for a specific property position
    void GUIhouseCreate(int position, int houseNum);

    // Deletes house icons from the GUI for a specific property position
    void GUIdeleteHouses(int position);

    // Calculates the X position for a house icon on the GUI
    int calculateHouseXPosition(int position, int houseNum);

    // Calculates the Y position for a house icon on the GUI
    int calculateHouseYPosition(int position, int houseNum);
public:
    // Constructor that initializes the game with players and a graphical scene
    Game(const std::vector<Player>& players, QGraphicsScene* scene);

    // Starts the game
    void startGame();

    // Ends the game and performs necessary cleanup
    void endGame();

    void buildHouseOnProperty(Player& player);
};

#endif // GAME_HPP
