//
// Created by Даниил Вольгов on 23.03.2023.
//

#ifndef AISD2S_VAR4_VOLGOV_SET_H
#define AISD2S_VAR4_VOLGOV_SET_H

// binary search
class set {
private:
    struct node {
        int key;
        node *left;
        node *right;
        node(int key, node *left, node *right) : key(key), left(left), right(right) {}
    };
public:
    // copy constructor
    set(const set &other) {
        
    }

    // destructor
    ~set();
    // operator=
    set &operator=(const set &other);
    // print
    void print() const;
    // insert
    bool insert(int key);
    // contains
    bool contains(int key) const;
    // erase
    bool erase(int key);
};


#endif //AISD2S_VAR4_VOLGOV_SET_H
