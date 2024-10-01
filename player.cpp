#include "player.hpp"
#include <algorithm>

// Constructor
Player::Player(const std::string& playerName, int playerId, int playerLogo)
    : name(playerName), id(playerId), logo(playerLogo),
    moneyBalance(1500), placeOnBoard(0),doubleCounter(0), jailTurn(0), myTurn(false),
    exitJailCard(false), isPrisoner(false), isFreeParked(false), isActive(true), trainCounter(0){}

// Setters
void Player::setName(const std::string& playerName) {
    name = playerName;
}

void Player::setId(int playerId) {
    id = playerId;
}

void Player::setOutOfTheGame(){
    this->isActive=false;
}
void Player::setIfPrisoner(bool ans){
    this->isPrisoner=ans;
}
void Player::setPlaceOnBoard(int place) {
    this->placeOnBoard=place;
}
void Player::incTrainCounter(){
    trainCounter++;
}
void Player::decTrainCounter(){
    trainCounter--;
}
void Player::setFreeParked(bool ans){
    isFreeParked=ans;
}
void Player::setJailCard(bool ans){
    exitJailCard=ans;
}

// Getters
std::string Player::getName() const {
    return name;
}

int Player::getId() const {
    return id;
}

int Player::getLogo() const {
    return logo;
}

int Player::getMoneyBalance() const {
    return moneyBalance;
}

int Player::getPlaceOnBoard() const {
    return placeOnBoard;
}

int Player::getJailTurn() const {
    return jailTurn;
}

int Player::getDoubleCounter() const {
    return doubleCounter;
}
int Player::getTrainCounter(){
    return trainCounter;
}

bool Player::getActive() const {
    return isActive;
}

bool Player::isMyTurn() const {
    return myTurn;
}

bool Player::hasExitJailCard() const {
    return exitJailCard;
}

bool Player::isInPrison() const {
    return isPrisoner;
}

bool Player::isFreeParkedStatus() const {
    return isFreeParked;
}

std::vector<int> Player::getOwnedProperties() const {
    return ownedProperties;
}

bool Player::haveNoProperties() const{
    return ownedProperties.empty();
}


// Methods
void Player::buyProperty(int propertyId) {
    ownedProperties.push_back(propertyId);
}

void Player::payToPlayer(Player& otherPlayer, int amount) {
    if (moneyBalance >= amount) {
        moneyBalance -= amount;
        otherPlayer.moneyBalance += amount;
    }
}

void Player::payToBank(int amount) {
    if (moneyBalance >= amount) {
        moneyBalance -= amount;
    }
}

void Player::sellProperty(int propertyId) {
    // Find and erase the property ID from ownedProperties
    auto it = std::find(ownedProperties.begin(), ownedProperties.end(), propertyId);
    if (it != ownedProperties.end()) {
        ownedProperties.erase(it); // Erase the property using the iterator
    }
}


void Player::increaseDoubleCounter() {
    this->doubleCounter++;
}
void Player::collectMoney(int amount){
    this->moneyBalance = moneyBalance+amount;
}
void Player::resetDoubleCounter(){
    this->doubleCounter=0;
}
void Player::increaseJailTurn() {
    this->jailTurn++;
}
void Player::resetJailTurn() {
    this->jailTurn=0;
}


