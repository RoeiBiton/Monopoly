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
    rent(rentValue),originalRent(rentValue), propertyPrice(price), propertyMortgage(price/2),
    owner(-1), housePrice(hPrice), houseAmount(0),
    color(propertyColor) {}

//Setters
void Property::setOwner(int id){
    this->owner= id;
}
void Property::setRent(int rentPrice){
    this->rent=rentPrice;
}
void Property::buildHouse(){
    this->houseAmount++;
    this->updateRent();
}
// Getters
int Property::getId() const {
    return id;
}

int Property::getPosition() const {
    return position;
}

std::string Property::getCity() const {
    return city;
}

std::string Property::getStreet() const {
    return street;
}

int Property::getRent() const {
    return rent;
}
int Property::getOriginalRent() const {
    return originalRent;
}

int Property::getPropertyPrice() const {
    return propertyPrice;
}

int Property::getPropertyMortgage() const {
    return propertyMortgage;
}

int Property::getOwner() const {
    return owner;
}

int Property::getHousePrice() const {
    return housePrice;
}


int Property::getHouseAmount() const {
    return houseAmount;
}

std::string Property::getColor() const {
    return color;
}

void Property::resetProperty(){
    this->houseAmount=0;
    this->updateRent();
    this->setOwner(-1);
}

void Property::updateRent(){

        // Position is not in the vector
    if(this->getHouseAmount()==0){
            this->setRent(this->getOriginalRent());
    }

    if(this->getHouseAmount()==1){
        if(this->getPosition()!=39 && 34){
            this->setRent(this->getRent()*5);
        }
        else if(this->getPosition()==34){
            this->setRent(150);
        }
        else if(this->getPosition()==39){
            this->setRent(200);
        }
    }
    else if(this->getHouseAmount()==2){
        switch(this->getId()){
        case 0: case 1: case 2: case 3: case 5: case 6: case 7: case 13: case 14: case 15: case 16: case 17: case 18: case 19: case 21:
            this->setRent(this->getRent()*3);
        case 4:
            this->setRent(100);
        case 8: case 9:
            this->setRent(200);
        case 10:
            this->setRent(220);
        case 11: case 12:
            this->setRent(250);
        case 20:
            this->setRent(500);
        }

    }
    else if(this->getHouseAmount()==3){
        switch(this->getId()){
        case 0: case 1: case 2: case 3: case 4: case 5: case 6:
            this->setRent(this->getRent()*3);
        case 7:
            this->setRent(500);
        case 8: case 9:
            this->setRent(550);
        case 10:
            this->setRent(600);
        case 11: case 12:
            this->setRent(700);
        case 13:
            this->setRent(750);
        case 14: case 15:
            this->setRent(800);
        case 16:
            this->setRent(850);
        case 17: case 18:
            this->setRent(900);
        case 19:
            this->setRent(1000);
        case 20:
            this->setRent(1100);
        case 21:
            this->setRent(1400);

        }
    }
    else if(this->getHouseAmount()==4){
        switch(this->getId()){
        case 0:
            this->setRent(160);
        case 1:
            this->setRent(320);
        case 2: case 3:
            this->setRent(400);
        case 4:
            this->setRent(450);
        case 5: case 6:
            this->setRent(625);
        case 7:
            this->setRent(700);
        case 8: case 9:
            this->setRent(700);
        case 10:
            this->setRent(800);
        case 11: case 12:
            this->setRent(875);
        case 13:
            this->setRent(925);
        case 14: case 15:
            this->setRent(975);
        case 16:
            this->setRent(1025);
        case 17: case 18:
            this->setRent(1100);
        case 19:
            this->setRent(1200);
        case 20:
            this->setRent(1300);
        case 21:
            this->setRent(1700);

        }
    }
    else if(this->getHouseAmount()==5){
        switch(this->getId()){
        case 0:
            this->setRent(250);
        case 1:
            this->setRent(450);
        case 2: case 3:
            this->setRent(550);
        case 4:
            this->setRent(600);
        case 5: case 6:
            this->setRent(750);
        case 7:
            this->setRent(900);
        case 8:
            this->setRent(900);
        case 9:
            this->setRent(950);
        case 10:
            this->setRent(1000);
        case 11: case 12:
            this->setRent(1050);
        case 13:
            this->setRent(1100);
        case 14: case 15:
            this->setRent(1150);
        case 16:
            this->setRent(1200);
        case 17: case 18:
            this->setRent(1275);
        case 19:
            this->setRent(1400);
        case 20:
            this->setRent(1500);
        case 21:
            this->setRent(2000);

        }
    }


}
