//
// Created by Даниил Вольгов on 23.03.2023.
//

#include <iostream>
#include "set.h"

/*
// copy constructor
set::set(const set &other) {

}

// destructor
set::~set() {
    delete[] _data;
}

// operator=
set &set::operator=(const set &other) {
    if (this != &other) {
        delete[] _data;
        _size = other._size;
        _capacity = other._capacity;
        _data = new int[_capacity];
        for (int i = 0; i < _size; i++) {
            _data[i] = other._data[i];
        }
    }
    return *this;
}

// print
void set::print() const {
    for (int i = 0; i < _size; i++) {
        std::cout << _data[i] << " ";
    }
    std::cout << std::endl;
}

// insert
bool set::insert(int key) {
    if (contains(key)) {
        return false;
    }
    if (_size == _capacity) {
        _capacity *= 2;
        int *new_data = new int[_capacity];
        for (int i = 0; i < _size; i++) {
            new_data[i] = _data[i];
        }
        delete[] _data;
        _data = new_data;
    }
    _data[_size] = key;
    _size++;
    return true;
}

// contains
bool set::contains(int key) const {
    for (int i = 0; i < _size; i++) {
        if (_data[i] == key) {
            return true;
        }
    }
    return false;
}

// erase
bool set::erase(int key) {
    if (!contains(key)) {
        return false;
    }
    int index = 0;
    for (int i = 0; i < _size; i++) {
        if (_data[i] == key) {
            index = i;
            break;
        }
    }
    for (int i = index; i < _size - 1; i++) {
        _data[i] = _data[i + 1];
    }
    _size--;
    return true;
}
*/