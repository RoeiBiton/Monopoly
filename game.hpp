// Game.hpp
#ifndef GAME_HPP
#define GAME_HPP

#include <vector>
#include "player.hpp"
#include "board.hpp"
#include "dice.hpp"

class Game {
private:
    std::vector<Player> players; // List of players
    Board board; // The game board
    Dice dice; // The dice for the game
    int currentPlayerIndex; // Index of the current player
    bool gameEnded; // Flag to indicate if the game has ended

public:
    Game(const std::vector<Player>& players); // Constructor
    void startGame(); // Start the game
    void playTurn(); // Handle a player's turn
    bool isGameOver() const; // Check if the game is over
    void endGame(); // End the game
    void handleTile(Player& player, int newPosition, int diceResult); // Handle landing on a tile
    void sellProperties(Player& player);
    void buyHouse(Property* property, Player& player);
    void buyHotel(Property* property, Player& player);
    void updateTrainRent(int playerId, int trainCounter);
};

#endif // GAME_HPP
