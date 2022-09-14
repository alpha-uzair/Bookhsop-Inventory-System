#include <iostream>
#include "Bookshop.cpp"
using namespace std;
int main() {
    screenchangeFont(20);
    screenloginheader();
    User* userptr; Admin Boss; Customer Cus1;
    cout << "\t1. Login as Admin" << endl;
    cout << "\t2. Continue as Customer" << endl;
    cout << "\t3. Exit" << endl;
    int choice;
    cout << "\n\tEnter choice: ";
    cin >> choice;
    if (choice == 1) {
        userptr = &Boss;
        userptr->Login();
        Boss.MainMenu();
    }
    else if (choice == 2) {
        userptr = &Cus1;
        userptr->Login();
        Cus1.MainMenu();
    }
    else if (choice == 3) {
        system("pause>0");
    }

    return 0;
}
