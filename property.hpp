#ifndef PROPERTY_HPP
#define PROPERTY_HPP

#include <string>

class Property {
private:
    int id;                             // Property ID
    std::string city;                   // City where the property is located
    std::string street;                 // Street name
    int position;                       // Property position on the board
    int rent;                           // Rent value
    int originalRent;
    int propertyPrice;                  // Purchase price
    int propertyMortgage;                // Mortgage value
    int owner;                          // ID of the property owner (or -1 if not owned)
    int housePrice;                     // Price for building houses
    int houseAmount;                    // Number of houses on the property
    std::string color;                  // Color of the property

public:
    // Constructor
    Property(int propertyId, const std::string& propertyCity, const std::string& propertyStreet, int propertyPosition,
             int rentValue, int price, int hPrice, const std::string& propertyColor);

    //Setters
    void setOwner(int id);
    void setRent(int rentPrice);
    void buildHouse();
    // Getters
    int getId() const;
    std::string getCity() const;
    std::string getStreet() const;
    int getRent() const;
    int getOriginalRent() const;
    int getPropertyPrice() const;
    int getPosition() const;
    int getPropertyMortgage() const;
    int getOwner() const;
    int getHousePrice() const;
    int getHouseAmount() const;
    std::string getColor() const;
    void updateRent();
    void resetProperty();

};

#endif
