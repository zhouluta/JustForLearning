#include "init.h"

class Trapezoid{
    private:
        float upper_base;
        float lower_base;
        float height;
        float area;
    
    public:
        Trapezoid();
        Trapezoid(float upper_base, float lower_base, float height);
        Trapezoid(Trapezoid &t);
        
        ~Trapezoid();
        float getArea();
        void setUpperBase(float upper_base);
        void setLowerBase(float lower_base);
        void setHeight(float height);
        float getUpperBase();
        float getLowerBase();
        float getHeight();
};

Trapezoid::Trapezoid(){

}

Trapezoid::Trapezoid(float upper_base, float lower_base, float height){
    this->upper_base = upper_base;
    this->lower_base = lower_base;
    this->height = height;
}

Trapezoid::Trapezoid(Trapezoid &t){
    this->upper_base = t.upper_base;
    this->lower_base = t.lower_base;
    this->height = t.height;
}

Trapezoid::~Trapezoid(){

}

void Trapezoid::setUpperBase(float upper_base){
    this->upper_base = upper_base;
}

void Trapezoid::setLowerBase(float lower_base){
    this->lower_base = lower_base;
}

void Trapezoid::setHeight(float height){
    this->height = height;
}

float Trapezoid::getUpperBase(){
    return this->upper_base;
}

float Trapezoid::getLowerBase(){
    return this->lower_base;
}

float Trapezoid::getArea(){
    return (this->upper_base + this->lower_base) * this->height / 2;
}

float Trapezoid::getHeight(){
    return this->height;
}


int main(){
    cout << "Create a trapezoid: " << endl;
    Trapezoid t1;
    float temp_value;

    cout << "upper base >> ";
    cin >> temp_value;
    t1.setUpperBase(temp_value);

    cout << "lower base >> ";
    cin >> temp_value;
    t1.setLowerBase(temp_value);

    cout << "height: ";
    cin >> temp_value;
    t1.setHeight(temp_value);

    cout << "The trapezoid's upper base is " << t1.getUpperBase() << ", lower base is " << t1.getLowerBase() << ", height is " << t1.getHeight() << endl;
    cout << "And the area is " << t1.getArea() << endl;
    
    Trapezoid t2(t1);
    cout << "The copied trapezoid's area is " << t2.getArea() << endl;

    return 0;
}

