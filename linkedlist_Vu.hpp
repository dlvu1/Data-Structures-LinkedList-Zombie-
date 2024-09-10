/*
Name: Duyen Vu
Date: 07/03/2023
Description: Assignment 4 Data Structures
Usage:
*/

#include <iostream>

// Define a Node structure to hold the data and pointers to the next and previous nodes.
template <typename T> 
struct Node {
private:
    T data;
    Node<T>* next;
    Node<T>* previous;
    
public:
    Node() : next(nullptr), previous(nullptr) {}
    Node(T data) : data(data), next(nullptr), previous(nullptr) {}
    Node(T data, Node<T>* next) : data(data), next(next), previous(nullptr) {}

    T getData() const { 
        return data; 
        
    }
    void setData(T data) { 
        this->data = data; 
        
    }

    Node<T>* getNext() const {
        return next; 
    }
    
    void setNext(Node<T>* next) {
        this->next = next; 
    }

    Node<T>* getPrevious() const {
        return previous; 
    }
    
    void setPrevious(Node<T>* previous) {
        this->previous = previous; 
    }
};

template <typename T>
class LinkedList {
    
private:
    Node<T>* head;
    Node<T>* tail;
    int size;

public:
    LinkedList();
    void AddToFront(T data);
    void AddToEnd(T data);
    void AddAtIndex(T data, int index);
    void AddBefore(Node<T>* node, T data);
    void AddAfter(Node<T>* node, T data);
    
    T RemoveFromFront();
    T RemoveFromEnd();
    void RemoveTheFirst(T data);
    void RemoveAllOf(T data);
    T RemoveBefore(Node<T>*);
    T RemoveAfter(Node<T>*);
    
    bool ElementExists(T data);
    Node<T>* Find(T data);
    int IndexOf(T data);
    
    T RetrieveFront();
    T RetrieveEnd();
    T Retrieve(int index);
    
    void PrintList();
    void Empty();
    int Length();
    
    ~LinkedList() {
        Empty();
    }
};

    template <typename T>
    LinkedList<T>::LinkedList() : head(nullptr), tail(nullptr), size(0) {}
    
    template <typename T>
    void LinkedList<T>::AddToFront(T data) {
        Node<T>* newNode = new Node<T>(data);  
        newNode->setNext(head);
        if (head != nullptr) { // If the list is not empty
            head->setPrevious(newNode); // Set head to the new node
        }
        head = newNode;
        if (tail == nullptr) {
            tail = newNode; // If the list is empty, update the tail point to the new node
        }
    size++;
}
    
    template <typename T>
    void LinkedList<T>::AddToEnd(T data) {
        Node<T>* newNode = new Node<T>(data);
        if (head == nullptr) {   // If head is null
            head = tail = newNode;
        } else {
             // Update the tail to point to the recently added node
            newNode->setPrevious(tail);
            tail->setNext(newNode);
            tail = newNode;
        }
        size++;
    }
    
    template <typename T>
    void LinkedList<T>::AddAtIndex(T data, int index) {
        if (index < 0 ||  index > size) {
            throw std::out_of_range("Out of range!");
        }
        // Add a new node to the front if index is 0
        if (index == 0) {
            AddToFront(data);
        // Insert a new node to the end if index is equal to the size
        } else if (index == size) {
            AddToEnd(data);
        // Add a new node neither at the front nor at the end
        } else {
            Node<T>* newNode = new Node<T>(data);
            Node<T>* current = head;
            for (int i = 0; i < index - 1; i++) {
                current = current->getNext();
            }
            newNode->setNext(current->getNext());
            newNode->setPrevious(current);
            current->getNext()->setPrevious(newNode);
            current->setNext(newNode);
            size++;
        }
    }

    template <typename T>
    void LinkedList<T>::AddBefore(Node<T>* node, T data) {
        if (node == nullptr) {
            throw std::invalid_argument("Invalid node pointer!");
        }
        // Add a new node to the front if node == head
        if (node == head) {
            AddToFront(data);
          // If the inserted node is not the head, insert the new node before it
        } else {
            Node<T>* newNode = new Node<T>(data);
            newNode->setNext(node);
            newNode->setPrevious(node->getPrevious());
            node->getPrevious()->setNext(newNode);
            node->setPrevious(newNode);
            size++;
        }
    }

    template <typename T>
    void LinkedList<T>::AddAfter(Node<T>* node, T data) {
        if (node == nullptr) {
            throw std::invalid_argument("Invalid node pointer!");
        }
        // Add a new node to the end if node == tail
        if (node == tail) {
            AddToEnd(data);
        // Insert the new node after if the new node is not the tail
        } else {
            Node<T>* newNode = new Node<T>(data);
            newNode->setPrevious(node);
            newNode->setNext(node->getNext());
            node->getNext()->setPrevious(newNode);
            node->setNext(newNode);
            size++;
        }
    }

    template <typename T>
    T LinkedList<T>::RemoveFromFront() {
        if (head == nullptr) {
            throw std::runtime_error("Cannot remove from an empty list!");
        }
         // Get the data from the head then transfer it to the next node 
        Node<T>* temp = head;
        T data = temp->getData();
        
        if (head == tail) {
            head = tail = nullptr;
        } else {
            head = head->getNext();
            head->setPrevious(nullptr);
        }
        
        delete temp; // Remove the current head and update the pointers for the new head
        size--;
        return data;
    }
    
    template <typename T>
    T LinkedList<T>::RemoveFromEnd() {
        if (tail == nullptr) {
            throw std::runtime_error("Cannot remove from an empty list.");
        }
        
        // Get the data from the tail then transfer it to the prev node
        Node<T>* temp = tail;
        T data = temp->getData();

        if (head == tail) {
            head = tail = nullptr;
        } else {
            tail = tail->getPrevious();
            tail->setNext(nullptr);
        }
        
        delete temp; // Remove the current tail and update the pointers for the new tail node
        size--;
        return data;
    }

    template <typename T>
    void LinkedList<T>::RemoveTheFirst(T data) {
        Node<T>* current = head;
        // Look for the specified data
        while (current != nullptr) {
            if (current->getData() == data) {
                // If the node is the head, update the head to the next note
                if (current == head) {
                    RemoveFromFront();
                // If the node is the tail, update the tail to the prev note
                } else if (current == tail) {
                    RemoveFromEnd();
                // If the node to remove is neither the head nor the tail
                } else {
                    current->getPrevious()->setNext(current->getNext());
                    current->getNext()->setPrevious(current->getPrevious());
                    delete current;
                    size--;
                }
                return;
            }
            current = current->getNext();
        }
    }

    template <typename T>
    void LinkedList<T>::RemoveAllOf(T data) {
        Node<T>* current = head;
        while (current != nullptr) {
            Node<T>* nextNode = current->getNext();
            // Check if the current's data matches the specified data
            if (current->getData() == data) {
                // If the current node is the head, remove it from the front
                if (current == head) {
                    RemoveFromFront();
                // If the current node is the tail, remove it from the end
                } else if (current == tail) {
                RemoveFromEnd();
                } else {
                // If the current node is neither the head nor the tail
                current->getPrevious()->setNext(current->getNext());
                current->getNext()->setPrevious(current->getPrevious());
                delete current;
                size--;
                }
            }
        current = nextNode;
    }
}

    template <typename T>
    T LinkedList<T>::RemoveBefore(Node<T>* node) {
        if (node == nullptr || node == head) {
            throw std::invalid_argument("Invalid node or no node before it.");
        }
         // Look for the node before the given node and delete it
        Node<T>* before = node->getPrevious();
        if (before == nullptr) {
            return RemoveFromFront();
        }

        T data = before->getData();
        
        if (before == head) {
            RemoveFromFront();
        } else {
            before->getPrevious()->setNext(node);
            node->setPrevious(before->getPrevious());
            delete before;
            size--;
        }

        return data;
    }

    template <typename T>
    T LinkedList<T>::RemoveAfter(Node<T>* node) {
        if (node == nullptr || node == tail) {
            throw std::invalid_argument("Invalid node or no node after it.");
        }
        // Remove the node after the given node
        Node<T>* after = node->getNext();
        if (after == nullptr) {
            return RemoveFromEnd();
        }

        T data = after->getData();
        
        if (after == tail) {
            RemoveFromEnd();
        } else {
            node->setNext(after->getNext());
            after->getNext()->setPrevious(node);
            delete after;
            size--;
        }

        return data;
    }

    template <typename T>
    bool LinkedList<T>::ElementExists(T data) {
        Node<T>* current = head;
        // Go through the list to look for the specified data that exists in the list
        while (current != nullptr) {
            if (current->getData() == data) {
                return true;  // Return true if find one
            }
            current = current->getNext();  // Move to the next node
        }
        return false; // Return false if find nothing
    }

    template <typename T>
    Node<T>* LinkedList<T>::Find(T data) {
        // Go through the list to look for the first node containing the specified data
        Node<T>* current = head;
        while (current != nullptr) {
            if (current->getData() == data) {
                return current;  // Return the node if find the data
            }
            current = current->getNext();
        }
        return nullptr; // Return null if no data is found
    }

    template <typename T>
    int LinkedList<T>::IndexOf(T data) {
        Node<T>* current = head;
        int index = 0;
         // Check the list to find the index of the first node containing the specified data
        while (current != nullptr) {
            if (current->getData() == data) {
                return index; // Return the index if find the data
            }
            current = current->getNext();
            index++;
        }
        return -1; // Return null if no data is found
    }

    template <typename T>
    T LinkedList<T>::RetrieveFront() {
        if (head == nullptr) {
            throw std::runtime_error("List is empty.");
        }
        return head->getData();  // Return the data of the head
    }

    template <typename T>
    T LinkedList<T>::RetrieveEnd() {
        if (tail == nullptr) {
            throw std::runtime_error("List is empty."); // Return the data of the tail
        }
        return tail->getData();
    }

    template <typename T>
    T LinkedList<T>::Retrieve(int index) {
        if (index < 0 || index >= size) {
            throw std::out_of_range("Out of range!");
        }

        Node<T>* current = head;
        for (int i = 0; i < index; i++) {
            current = current->getNext();
        }

        return current->getData();
    }
    
    // Print the data of each node
    template <typename T>
    void LinkedList<T>::PrintList() {
        Node<T>* current = head;
        while (current != nullptr) {
            std::cout << current->getData(); // Use operator<< for Zombie
            if (current->getNext() != nullptr) {
            std::cout << "=";
        }
        current = current->getNext();
    }
}

    // Empty the list
    template <typename T>
    void LinkedList<T>::Empty() {
        Node<T>* currentNode = head;
        
        while (currentNode != nullptr) {
            Node<T>* nextNode = currentNode->getNext();
            delete currentNode; // Free the memory of the current node
            currentNode = nextNode;
        }
        
        head = tail = nullptr;
        size = 0;
    }

    // Return the size of the List
    template <typename T>
    int LinkedList<T>::Length() {
        return size;
    }

