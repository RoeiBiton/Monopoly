// Game.hpp
#ifndef GAME_HPP
#define GAME_HPP

#include <vector>
#include "player.hpp"
#include "board.hpp"
#include "dice.hpp"
#include <QGraphicsScene>

class Game {
private:
    std::vector<Player> players; // List of players
    Board board; // The game board
    Dice dice; // The dice for the game
    int currentPlayerIndex; // Index of the current player
    bool gameEnded; // Flag to indicate if the game has ended
    QGraphicsScene* scene;
    std::vector<QGraphicsPixmapItem*> playerIcons;
    std::vector<QGraphicsPixmapItem*> houseIcons;



    void takeChanceCard(Player& player, int newPosition, int diceResult);
    void takeCommunityChestCard(Player& player, int newPosition, int diceResult);

    void handleTile(Player& player, int newPosition, int diceResult); // Handle landing on a tile
    void sellProperties(Player& player);
    void buyHouse(Property* property, Player& player);
    void buyHotel(Property* property, Player& player);
    void updateAllTrainRent(int playerId, int trainCounter);
    void handleRentPayment(Player& player, Property* property, int diceResult);
    void handlePropertyPurchase(Player& player, Property* property, int newPosition);
    void handlePropertyDevelopement(Player& player, Property* property, int newPosition);
    void chargeTax(Player& player, int amount);
    void handleJailCard(Player& player);

    void GUIupdatePlayerPosition(const Player& player);
    int calculateXPosition(int playerId, int position);
    int calculateYPosition(int playerId, int position);
    void GUIhouseCreate(int position, int houseNum);
    void GUIdeleteHouses(int position);
    int calculateHouseXPosition(int position, int houseNum);
    int calculateHouseYPosition(int position, int houseNum);
public:
    Game(const std::vector<Player>& players, QGraphicsScene* scene);; // Constructor
    void startGame(); // Start the game
    void playTurn(); // Handle a player's turn
    bool isGameOver(); // Check if the game is over
    void endGame(); // End the game


    //GUI methods
    void GUIShowMessage(std::string message);
};

#endif // GAME_HPP
