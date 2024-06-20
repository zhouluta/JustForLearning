#pragma once
#include <iostream>
using namespace std;

class Shape {
protected:
    int width, height;
public:
    Shape(int, int);
    
    virtual int area();
    
};