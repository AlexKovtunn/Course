#pragma once
#include "elem.h"
#ifndef STACK_H
#define STACK_H

class stack {
private:
    size_t size;
    element* top;
public:
    stack() {
        size = 0;
        top = nullptr;
    }

    ~stack() {
        clear();
    }

    element getTop() {
        return *top;
    }

    void pop()
    {
        element* temp = top;
        top = top->getNext();
        delete temp;
        size--;
    }

    void push(strl value) {
        top = new element(value, top);
        size++;
    }

    void push(double value) {
        top = new element(value, top);
        size++;
    }

    size_t getSize() {
        return size;
    }
    bool isEmpty() {
        if (size == 0) return true;
        else return false;
    }

    void clear() {
        while (!isEmpty()) pop();
    }

};

#endif // !STACK_H