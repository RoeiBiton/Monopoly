/**
 * Created by Roei Biton
 * Gmail: roei.biton33@gmail.com
 * */



#include "player.hpp"
#include <algorithm>
/**

 * @brief Contains the Player class, representing each player in the Monopoly game.
 *
 * The Player class manages the player's information, including their name,
 * ID, logo, money balance, position on the board, properties owned, and various
 * game states such as jail status and turn management.
 */


// Constructor
/**
 * @brief Constructs a Player object.
 *
 * @param playerName The name of the player.
 * @param playerId The unique identifier for the player.
 * @param playerLogo The logo associated with the player.
 */
Player::Player(const std::string& playerName, int playerId)
    : name(playerName), id(playerId),
    moneyBalance(1500), placeOnBoard(0), doubleCounter(0), jailTurn(0), myTurn(false),
    exitJailCard(false), isPrisoner(false), isFreeParked(false), isActive(true), trainCounter(0) {}

// Setters
/**
 * @brief Sets the player's name.
 *
 * @param playerName The new name for the player.
 */
void Player::setName(const std::string& playerName) {
    name = playerName;
}

/**
 * @brief Sets the player's ID.
 *
 * @param playerId The new ID for the player.
 */
void Player::setId(int playerId) {
    id = playerId;
}

/**
 * @brief Marks the player as out of the game.
 */
void Player::setOutOfTheGame() {
    this->isActive = false;
}

/**
 * @brief Sets the player's prisoner status.
 *
 * @param ans True if the player is a prisoner; false otherwise.
 */
void Player::setIfPrisoner(bool ans) {
    this->isPrisoner = ans;
}

/**
 * @brief Updates the player's position on the board.
 *
 * @param place The new position on the board.
 */
void Player::setPlaceOnBoard(int place) {
    this->placeOnBoard = place;
}

/**
 * @brief Increments the player's train counter.
 */
void Player::incTrainCounter() {
    trainCounter++;
}

/**
 * @brief Decrements the player's train counter.
 */
void Player::decTrainCounter() {
    trainCounter--;
}

/**
 * @brief Sets the player's free parking status.
 *
 * @param ans True if the player is in free parking; false otherwise.
 */
void Player::setFreeParked(bool ans) {
    isFreeParked = ans;
}

/**
 * @brief Sets the player's exit jail card status.
 *
 * @param ans True if the player has an exit jail card; false otherwise.
 */
void Player::setJailCard(bool ans) {
    exitJailCard = ans;
}

// Getters
/**
 * @brief Gets the player's name.
 *
 * @return The player's name.
 */
std::string Player::getName() const {
    return name;
}

/**
 * @brief Gets the player's ID.
 *
 * @return The player's ID.
 */
int Player::getId() const {
    return id;
}

/**
 * @brief Gets the player's money balance.
 *
 * @return The player's current money balance.
 */
int Player::getMoneyBalance() const {
    return moneyBalance;
}

/**
 * @brief Gets the player's current position on the board.
 *
 * @return The player's position on the board.
 */
int Player::getPlaceOnBoard() const {
    return placeOnBoard;
}

/**
 * @brief Gets the number of turns the player has spent in jail.
 *
 * @return The number of jail turns.
 */
int Player::getJailTurn() const {
    return jailTurn;
}

/**
 * @brief Gets the player's double roll counter.
 *
 * @return The number of double rolls.
 */
int Player::getDoubleCounter() const {
    return doubleCounter;
}

/**
 * @brief Gets the player's train counter.
 *
 * @return The train counter value.
 */
int Player::getTrainCounter() {
    return trainCounter;
}

/**
 * @brief Checks if the player is active in the game.
 *
 * @return True if the player is active; false otherwise.
 */
bool Player::getActive() const {
    return isActive;
}

/**
 * @brief Checks if it is the player's turn.
 *
 * @return True if it is the player's turn; false otherwise.
 */
bool Player::isMyTurn() const {
    return myTurn;
}

/**
 * @brief Checks if the player has an exit jail card.
 *
 * @return True if the player has an exit jail card; false otherwise.
 */
bool Player::hasExitJailCard() const {
    return exitJailCard;
}

/**
 * @brief Checks if the player is in jail.
 *
 * @return True if the player is a prisoner; false otherwise.
 */
bool Player::isInPrison() const {
    return isPrisoner;
}

/**
 * @brief Checks if the player is in free parking.
 *
 * @return True if the player is in free parking; false otherwise.
 */
bool Player::isFreeParkedStatus() const {
    return isFreeParked;
}

/**
 * @brief Gets the properties owned by the player.
 *
 * @return A vector containing the IDs of owned properties.
 */
std::vector<int> Player::getOwnedProperties() const {
    return ownedProperties;
}

/**
 * @brief Checks if the player has no properties.
 *
 * @return True if the player has no properties; false otherwise.
 */
bool Player::haveNoProperties() const {
    return ownedProperties.empty();
}

// Methods
/**
 * @brief Buys a property and adds it to the player's owned properties.
 *
 * @param propertyId The ID of the property to buy.
 */
void Player::buyProperty(int propertyId) {
    ownedProperties.push_back(propertyId);
}

/**
 * @brief Transfers money from this player to another player.
 *
 * @param otherPlayer The player receiving the money.
 * @param amount The amount of money to transfer.
 */
void Player::payToPlayer(Player& otherPlayer, int amount) {
    if (moneyBalance >= amount) {
        moneyBalance -= amount;
        otherPlayer.moneyBalance += amount;
    }
}

/**
 * @brief Pays money to the bank.
 *
 * @param amount The amount of money to pay.
 */
void Player::payToBank(int amount) {
    if (moneyBalance >= amount) {
        moneyBalance -= amount;
    }
}

/**
 * @brief Sells a property and removes it from the player's owned properties.
 *
 * @param propertyId The ID of the property to sell.
 */
void Player::sellProperty(int propertyId) {
    // Find and erase the property ID from ownedProperties
    auto it = std::find(ownedProperties.begin(), ownedProperties.end(), propertyId);
    if (it != ownedProperties.end()) {
        ownedProperties.erase(it); // Erase the property using the iterator
    }
}

/**
 * @brief Increases the double roll counter.
 */
void Player::increaseDoubleCounter() {
    this->doubleCounter++;
}

/**
 * @brief Collects money for the player.
 *
 * @param amount The amount of money to collect.
 */
void Player::collectMoney(int amount) {
    this->moneyBalance += amount;
}

/**
 * @brief Resets the double roll counter to zero.
 */
void Player::resetDoubleCounter() {
    this->doubleCounter = 0;
}

/**
 * @brief Increases the jail turn counter.
 */
void Player::increaseJailTurn() {
    this->jailTurn++;
}

/**
 * @brief Resets the jail turn counter to zero.
 */
void Player::resetJailTurn() {
    this->jailTurn = 0;
}
