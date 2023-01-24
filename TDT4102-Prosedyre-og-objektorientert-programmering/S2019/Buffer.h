#pragma once

#include <string>
#include <cassert>
using namespace std;

#include <iostream>



class RingBuf {
private:
    char* buf;    // The underlying buffer
    int capacity; // Capacity of underlying buffer (max size)
    int start;    // Start of valid data
    int size;     // Size of valid data (0 if empty)
public:
    RingBuf(int capacity);
    RingBuf(const RingBuf &other); // copy constructor
    RingBuf(RingBuf &&other); // move constructor
    ~RingBuf();
    RingBuf& operator=(RingBuf rhs); // assignment operator, copy assignment
    void write(char c); // write a character to the buffer
    void write(string s); // write a string of characters to the buffer
    char read(); // read a char from the buffer
    string read(int count); // read a number of chars from the buffer
    string peek();
    friend void testRingBuf();
};

void testRingBuf();