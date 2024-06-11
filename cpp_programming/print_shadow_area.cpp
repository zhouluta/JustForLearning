#include "init.h"
#include <math.h>

#define pie 3.14

struct Point{
    float x;
    float y;
};

struct Shadow{
    float origin_x;
    float origin_y;
    float s_circle_radius;
    float b_circle_radius;
};

int main(){
    Point p;
    cout << "Create a point: " << endl;
    cout << "x >> ";
    cin >> p.x;
    cout << "y >> ";
    cin >> p.y;
    
    Shadow shadow;
    shadow.origin_x = 0;
    shadow.origin_y = 0;
    shadow.s_circle_radius = 2;
    shadow.b_circle_radius = 4;

    float distence = sqrt(pow(p.x - shadow.origin_x, 2) + pow(p.y - shadow.origin_y, 2));
    if(distence >= 2 && distence <= 4){
        cout << "Point p is in the shadow, and the area of shadow is " << pie * (pow(shadow.b_circle_radius, 2) - pow(shadow.s_circle_radius, 2)) << ".\n";
    }else{
        cout << "Point p is not in the shadow.\n";
    }

    return 0;
}