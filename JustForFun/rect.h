#pragma once
#include "shape.h"

class Rectangle : public Shape {
public:
    Rectangle(int, int);

    int area();
    
};