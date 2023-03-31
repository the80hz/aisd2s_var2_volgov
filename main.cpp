#include <iostream>
#include "set.h"

// generator
size_t lcg(){
    static size_t x = 0;
    x = (1021*x+24631) % 116640;
    return x;
}

class CustomSet {
public:
    CustomSet() : root(nullptr) {}

    CustomSet(const CustomSet& other) : root(nullptr) {
        copyTree(root, other.root);
    }

    ~CustomSet() {
        clear(root);
    }

    CustomSet& operator=(const CustomSet& other) {
        if (this != &other) {
            clear(root);
            copyTree(root, other.root);
        }
        return *this;
    }

    void print() const {
        printInOrder(root);
        std::cout << std::endl;
    }

    bool insert(int key) {
        return insert(root, key);
    }

    [[nodiscard]] bool contains(int key) const {
        return contains(root, key);
    }

    bool erase(int key) {
        return erase(root, key);
    }

private:
    struct Node {
        int key;
        Node* left;
        Node* right;

        explicit Node(int k) : key(k), left(nullptr), right(nullptr) {}
    };

    Node* root;

    void clear(Node* node) {
        if (node) {
            clear(node->left);
            clear(node->right);
            delete node;
        }
    }

    void copyTree(Node*& dest, Node* src) {
        if (src) {
            dest = new Node(src->key);
            copyTree(dest->left, src->left);
            copyTree(dest->right, src->right);
        }
    }

    void printInOrder(Node* node) const {
        if (node) {
            printInOrder(node->left);
            std::cout << node->key << " ";
            printInOrder(node->right);
        }
    }

    bool insert(Node*& node, int key) {
        if (!node) {
            node = new Node(key);
            return true;
        }

        if (key < node->key) {
            return insert(node->left, key);
        } else if (key > node->key) {
            return insert(node->right, key);
        } else {
            return false; // Element already exists
        }
    }

    bool contains(Node* node, int key) const {
        if (!node) {
            return false;
        }

        if (key < node->key) {
            return contains(node->left, key);
        } else if (key > node->key) {
            return contains(node->right, key);
        } else {
            return true; // Element found
        }
    }

    static Node* findMin(Node* node) {
        while (node->left) {
            node = node->left;
        }
        return node;
    }

    bool erase(Node*& node, int key) {
        if (!node) {
            return false; // Element not found
        }

        if (key < node->key) {
            return erase(node->left, key);
        } else if (key > node->key) {
            return erase(node->right, key);
        } else {
            if (!node->left && !node->right) {
                delete node;
                node = nullptr;
            } else if (!node->left) {
                Node* temp = node;
                node = node->right;
                delete temp;
            } else if (!node->right) {
                Node* temp = node;
                node = node->left;
                delete temp;
            } else {
                node->key = findMin(node->right)->key;
                return erase(node->right, node->key);
            }
            return true; // Element deleted
        }
    }
};


int main() {
    CustomSet mySet;

    // Insert elements
    mySet.insert(5);
    mySet.insert(3);
    mySet.insert(8);
    mySet.insert(1);
    mySet.insert(4);

    // Print the set
    std::cout << "My set: ";
    mySet.print();

    // Check for presence of elements
    std::cout << "Contains 3: " << mySet.contains(3) << std::endl;
    std::cout << "Contains 7: " << mySet.contains(7) << std::endl;

    // Delete elements
    mySet.erase(3);
    mySet.erase(8);

    // Print the set after deleting elements
    std::cout << "My set after deletions: ";
    mySet.print();

    // Create a copy of the set using the copy constructor
    CustomSet copiedSet(mySet);

    // Print the copied set
    std::cout << "Copied set: ";
    copiedSet.print();

    // Create a new set and assign the original set using the assignment operator
    CustomSet assignedSet;
    assignedSet = mySet;

    // Print the assigned set
    std::cout << "Assigned set: ";
    assignedSet.print();

    return 0;
}