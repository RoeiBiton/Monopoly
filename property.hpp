/**
 * Created by Roei Biton
 * Gmail: roei.biton33@gmail.com
 * */

#ifndef PROPERTY_HPP
#define PROPERTY_HPP

#include <string>

class Property {
private:
    int id;                             // Property ID
    std::string city;                   // City where the property is located
    std::string street;                 // Street name
    int position;                       // Property position on the board
    int rent;                           // Current rent value
    int originalRent;                   // Original rent value before modifications
    int propertyPrice;                  // Purchase price of the property
    int propertyMortgage;                // Mortgage value of the property
    int owner;                          // ID of the property owner (or -1 if not owned)
    int housePrice;                     // Price for building houses on the property
    int houseAmount;                    // Number of houses currently built on the property
    std::string color;                  // Color associated with the property

public:
    // Constructor
    Property(int propertyId, const std::string& propertyCity, const std::string& propertyStreet, int propertyPosition,
             int rentValue, int price, int hPrice, const std::string& propertyColor);

    // Setters
    void setOwner(int id);               // Set the owner of the property
    void setRent(int rentPrice);         // Set the current rent value
    void buildHouse();                   // Increase the number of houses on the property
    void resetProperty();                // Reset the property to its original state

    // Getters
    int getId() const;                   // Get the property ID
    std::string getCity() const;         // Get the city of the property
    std::string getStreet() const;       // Get the street name of the property
    std::string getName() const;         // Get the full name (city and street) of the property
    int getRent() const;                 // Get the current rent value
    int getOriginalRent() const;         // Get the original rent value
    int getPropertyPrice() const;        // Get the purchase price of the property
    int getPosition() const;             // Get the position of the property on the board
    int getPropertyMortgage() const;     // Get the mortgage value of the property
    int getOwner() const;                // Get the owner ID of the property
    int getHousePrice() const;           // Get the price for building houses
    int getHouseAmount() const;          // Get the number of houses built on the property
    std::string getColor() const;        // Get the color associated with the property

    // Methods
    void updateRent();                   // Update the rent value based on the number of houses
    void updateTrainRent(int playerId, int trainCounter); // Update rent for train properties based on the number of trains owned
};

#endif
