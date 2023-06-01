//
// Created by Даниил Вольгов on 31.03.2023.
//

#ifndef AISD2S_VAR4_VOLGOV_CUSTOMSET_H
#define AISD2S_VAR4_VOLGOV_CUSTOMSET_H

#include <iostream>

/**
 * CustomSet is a set of integers implemented as a binary search tree.
 */
class CustomSet {
public:
    /**
     * @brief Creates an empty set.
     */
    CustomSet() : root(nullptr) {} // default constructor

    /**
     * @brief Creates a set from another set.
     * @param other another set
     */
    CustomSet(const CustomSet& other) : root(nullptr) { // copy constructor
        copyTree(root, other.root); // copy the tree
    }

    /**
     * @brief Destroys the set.
     */
    ~CustomSet(); // destructor

    /**
     * @brief Assigns a set to another set.
     * @param other another set
     * @return reference to the set
     */
    CustomSet& operator=(const CustomSet& other); // copy assignment

    /**
     * @brief Prints the set in ascending order.
     */
    void print() const; // print the set

    /**
     * @brief Inserts a key into the set.
     * @param key key to insert
     * @return true if the key was inserted, false if the key was already in the set
     */
    bool insert(int key); // insert a key

    /**
     * @brief Checks if the set contains a key.
     * @param key key to check
     * @return true if the set contains the key, false otherwise
     */
    [[nodiscard]]
    bool contains(int key) const; // check if the set contains a key

    /**
     * @brief Erases a key from the set.
     * @param key key to erase
     * @return true if the key was erased, false if the key was not in the set
     */
    bool erase(int key); // erase a key

private:
    struct Node {
        int key; // key of the node
        Node* left; // left child
        Node* right; // right child

        explicit Node(int k) : key(k), left(nullptr), right(nullptr) {} // constructor
    };

    Node* root; // root of the tree

    /**
     * @brief Destroys the tree.
     * @param node root of the tree
     */
    void clear(Node* node); // clear the tree

    /**
     * @brief Copies a tree.
     * @param dest root of the destination tree
     * @param src root of the source tree
     */
    void copyTree(Node*& dest, Node* src); // copy the tree

    /**
     * @brief Prints the tree in ascending order.
     * @param node root of the tree
     */
    void printInOrder(Node* node) const; // print the tree in ascending order

    /**
     * @brief Inserts a key into the tree.
     * @param node root of the tree
     * @param key key to insert
     * @return true if the key was inserted, false if the key was already in the tree
     */
    bool insert(Node*& node, int key); // insert a key

    /**
     * @brief Checks if the tree contains a key.
     * @param node root of the tree
     * @param key key to check
     * @return true if the tree contains the key, false otherwise
     */
    [[nodiscard]]
    bool contains(Node* node, int key) const; // check if the tree contains a key

    /**
     * @brief Finds the minimum node in the tree.
     * @param node root of the tree
     * @return pointer to the minimum node
     */
    static Node* findMin(Node* node) { // find the minimum node in the tree
        while (node->left) { // go to the leftmost node
            node = node->left; // go to the left child
        }
        return node; // return the minimum node
    }

    /**
     * @brief Erases a key from the tree.
     * @param node root of the tree
     * @param key key to erase
     * @return true if the key was erased, false if the key was not in the tree
     */
    bool erase(Node*& node, int key); // erase a key
};


#endif //AISD2S_VAR4_VOLGOV_CUSTOMSET_H
