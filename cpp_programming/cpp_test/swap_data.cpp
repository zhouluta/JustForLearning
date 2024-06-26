#include "init.h"

/*
* Swap two known value
*/

void swap_value(int &x, int &y){
    int temp;
    temp = x;
    x = y;
    y = temp;
}

int main(){
    int x = 0, y = 0;
    cout << "input value: " << endl;
    cout << "x >> ";
    cin >> x;
    cout << "y >> ";
    cin >> y;
    swap_value(x, y);
    cout << "after swapping, x = " << x << ", y = " << y << endl;

    return 0;
}