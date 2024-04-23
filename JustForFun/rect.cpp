#include "rect.h"

Rectangle::Rectangle(int m_width, int m_height) :Shape(m_width, m_height){}

int Rectangle::area() {
	cout << "Rectangle Area is: " << width * height << endl;
	return 0;
}
