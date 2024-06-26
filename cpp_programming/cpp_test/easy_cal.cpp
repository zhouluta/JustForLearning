#include "init.h"

int main(){
    int x = 0, y = 0;
    char op;
    cout << "number1 operator number2" << endl;
    cin >> x >> op >> y;
    int sum = 0;
    switch(op){
        case '+':
            sum = x + y;
            break;
        case '-':
            sum = x - y;
            break;
        case '*':
            sum = x * y;
            break;
        case '/':
            sum = x / y;
            break;
    }
    cout << x << " " << op << " " << y << " = " << sum << endl;

    return 0;
}