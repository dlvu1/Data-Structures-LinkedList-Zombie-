/*
Name: Duyen Vu
Date: 07/03/2023
Description: Assignment 4 Data Structures
Usage:
*/

#ifndef ZOMBIE_VU_H
#define ZOMBIE_VU_H

#include <iostream>

class Zombie {
public:
    // Constructors
    Zombie();
    Zombie(char type);

    // Get method for type
    char getType() const;

    // Operator
    bool operator==(Zombie other);

    // Friend function
    friend std::ostream& operator<<(std::ostream& os, const Zombie& zombie);

private:
    // Properties
    char type;
};

#endif // ZOMBIE_VU_H