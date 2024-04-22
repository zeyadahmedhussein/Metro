#include <iostream>

void nestedSwitch(char outerCase, int innerCase) {
    using namespace std; // Adding namespace std

    switch (outerCase) {
        case '1': // Change case values to characters
            switch (innerCase) {
                case 1:
                    cout << "Outer Case 1, Inner Case 1" << endl;
                    break;
                case 2:
                    cout << "Outer Case 1, Inner Case 2" << endl;
                    break;
                default:
                    cout << "Invalid Inner Case for Outer Case 1" << endl;
            }
            break;
        case '2': // Change case values to characters
            switch (innerCase) {
                case 1:
                    cout << "Outer Case 2, Inner Case 1" << endl;
                    break;
                case 2:
                    cout << "Outer Case 2, Inner Case 2" << endl;
                    break;
                default:
                    cout << "Invalid Inner Case for Outer Case 2" << endl;
            }
            break;
        case '3': // Change case values to characters
            switch (innerCase) {
                case 1:
                    cout << "Outer Case 3, Inner Case 1" << endl;
                    break;
                case 2:
                    cout << "Outer Case 3, Inner Case 2" << endl;
                    break;
                default:
                    cout << "Invalid Inner Case for Outer Case 3" << endl;
            }
            break;
        case '4': // Change case values to characters
            switch (innerCase) {
                case 1:
                    cout << "Outer Case 4, Inner Case 1" << endl;
                    break;
                case 2:
                    cout << "Outer Case 4, Inner Case 2" << endl;
                    break;
                default:
                    cout << "Invalid Inner Case for Outer Case 4" << endl;
            }
            break;
        default:
            cout << "Invalid Outer Case" << endl;
    }
}

int main() {
    char outer = '2'; // Change outer to char
    int inner = 1;
    nestedSwitch(outer, inner);
    return 0;
}
