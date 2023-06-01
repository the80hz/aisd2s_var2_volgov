//
// Created by Даниил Вольгов on 31.03.2023.
//

#include "CustomSet.h"

/**
* @brief Destroys the set.
*/
CustomSet::~CustomSet() { // destructor
    clear(root); // call the clear function
}

/**
 * @brief Assigns a set to another set.
 * @param other another set
 * @return reference to the set
 */
CustomSet &CustomSet::operator=(const CustomSet &other) { // copy assignment
    if (this != &other) { // check for self-assignment
        clear(root); // call the clear function
        copyTree(root, other.root); // call the copyTree function
    }
    return *this; // return the reference to the set
}

/**
 * @brief Prints the set in ascending order.
 */
void CustomSet::print() const { // print the set
    printInOrder(root); // call the printInOrder function
    std::cout << std::endl; // print a new line
}

/**
 * @brief Inserts a key into the set.
 * @param key key to insert
 * @return true if the key was inserted, false if the key was already in the set
 */
bool CustomSet::insert(int key) { // insert a key
    return insert(root, key); // call the insert function
}

/**
 * @brief Checks if the set contains a key.
 * @param key key to check
 * @return true if the set contains the key, false otherwise
 */
[[nodiscard]]
bool CustomSet::contains(int key) const { // check if the set contains a key
    return contains(root, key); // call the contains function
}

/**
 * @brief Erases a key from the set.
 * @param key key to erase
 * @return true if the key was erased, false if the key was not in the set
 */
bool CustomSet::erase(int key) { // erase a key
    return erase(root, key); // call the erase function
}

/**
 * @brief Destroys the tree.
 * @param node root of the tree
 */
void CustomSet::clear(CustomSet::Node *node) { // destroy the tree
    if (node) { // check if the node is not null
        clear(node->left); // call the clear function for the left child
        clear(node->right); // call the clear function for the right child
        delete node; // delete the node
    }
}

/**
 * @brief Copies a tree.
 * @param dest root of the destination tree
 * @param src root of the source tree
 */
void CustomSet::copyTree(CustomSet::Node *&dest, CustomSet::Node *src) { // copy the tree
    if (src) { // check if the node is not null
        dest = new Node(src->key); // create a new node
        copyTree(dest->left, src->left); // call the copyTree function for the left child
        copyTree(dest->right, src->right); // call the copyTree function for the right child
    }
}

/**
 * @brief Prints the tree in ascending order.
 * @param node root of the tree
 */
void CustomSet::printInOrder(CustomSet::Node *node) const { // print the tree in ascending order
    if (node) { // check if the node is not null
        printInOrder(node->left); // call the printInOrder function for the left child
        std::cout << node->key << " "; // print the key
        printInOrder(node->right); // call the printInOrder function for the right child
    }
}

/**
 * @brief Inserts a key into the tree.
 * @param node root of the tree
 * @param key key to insert
 * @return true if the key was inserted, false if the key was already in the tree
 */
bool CustomSet::insert(CustomSet::Node *&node, int key) {
    if (!node) { // Element not found
        node = new Node(key); // Create a new node
        return true; // Element inserted
    }

    if (key < node->key) { // Element is less than the current node
        return insert(node->left, key); // Insert into the left subtree
    } else if (key > node->key) { // Element is greater than the current node
        return insert(node->right, key); // Insert into the right subtree
    } else { // Element is equal to the current node
        return false; // Element already exists
    }
}

/**
 * @brief Checks if the tree contains a key.
 * @param node root of the tree
 * @param key key to check
 * @return true if the tree contains the key, false otherwise
 */
[[nodiscard]]
bool CustomSet::contains(CustomSet::Node *node, int key) const {
    if (!node) { // Element not found
        return false; // Element not found
    }

    if (key < node->key) { // Element is less than the current node
        return contains(node->left, key); // Search in the left subtree
    } else if (key > node->key) { // Element is greater than the current node
        return contains(node->right, key); // Search in the right subtree
    } else { // Element is equal to the current node
        return true; // Element found
    }
}

/**
 * @brief Erases a key from the tree.
 * @param node root of the tree
 * @param key key to erase
 * @return true if the key was erased, false if the key was not in the tree
 */
bool CustomSet::erase(CustomSet::Node *&node, int key) {
    if (!node) { // Element not found
        return false; // Element not found
    }

    if (key < node->key) { // Element is less than the current node
        return erase(node->left, key); // Erase from the left subtree
    } else if (key > node->key) { // Element is greater than the current node
        return erase(node->right, key); // Erase from the right subtree
    } else { // Element is equal to the current node
        if (!node->left && !node->right) { // Node is a leaf
            delete node; // Delete the node
            node = nullptr; // Set the node to null
        } else if (!node->left) { // Node has only a right child
            Node* temp = node; // Save the node
            node = node->right; // Set the node to the right child
            delete temp; // Delete the node
        } else if (!node->right) { // Node has only a left child
            Node* temp = node; // Save the node
            node = node->left; // Set the node to the left child
            delete temp; // Delete the node
        } else { // Node has two children
            node->key = findMin(node->right)->key; // Replace the key with the minimum key in the right subtree
            return erase(node->right, node->key); // Erase the minimum key in the right subtree
        }
        return true; // Element deleted
    }
}

/**
 * @brief Returns the number of elements in the set.
 * @return number of elements in the set
 */
std::vector<int> CustomSet::getSortedElements() const { // get the elements in ascending order
    std::vector<int> elements; // create a vector to store the elements
    inorderTraversal(root, elements); // call the inorderTraversal function
    return elements; // return the elements
}

/**
 * @brief Traverses the tree in ascending order.
 * @param node root of the tree
 * @param elements vector to store the elements
 */
void CustomSet::inorderTraversal(CustomSet::Node *node, std::vector<int> &elements) const { // traverse the tree in ascending order
    if (node == nullptr) { // check if the node is null
        return;
    }
    inorderTraversal(node->left, elements); // call the inorderTraversal function for the left child
    elements.push_back(node->key); // add the key to the vector
    inorderTraversal(node->right, elements); // call the inorderTraversal function for the right child
}
