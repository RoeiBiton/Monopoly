#include "property.hpp"

// Constructor
Property::Property(int propertyId,
                   const std::string& propertyCity,
                   const std::string& propertyStreet,
                   int propertyPosition,
                   int rentValue,
                   int price,
                   int hPrice,
                   const std::string& propertyColor)
    : id(propertyId), city(propertyCity), street(propertyStreet), position(propertyPosition),
    rent(rentValue), originalRent(rentValue), propertyPrice(price), propertyMortgage(price / 2),
    owner(-1), housePrice(hPrice), houseAmount(0),
    color(propertyColor) {}

// Setters
void Property::setOwner(int id) {
    this->owner = id; // Sets the owner ID of the property
}

void Property::setRent(int rentPrice) {
    this->rent = rentPrice; // Sets the current rent price of the property
}

void Property::buildHouse() {
    this->houseAmount++; // Increments the number of houses on the property
    this->updateRent();  // Updates the rent based on the new number of houses
}

// Getters
int Property::getId() const {
    return id; // Returns the property's ID
}

int Property::getPosition() const {
    return position; // Returns the property's position on the board
}

std::string Property::getCity() const {
    return city; // Returns the city's name
}

std::string Property::getStreet() const {
    return street; // Returns the street's name
}

std::string Property::getName() const {
    return (city + " " + street); // Returns the full name of the property (city + street)
}

int Property::getRent() const {
    return rent; // Returns the current rent price
}

int Property::getOriginalRent() const {
    return originalRent; // Returns the original rent price before modifications
}

int Property::getPropertyPrice() const {
    return propertyPrice; // Returns the price to purchase the property
}

int Property::getPropertyMortgage() const {
    return propertyMortgage; // Returns the mortgage value of the property
}

int Property::getOwner() const {
    return owner; // Returns the ID of the property owner
}

int Property::getHousePrice() const {
    return housePrice; // Returns the price to build a house on the property
}

int Property::getHouseAmount() const {
    return houseAmount; // Returns the current number of houses on the property
}

std::string Property::getColor() const {
    return color; // Returns the color associated with the property
}

// Resets the property to its initial state
void Property::resetProperty() {
    this->houseAmount = 0; // Resets house count to zero
    this->updateRent();    // Updates rent based on house count
    this->updateTrainRent(getOwner(), getOwner()); // Updates rent for train properties
    this->setOwner(-1);    // Resets owner to none
}

// Updates the rent based on the number of houses on the property
void Property::updateRent() {
    // Set rent based on house amount
    if (this->getHouseAmount() == 0) {
        this->setRent(this->getOriginalRent()); // Rent is original rent when no houses are built
    }

    // Rent calculations for 1 house
    if (this->getHouseAmount() == 1) {
        if (this->getPosition() != 39 && this->getPosition() != 34) {
            this->setRent(this->getRent() * 5); // Example adjustment for 1 house
        } else if (this->getPosition() == 34) {
            this->setRent(150); // Specific rent for property at position 34
        } else if (this->getPosition() == 39) {
            this->setRent(200); // Specific rent for property at position 39
        }
    }
    // Rent calculations for 2 houses
    else if (this->getHouseAmount() == 2) {
        switch (this->getId()) {
        case 0: case 1: case 2: case 3: case 5: case 6: case 7: case 13: case 14: case 15: case 16: case 17: case 18: case 19: case 21:
            this->setRent(this->getRent() * 3); // Triples the rent for these property IDs
            break;
        case 4:
            this->setRent(100); // Specific rent for property ID 4
            break;
        case 8: case 9:
            this->setRent(200); // Specific rent for property IDs 8 and 9
            break;
        case 10:
            this->setRent(220); // Specific rent for property ID 10
            break;
        case 11: case 12:
            this->setRent(250); // Specific rent for property IDs 11 and 12
            break;
        case 20:
            this->setRent(500); // Specific rent for property ID 20
            break;
        }
    }
    // Rent calculations for 3 houses
    else if (this->getHouseAmount() == 3) {
        switch (this->getId()) {
        case 0: case 1: case 2: case 3: case 4: case 5: case 6:
            this->setRent(this->getRent() * 3); // Triples the rent for these property IDs
            break;
        case 7:
            this->setRent(500); // Specific rent for property ID 7
            break;
        case 8: case 9:
            this->setRent(550); // Specific rent for property IDs 8 and 9
            break;
        case 10:
            this->setRent(600); // Specific rent for property ID 10
            break;
        case 11: case 12:
            this->setRent(700); // Specific rent for property IDs 11 and 12
            break;
        case 13:
            this->setRent(750); // Specific rent for property ID 13
            break;
        case 14: case 15:
            this->setRent(800); // Specific rent for property IDs 14 and 15
            break;
        case 16:
            this->setRent(850); // Specific rent for property ID 16
            break;
        case 17: case 18:
            this->setRent(900); // Specific rent for property IDs 17 and 18
            break;
        case 19:
            this->setRent(1000); // Specific rent for property ID 19
            break;
        case 20:
            this->setRent(1100); // Specific rent for property ID 20
            break;
        case 21:
            this->setRent(1400); // Specific rent for property ID 21
            break;
        }
    }
    // Rent calculations for 4 houses
    else if (this->getHouseAmount() == 4) {
        switch (this->getId()) {
        case 0:
            this->setRent(160); // Specific rent for property ID 0
            break;
        case 1:
            this->setRent(320); // Specific rent for property ID 1
            break;
        case 2: case 3:
            this->setRent(400); // Specific rent for property IDs 2 and 3
            break;
        case 4:
            this->setRent(450); // Specific rent for property ID 4
            break;
        case 5: case 6:
            this->setRent(625); // Specific rent for property IDs 5 and 6
            break;
        case 7:
            this->setRent(700); // Specific rent for property ID 7
            break;
        case 8: case 9:
            this->setRent(700); // Specific rent for property IDs 8 and 9
            break;
        case 10:
            this->setRent(800); // Specific rent for property ID 10
            break;
        case 11: case 12:
            this->setRent(875); // Specific rent for property IDs 11 and 12
            break;
        case 13:
            this->setRent(925); // Specific rent for property ID 13
            break;
        case 14: case 15:
            this->setRent(975); // Specific rent for property IDs 14 and 15
            break;
        case 16:
            this->setRent(1025); // Specific rent for property ID 16
            break;
        case 17: case 18:
            this->setRent(1100); // Specific rent for property IDs 17 and 18
            break;
        case 19:
            this->setRent(1200); // Specific rent for property ID 19
            break;
        case 20:
            this->setRent(1300); // Specific rent for property ID 20
            break;
        case 21:
            this->setRent(1700); // Specific rent for property ID 21
            break;
        }
    }
    // Rent calculations for 5 houses
    else if (this->getHouseAmount() == 5) {
        switch (this->getId()) {
        case 0:
            this->setRent(250); // Specific rent for property ID 0
            break;
        case 1:
            this->setRent(500); // Specific rent for property ID 1
            break;
        case 2: case 3:
            this->setRent(600); // Specific rent for property IDs 2 and 3
            break;
        case 4:
            this->setRent(650); // Specific rent for property ID 4
            break;
        case 5: case 6:
            this->setRent(900); // Specific rent for property IDs 5 and 6
            break;
        case 7:
            this->setRent(1000); // Specific rent for property ID 7
            break;
        case 8: case 9:
            this->setRent(1000); // Specific rent for property IDs 8 and 9
            break;
        case 10:
            this->setRent(1200); // Specific rent for property ID 10
            break;
        case 11: case 12:
            this->setRent(1300); // Specific rent for property IDs 11 and 12
            break;
        case 13:
            this->setRent(1400); // Specific rent for property ID 13
            break;
        case 14: case 15:
            this->setRent(1500); // Specific rent for property IDs 14 and 15
            break;
        case 16:
            this->setRent(1600); // Specific rent for property ID 16
            break;
        case 17: case 18:
            this->setRent(1700); // Specific rent for property IDs 17 and 18
            break;
        case 19:
            this->setRent(1800); // Specific rent for property ID 19
            break;
        case 20:
            this->setRent(1900); // Specific rent for property ID 20
            break;
        case 21:
            this->setRent(2500); // Specific rent for property ID 21
            break;
        }
    }
}

// Updates rent for train properties based on the number of trains owned
void Property::updateTrainRent(int playerId, int trainCounter) {
    // Set rent based on number of trains owned
    switch (trainCounter) {
    case 1:
        if (this->getOwner() == playerId) {
            this->setRent(25); // Rent for 1 train owned
        }
        break;
    case 2:
        if (this->getOwner() == playerId) {
            this->setRent(50); // Rent for 2 trains owned
        }
        break;
    case 3:
        if (this->getOwner() == playerId) {
            this->setRent(100); // Rent for 3 trains owned
        }
        break;
    case 4:
        if (this->getOwner() == playerId) {
            this->setRent(200); // Rent for 4 trains owned
        }
        break;
    }
}
