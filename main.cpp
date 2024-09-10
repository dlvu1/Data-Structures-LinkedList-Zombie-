/*
Name: Duyen Vu
Date: 07/04/2023
Description: Assignment 4 Data Structures
Usage:
*/

#include "linkedlist_Vu.hpp"
#include "zombie_Vu.h"
#include <iostream>
#include <cstdlib>  // for std::atoi
#include <ctime>    // for time and srand

void engine_action(LinkedList<Zombie>& list, Zombie randomZomb);
void caboose_action(LinkedList<Zombie>& list, Zombie randomZomb);
void jump_in_action(LinkedList<Zombie>& list, Zombie randomZomb);
void everyone_out_action(LinkedList<Zombie>& list, Zombie randomZomb);
void you_out_action(LinkedList<Zombie>& list, Zombie randomZomb);
void brains_action(LinkedList<Zombie>& list, Zombie randomZomb);
void rainbow_action(LinkedList<Zombie>& list, Zombie randomZomb);
void friends_action(LinkedList<Zombie>& list, Zombie randomZomb);
std::string getActionString(int randomAction);
char getColorChar(int randomZombie);

// Engine! Function to make this zombie the first zombie in the conga line
void engine_action(LinkedList<Zombie>& list, Zombie randomZomb) {
    // Add zombie to the front
    list.AddToFront(randomZomb);
}

// Caboose! Function to make this zombie the last zombie in the conga line
void caboose_action(LinkedList<Zombie>& list, Zombie randomZomb) {
    // Add zombie to the end
    list.AddToEnd(randomZomb);
}

// Jump in the Line! Function to make this zombie join the conga line at position X where X <= length of the linked list
void jump_in_action(LinkedList<Zombie>& list, Zombie randomZomb) {
    int listLength = list.Length();
    
    // Add the zombie to the end (front) of the list if only 1 or 0 in the list
    if (listLength <= 1) {
        list.AddToEnd(randomZomb);
        return;
    }
    
    // Generate a random index between 0 and listLength to insert the zombie
    int position = rand() % (listLength + 1);

    // Use the AddAtIndex function to insert the zombie
    list.AddAtIndex(randomZomb, position);
}
    
// Everyone Out!
void everyone_out_action(LinkedList<Zombie>& list, Zombie randomZomb) {
    list.RemoveAllOf(randomZomb);
}

// You Out!
void you_out_action(LinkedList<Zombie>& list, Zombie randomZomb) {
    list.RemoveTheFirst(randomZomb);
}

// Brains!
void brains_action(LinkedList<Zombie>& list, Zombie randomZomb) {
    // Create two new zombies with the same type
    Zombie newZombie1(randomZomb.getType());
    Zombie newZombie2(randomZomb.getType());
    
    // Add the new zombies using engine_action and caboose_action
    engine_action(list, newZombie1);
    caboose_action(list, newZombie2);
    
    // Search for a position to insert a zombie in the middle
    int length = list.Length();
    int middleIndex = length / 2;
    
    // Find the node at the middleIndex
    Node<Zombie>* currentNode = list.Find(middleIndex);
    
    // If the current node is null, add to the end
    if (currentNode == nullptr) {
        list.AddToEnd(randomZomb);
    // Add the third new zombie before the current node
    } else {
        list.AddBefore(currentNode, randomZomb);
    }
}

// Rainbow Brains!
void rainbow_action(LinkedList<Zombie>& list, Zombie randomZomb) {
    // Perform engine_action on the zombie
    engine_action(list, randomZomb);
    
    // Add zombies of different colors to the end using caboose_action
    list.AddToFront(randomZomb);
    caboose_action(list, Zombie('R'));
    caboose_action(list, Zombie('Y'));
    caboose_action(list, Zombie('G'));
    caboose_action(list, Zombie('B'));
    caboose_action(list, Zombie('C'));
    caboose_action(list, Zombie('M'));
}

// Making new Friends!
void friends_action(LinkedList<Zombie>& list, Zombie randomZomb) {
    // Find the first zombie that has the same color
    Node<Zombie>* current = list.Find(randomZomb);
    
    // Do a coin flip to decide whether insert before or after the found zombie
    if (current != nullptr) {
        srand(static_cast<unsigned>(time(0))); 
        bool insertBefore = rand() % 2 == 0;
        
        if (insertBefore) {
            list.AddBefore(current, randomZomb);
        } else {
            list.AddAfter(current, randomZomb);
        }
        
    } else {
        // Perform caboose_action if no zombie the same
        list.AddToEnd(randomZomb);
    }
}

// Function to get the Zombie color
char getColorChar(int randomZombie) {
    switch (randomZombie) {
        case 0:
            return 'R';
        case 1:
            return 'Y';
        case 2:
            return 'G';
        case 3:
            return 'B';
        case 4:
            return 'C';
        case 5:
            return 'M';
        default:
            return '\0';
    }
}

// Function to get the action string
std::string getActionString(int randomAction) {
    switch (randomAction) {
        case 0:
            return "Engine";
        case 1:
            return "Caboose";
        case 2:
            return "Jump in the Line";
        case 3:
            return "Everyone Out";
        case 4:
            return "You Out";
        case 5:
            return "Brains";
        case 6:
            return "Rainbow Brains";
        case 7:
            return "Making new Friends";
        default:
        return "Invalid action!";
    }
}

int main(int argc, char* argv[]) {
    
    int recurringChoice = 1;
    int numRounds = 0;
    
    // Set up the initial Conga Line 
    LinkedList<Zombie> myLinkedList = LinkedList<Zombie>();
    
    // Let the user entered a seed for the generator
    if (argc >= 3 && std::string(argv[1]) == "-s") {
        srand(std::atoi(argv[2]));
    }
    else {
        srand(static_cast<unsigned int>(time(0)));
    }
    
    while (recurringChoice == 1) {
        // Ask the user how many rounds they want to run
        std::cout << "How many rounds you want to run?" << std::endl;
        std::cin >> numRounds;
        
        // Run the conga party for the specified rounds
        for (int round = 1; round <= numRounds; round++) {
            
            // Perform the action based on rand() % 8, and perform the color based on rand() % 6
            int randomAction = rand() % 8;
            Zombie randomZombie = Zombie(getColorChar(rand() % 6));
            
            // Run a Rainbow Brains Action
            rainbow_action(myLinkedList, randomZombie);
            brains_action(myLinkedList, randomZombie);
            brains_action(myLinkedList, randomZombie);
            brains_action(myLinkedList, randomZombie);

            // Check if it's a multiple of 5 to delete the first and last zombies
            if (round % 5 == 0) {
                myLinkedList.RemoveFromFront();
                myLinkedList.RemoveFromEnd();
                if (myLinkedList.Length() == 0) {
                    std::cout << "The Party is Over." << std::endl;
                    break;
                }
            }
            
            std::cout << "Round: " << round << std::endl;
            std::cout << "Size: " << myLinkedList.Length() << " :: ";
            myLinkedList.PrintList();
            std::cout << std::endl;
        
        switch (randomAction) {
                case 0:
                    engine_action(myLinkedList, randomZombie);
                    break;
                case 1:
                    caboose_action(myLinkedList, randomZombie);
                    break;
                case 2:
                    jump_in_action(myLinkedList, randomZombie);
                    break;
                case 3:
                    everyone_out_action(myLinkedList, randomZombie);
                    break;
                case 4:
                    you_out_action(myLinkedList, randomZombie);
                    break;
                case 5:
                    brains_action(myLinkedList, randomZombie);
                    break;
                case 6:
                    rainbow_action(myLinkedList, randomZombie);
                    break;
                case 7:
                    friends_action(myLinkedList, randomZombie);
                    break;
                default:
                    std::cout << "Invalid action!" << std::endl;
                    break;
            }
            
            // Get the action string
            std::string actionStr = getActionString(randomAction);
            
            std::cout << "New Zombie: [" << randomZombie.getType() << "] -- Action: [" << actionStr << "]" << std::endl;
            std::cout << "The conga line is now:" << std::endl;
            std::cout << "Size: " << myLinkedList.Length() << " :: ";
            myLinkedList.PrintList();
            std::cout << std::endl;
            std::cout << "**************************************************" << std::endl;
        }
        
        recurringChoice--;
        
        // Empty the linked list for the next party
        myLinkedList.Empty();
    }

    return 0;
}