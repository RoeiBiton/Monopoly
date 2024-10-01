#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <string>
#include <vector>

class Player {
private:
    std::string name;                   // Player's name
    int id;                             // Player's ID
    int logo;                           // Logo identifier
    int moneyBalance;                   // Player's money balance
    std::vector<int> ownedProperties;   // Vector of owned property IDs
    int placeOnBoard;                   // Player's current position on the board
    int doubleCounter;                  // Counter for doubles rolled
    int jailTurn;                       // Number of turns the player has been in jail
    bool myTurn;                        // Indicates if it's the player's turn
    bool exitJailCard;                  // Indicates if the player has an exit jail card
    bool isPrisoner;                    // Indicates if the player is in jail
    bool isFreeParked;                  // Indicates if the player is in the Free Parking area
    bool isActive;                      // Indicates if the player is active in the game
    int trainCounter;                   // Counter for the number of trains owned

public:
    // Constructor
    Player(const std::string& playerName, int playerId, int playerLogo);

    // Setters
    void setName(const std::string& playerName);     // Set the player's name
    void setId(int playerId);                         // Set the player's ID
    void setOutOfTheGame();                           // Mark the player as out of the game
    void incTrainCounter();                           // Increment the train counter
    void decTrainCounter();                           // Decrement the train counter
    void increaseDoubleCounter();                     // Increment the double counter
    void resetDoubleCounter();                         // Reset the double counter
    void increaseJailTurn();                          // Increment the jail turn counter
    void resetJailTurn();                             // Reset the jail turn counter
    void setFreeParked(bool ans);                     // Set the player's Free Parking status
    void setJailCard(bool ans);                       // Set the player's exit jail card status
    void setIfPrisoner(bool ans);                     // Set the player's prison status
    void setPlaceOnBoard(int place);                  // Set the player's position on the board

    // Getters
    std::string getName() const;                      // Get the player's name
    int getId() const;                                // Get the player's ID
    int getLogo() const;                              // Get the player's logo identifier
    int getMoneyBalance() const;                      // Get the player's money balance
    int getPlaceOnBoard() const;                      // Get the player's position on the board
    int getJailTurn() const;                          // Get the number of turns the player has been in jail
    int getDoubleCounter() const;                     // Get the number of doubles rolled
    int getTrainCounter();                             // Get the number of trains owned
    bool getActive() const;                           // Check if the player is active
    bool isMyTurn() const;                            // Check if it's the player's turn
    bool hasExitJailCard() const;                     // Check if the player has an exit jail card
    bool isInPrison() const;                          // Check if the player is in jail
    bool isFreeParkedStatus() const;                  // Check if the player is in Free Parking
    std::vector<int> getOwnedProperties() const;      // Get the IDs of owned properties
    bool haveNoProperties() const;                     // Check if the player owns no properties

    // Methods
    void buyProperty(int propertyId);                 // Buy a property by ID
    void payToPlayer(Player& otherPlayer, int amount); // Pay another player a specified amount
    void payToBank(int amount);                        // Pay a specified amount to the bank
    void sellProperty(int propertyId);                 // Sell a property by ID
    void collectMoney(int amount);                     // Collect a specified amount of money
};

#endif
