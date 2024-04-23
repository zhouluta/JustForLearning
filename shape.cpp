#include "shape.h"

Shape::Shape(int m_width = 0, int m_height = 0){
	width = m_width;
	height = m_height;
}

int Shape::area() {
	cout << "Shape Area: " << width * height;
	return 0;
}
