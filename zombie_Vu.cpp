/*
Name: Duyen Vu
Date: 07/03/2023
Description: Assignment 4 Data Structures
Usage:
*/

#include "zombie_Vu.h"
#include <string>
#include <iostream>

// Default constructor
Zombie::Zombie() {
    type = ' ';
}

Zombie::Zombie(char newType) {
    type =newType;
}

// Get method for type
char Zombie::getType() const {
    return type;
}

// Operator==
bool Zombie::operator==(Zombie other) {
    // Return true if the type match
    if (other.type == getType()) {
        return true;
    }
    // Otherwise return false
    else {
        return false;
    }
}

// Friend function 
std::ostream& operator<<(std::ostream& os, const Zombie& zombie) {
    return os << "[" << zombie.getType() << "]";
}
