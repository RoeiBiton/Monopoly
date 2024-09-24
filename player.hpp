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
    std::vector<int> ownedProperties;   // vector of owned properties
    int placeOnBoard;                   // Player's current position on the board
    int doubleCounter;
    int jailTurn;
    bool myTurn;                        // Indicates if it's the player's turn
    bool exitJailCard;                  // Indicates if the player has an exit jail card
    bool isPrisoner;                    // Indicates if the player is in jail
    bool isFreeParked;                  // Indicates if the player is in the Free Parking area
    bool isActive;
    int trainCounter;

public:
    // Constructor
    Player(const std::string& playerName, int playerId, int playerLogo);

    // Setters
    void setName(const std::string& playerName);
    void setId(int playerId);
    void setOutOfTheGame();
    void incTrainCounter();
    void decTrainCounter();
    void setFreeParked(bool ans);


    // Getters
    std::string getName() const;
    int getId() const;
    int getLogo() const;
    int getMoneyBalance() const;
    int getPlaceOnBoard() const;
    int getJailTurn() const;
    int getDoubleCounter() const;
    int getTrainCounter();
    bool getActive() const;
    bool isMyTurn() const;
    bool hasExitJailCard() const;
    bool isInPrison() const;
    bool isFreeParkedStatus() const;
    std::vector<int> getOwnedProperties() const;
    bool haveNoProperties() const;



    // Methods
    void buyProperty(int propertyId);
    void payToPlayer(Player& otherPlayer, int amount);
    void payToBank(int amount);
    void sellProperty(int propertyId);
    void setPlaceOnBoard(int place);
    void increaseDoubleCounter();
    void collectMoney(int amount);
    void setIfPrisoner(bool ans);
    void resetDoubleCounter();
    void increaseJailTurn();
    void resetJailTurn();

};

#endif
