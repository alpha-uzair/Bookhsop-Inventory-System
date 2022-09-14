#include "Bookshop.h"
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <sstream>
#include <vector>
using namespace std;
int main();
//
Book::Book(){
    Title="Null";
    ISBN="Null";
    Category="Null";
    Author="Null";
    Copies=0;
    Price=0;
}

//User Implementation//
void User::Login() {}
User::User() {
    Username = "password";
    Password = "username";
}
string User::getPassword() { return Password; }
string User::getUsername() { return Username; }
//Admin Implementation//
void Admin::Login() {
    system("cls");
    string UName;
    string Pword;
    while (true) {
        screenmainheader();
        cout <<endl<<endl<< std::setw(76) << right << "--------------------";
        cout <<endl<< std::setw(76) << right << "|  LOGIN AS ADMIN  |";
        cout <<endl<< std::setw(76) << right << "--------------------";
        cout << "\n\n\n\n";
        cout << std::setw(67) << right << "USERNAME: ";
        cin >> UName;
        cout <<endl<< std::setw(67) << right << "PASSWORD: ";
        cin >> Pword;
        try {
            if ((UName == getUsername()) && (Pword == getPassword())) {
                break;
            }
            else { throw 1; }
        }
        catch (int x) {
            cout <<endl<<endl<< std::setw(77) << right << "Incorrect Login Details" << endl;
            cout << std::setw(78) << right << "-------------------------" << endl;
            cout << "\n\n\tPress any Key to re-enter Login Details...";
            system("pause>0");
            system("cls");
        }
    }
}

void Admin::MainMenu() {
    system("cls");
    screenmainheader();
    screenmainmenu();
    cout << "\t1. Display all Books" << endl;
    cout << "\t2. Search Books" << endl;
    cout << "\t3. Add Books" << endl;
    cout << "\t4. Update Books" << endl;
    cout << "\t5. Delete Books" << endl;
    cout << "\t6. Low Stock" << endl;
    cout << "\t7. Log Out" << endl << endl << endl;//return main()//
    int choice;
    cout << "\tEnter your Choice: ";
    cin >> choice;
    switch (choice) {
    case 1:BA.DisplayBook(); MainMenu(); break;
    case 2:BA.SearchBookMenu(); MainMenu(); break;
    case 3:BA.AddBook(); MainMenu(); break;
    case 4:BA.UpdateBook(); MainMenu(); break;
    case 5:BA.DeleteBook(); MainMenu(); break;
    case 6:BA.LowStock(); MainMenu(); break;
    case 7:system("cls"); main(); break;
    }

}
//Customer Implementation//
void Customer::Login() {
    system("cls");
}
void Customer::MainMenu() {
    system("cls");
    screenmainheader();
    screenmainmenu();
    cout << "\t1. Search Books" << endl;
    cout << "\t2. Browse all Books" << endl;
    cout << "\t3. Order Books" << endl;
    cout << "\t4. Log Out" << endl;
    int choice;
    cout << "\n\tEnter your Choice: ";
    cin >> choice;
    switch (choice) {
    case 1:BU.SearchBookMenu(); MainMenu(); break;
    case 2:BU.DisplayBook(); MainMenu(); break;
    case 3:Order(); Billing(); MainMenu(); break;
    case 4:system("cls"); main(); break;
    }
}

//Book Implementation//
void Book::AddBook() {
    cin.ignore();
    system("cls");
    ofstream file("booklist.csv", ios::app);
    screenmainheader();
    cout << endl << std::setw(74) << right << "--------------" << endl;
    cout << std::setw(74) << right << "|  ADD BOOK  |" << endl;
    cout << std::setw(74) << right << "--------------" << endl << endl << endl << endl;
    cout << "\tEnter 4-digit Book ISBN: ";
    getline(cin, ISBN);
    while ((ISBN.length()) != 4) {
        cout << "\n\tInvalid ISBN\n\n\tPress any Key to Re-enter ISBN...";
        system("pause>0");
        system("cls");
        screenmainheader();
        cout << endl << std::setw(74) << right << "--------------" << endl;
        cout << std::setw(74) << right << "|  ADD BOOK  |" << endl;
        cout << std::setw(74) << right << "--------------" << endl << endl << endl << endl;
        cout << "\tEnter 4-digit Book ISBN: ";
        getline(cin, ISBN);
    }
    cout << "\tEnter Book Title: ";
    getline(cin, Title);
    cout << "\tEnter Book Category: ";
    getline(cin, Category);
    cout << "\tEnter Book Author: ";
    getline(cin, Author);
    cout << "\tEnter Book Price: ";
    cin >> Price;
    cout << "\tEnter Stock: ";
    cin >> Copies;
    file << ISBN << "," << Title << "," << Category << "," << Author << "," << Price << "," << Copies << endl;
    cout <<endl<< "\n\tBook Added Successfully";
    cout << "\n\n\tPress any Key to go to main menu...";
    system("pause>0");
}
void Book::DisplayBook() {
    system("cls");
    cin.ignore();
    ifstream Library;
    int count = 0;
    vector<string>row;
    string Attribute, Words;
    Library.open("booklist.csv");
    screenmainheader();
    cout << endl << std::setw(76) << right << "-------------------" << endl;
    cout << std::setw(76) << right << "|  DISPLAY BOOKS  |" << endl;
    cout << std::setw(76) << right << "-------------------" << endl << endl << endl << endl;

    cout << "\t\t      " << std::setw(8) << right << "ISBN" << std::setw(25) << left << "\t    TITLE" << std::setw(17) << left << " CATEGORY" << std::setw(16) << left << "AUTHOR" << std::setw(8) << left << "PRICE" << std::setw(10) << right << "COPIES" << endl;
    cout << "\t\t     -------------------------------------------------------------------------------------------" << endl;
    while (Library.good()) {
        while (getline(Library, Attribute)) {
            row.clear();
            istringstream s(Attribute);
            for (int i = 0; i < 6; i++) {
                getline(s, Words, ',');

                row.push_back(Words);
            }
            if (row[5] != "0") {
                // Print the found data
                count = 1;
                cout << "\t\t\t  " << row[0];
                cout << "\t   " << std::setw(23) << left << row[1];
                cout << std::setw(14) << left << row[2];
                cout << std::setw(18) << left << row[3];
                cout << std::setw(13) << left << row[4];
                cout << row[5];
                cout << endl;
            }
        }
        if (count == 0) {
            cout << "\n\n\tNo Book Available\n";
        }
        break;
    }
    Library.close();
    cout << "\n\n\n\tPress any key to go to Main menu...";
    system("pause>0");
}
void Book::SearchBookISBN() {
    ifstream Library;
    int count = 0;
    vector<string>row;
    string Attribute, Words;
    Library.open("booklist.csv");
    int SearchISBN, GotISBN;
    screenmainheader();
    cout << endl << std::setw(76) << right << " ------------------" << endl;
    cout << std::setw(76) << right << "|  SEARCH BOOKS  |" << endl;
    cout << std::setw(76) << right << " ------------------" << endl << endl << endl << endl;
    cout << "\tEnter the Book ISBN: ";
    cin >> SearchISBN;
    cout << "\n\n\n\t\t      " << std::setw(8) << right << "ISBN" << std::setw(25) << left << "\t    TITLE" << std::setw(17) << left << " CATEGORY" << std::setw(16) << left << "AUTHOR" << std::setw(8) << left << "PRICE" << std::setw(10) << right << "COPIES" << endl;
    cout << "\t\t     -------------------------------------------------------------------------------------------" << endl;

    while (Library.good()) {

        while (getline(Library, Attribute))
        {
            row.clear();
            istringstream s(Attribute);
            for (int i = 0; i < 6; i++) {
                getline(s, Words, ',');

                row.push_back(Words);
            }
            GotISBN = stoi(row[0]);
            if ((GotISBN == SearchISBN) && (row[5] != "0")) {

                // Print the found data
                count = 1;
                cout << "\t\t\t  " << row[0];
                cout << "\t   " << std::setw(23) << left << row[1];
                cout << std::setw(14) << left << row[2];
                cout << std::setw(18) << left << row[3];
                cout << std::setw(13) << left << row[4];
                cout << row[5];
                cout << endl;
                break;
            }
        }
        if (count == 0) {
            cout << "\n\n\n\tRecord not found\n";
        }
        break;
    }

    Library.close();
}
void Book::SearchBookTitle() {
    ifstream Library;
    int count = 0;
    vector<string>row;
    string Attribute, Words;
    Library.open("booklist.csv");
    string SearchTitle, GotTitle;
    screenmainheader();
    cout << endl << std::setw(76) << right << " ------------------" << endl;
    cout << std::setw(76) << right << "|  SEARCH BOOKS  |" << endl;
    cout << std::setw(76) << right << " ------------------" << endl << endl << endl << endl;
    cout << "\tEnter the Book Title: ";
    cin.ignore();
    getline(cin, SearchTitle);
    cout << "\n\n\n\t\t      " << std::setw(8) << right << "ISBN" << std::setw(25) << left << "\t    TITLE" << std::setw(17) << left << " CATEGORY" << std::setw(16) << left << "AUTHOR" << std::setw(8) << left << "PRICE" << std::setw(10) << right << "COPIES" << endl;
    cout << "\t\t     -------------------------------------------------------------------------------------------" << endl;
    while (Library.good()) {

        while (getline(Library, Attribute)) {
            row.clear();
            istringstream s(Attribute);
            for (int i = 0; i < 6; i++) {
                getline(s, Words, ',');

                row.push_back(Words);
            }
            GotTitle = row[1];
            if ((GotTitle == SearchTitle) && (row[5] != "0")) {

                // Print the found data
                count = 1;
                cout << "\t\t\t  " << row[0];
                cout << "\t   " << std::setw(23) << left << row[1];
                cout << std::setw(14) << left << row[2];
                cout << std::setw(18) << left << row[3];
                cout << std::setw(13) << left << row[4];
                cout << row[5];
                cout << endl;
                break;
            }
        }
        if (count == 0) {
            cout << "\n\n\n\tRecord not found\n";
        }
        break;
    }

    Library.close();
}
void Book::SearchBookAuthor() {
    ifstream Library;
    int count = 0;
    vector<string>row;
    string Attribute, Words;
    Library.open("booklist.csv");
    string SearchAuthor, GotAuthor;
    screenmainheader();
    cout << endl << std::setw(76) << right << " ------------------" << endl;
    cout << std::setw(76) << right << "|  SEARCH BOOKS  |" << endl;
    cout << std::setw(76) << right << " ------------------" << endl << endl << endl << endl;
    cout << "\tEnter the Book Author: ";
    cin.ignore();
    getline(cin, SearchAuthor);
    cout << "\n\n\n\t\t      " << std::setw(8) << right << "ISBN" << std::setw(25) << left << "\t    TITLE" << std::setw(17) << left << " CATEGORY" << std::setw(16) << left << "AUTHOR" << std::setw(8) << left << "PRICE" << std::setw(10) << right << "COPIES" << endl;
    cout << "\t\t     -------------------------------------------------------------------------------------------" << endl;
    while (Library.good()) {

        while (getline(Library, Attribute)) {
            row.clear();
            istringstream s(Attribute);
            for (int i = 0; i < 6; i++) {
                getline(s, Words, ',');

                row.push_back(Words);
            }
            GotAuthor = row[3];
            if ((GotAuthor == SearchAuthor) && (row[5] != "0")) {

                // Print the found data
                count = 1;
                cout << "\t\t\t  " << row[0];
                cout << "\t   " << std::setw(23) << left << row[1];
                cout << std::setw(14) << left << row[2];
                cout << std::setw(18) << left << row[3];
                cout << std::setw(13) << left << row[4];
                cout << row[5];
                cout << endl;
            }
        }
        if (count == 0) {
            cout << "\n\n\n\tRecord not found\n";
        }
        break;
    }

    Library.close();
}
void Book::SearchBookCategory() {
    ifstream Library;
    int count = 0;
    vector<string>row;
    string Attribute, Words;
    Library.open("booklist.csv");
    string SearchCategory, GotCategory;
    screenmainheader();
    cout << endl << std::setw(76) << right << " ------------------" << endl;
    cout << std::setw(76) << right << "|  SEARCH BOOKS  |" << endl;
    cout << std::setw(76) << right << " ------------------" << endl << endl << endl << endl;
    cout << "\tEnter Book Category: ";
    cin.ignore();
    getline(cin,SearchCategory);
    cout << "\n\n\n\t\t      " << std::setw(8) << right << "ISBN" << std::setw(25) << left << "\t    TITLE" << std::setw(17) << left << " CATEGORY" << std::setw(16) << left << "AUTHOR" << std::setw(8) << left << "PRICE" << std::setw(10) << right << "COPIES" << endl;
    cout << "\t\t     -------------------------------------------------------------------------------------------" << endl;
    while (Library.good()) {

        while (getline(Library, Attribute)) {
            row.clear();
            istringstream s(Attribute);
            for (int i = 0; i < 6; i++) {
                getline(s, Words, ',');

                row.push_back(Words);
            }
            GotCategory = row[2];
            if ((GotCategory == SearchCategory) && (row[5] != "0")) {

                // Print the found data
                count = 1;
                cout << "\t\t\t  " << row[0];
                cout << "\t   " << std::setw(23) << left << row[1];
                cout << std::setw(14) << left << row[2];
                cout << std::setw(18) << left << row[3];
                cout << std::setw(13) << left << row[4];
                cout << row[5];
                cout << endl;
            }
        }
        if (count == 0) {
            cout << "\n\n\n\tRecord not found\n";
        }
        break;
    }

    Library.close();
}

void Book::SearchBookMenu() {
    system("cls");
    int choice;
    screenmainheader();
    cout << endl << std::setw(76) << right << " ------------------" << endl;
    cout << std::setw(76) << right << "|  SEARCH BOOKS  |" << endl;
    cout << std::setw(76) << right << " ------------------" << endl << endl << endl << endl;
    cout << "\t1. Search By ISBN" << endl;
    cout << "\t2. Search By Title" << endl;
    cout << "\t3. Search By Category" << endl;
    cout << "\t4. Search By Author\n\n" << endl;
    cout << "\tEnter your Choice: ";
    cin >> choice;
    switch (choice) {
    case 1:
        system("cls");
        SearchBookISBN();
        break;
    case 2:
        system("cls");
        SearchBookTitle();
        break;
    case 3:
        system("cls");
        SearchBookCategory();
        break;
    case 4:
        system("cls");
        SearchBookAuthor();
        break;
    }
    cout << "\n\n\n\tPress any key to go to Main menu...";
    system("pause>0");
}

void Book::UpdateBook() {
    system("cls");
    cin.ignore();
    ifstream Library; ofstream NewLibrary;
    NewLibrary.open("newbooklist.csv", ios::app);
    int count = 0;
    vector<string>row;
    string Attribute, Words;
    Library.open("booklist.csv");
    int SearchISBN, GotISBN;
    screenmainheader();
    cout << endl << std::setw(76) << right << " ------------------" << endl;
    cout << std::setw(76) << right << "|  UPDATE BOOKS  |" << endl;
    cout << std::setw(76) << right << " ------------------" << endl << endl << endl << endl;
    cout << "\tEnter the Book ISBN: ";
    cin >> SearchISBN;

    while (Library.good()) {

        while (getline(Library, Attribute)) {
            row.clear();
            istringstream s(Attribute);
            for (int i = 0; i < 6; i++) {
                getline(s, Words, ',');

                row.push_back(Words);
            }
            GotISBN = stoi(row[0]);
            if (GotISBN == SearchISBN) {
                int choice;
                cout << "\n\tWhat attribute of Book do you want to edit?" << endl;
                cout << "\t 1. Category" << endl;
                cout << "\t 2. Price" << endl;
                cout << "\t 3. Copies" << endl;
                cout << "\n\n\tEnter choice: ";
                cin >> choice;
                switch (choice) {
                case 1:
                    system("cls");
                    screenmainheader();
                    cout << endl << std::setw(76) << right << " ------------------" << endl;
                    cout << std::setw(76) << right << "|  UPDATE BOOKS  |" << endl;
                    cout << std::setw(76) << right << " ------------------" << endl << endl << endl << endl;
                    cout << "\tEnter New Category: ";
                    cin >> row[2];
                    NewLibrary << row[0] << "," << row[1] << "," << row[2] << "," << row[3] << "," << row[4] << "," << row[5] << endl;
                    cout << "\n\n\tBook Updated Successfully";
                    break;
                case 2:
                    system("cls");
                    screenmainheader();
                    cout << endl << std::setw(76) << right << " ------------------" << endl;
                    cout << std::setw(76) << right << "|  UPDATE BOOKS  |" << endl;
                    cout << std::setw(76) << right << " ------------------" << endl << endl << endl << endl;
                    cout << "\tEnter New Price: ";
                    cin >> row[4];
                    NewLibrary << row[0] << "," << row[1] << "," << row[2] << "," << row[3] << "," << row[4] << "," << row[5] << endl;
                    cout << "\n\n\tBook Updated Successfully";
                    break;
                case 3:
                    system("cls");
                    screenmainheader();
                    cout << endl << std::setw(76) << right << " ------------------" << endl;
                    cout << std::setw(76) << right << "|  UPDATE BOOKS  |" << endl;
                    cout << std::setw(76) << right << " ------------------" << endl << endl << endl << endl;
                    cout << "\tEnter New Copies: ";
                    cin >> row[5];
                    NewLibrary << row[0] << "," << row[1] << "," << row[2] << "," << row[3] << "," << row[4] << "," << row[5] << endl;
                    cout << "\n\n\tBook Updated Successfully";
                    break;
                }
                // Print the found data
                count = 1;
                break;
            }
            else {
                NewLibrary << row[0] << "," << row[1] << "," << row[2] << "," << row[3] << "," << row[4] << "," << row[5] << endl;
            }
        }
        if (count == 0) {
            cout << "\n\n\n\tISBN not found\n";

        }
        NewLibrary.close();
        Library.close();
        remove("booklist.csv");
        rename("newbooklist.csv", "booklist.csv");
        break;

    }
    cout << "\n\n\tPress any key to go to Main menu...";
    system("pause>0");
}
void Book::DeleteBook() {
    system("cls");
    screenmainheader();
    cout << endl << std::setw(76) << right << " ------------------" << endl;
    cout << std::setw(76) << right << "|  DELETE BOOKS  |" << endl;
    cout << std::setw(76) << right << " ------------------" << endl << endl << endl << endl;
    cin.ignore();

    ifstream Library; ofstream NewLibrary;
    NewLibrary.open("newbooklist.csv", ios::app);
    int count = 0;
    vector<string>row;
    string Attribute, Words;
    Library.open("booklist.csv");
    int SearchISBN, GotISBN;
    cout << "\tEnter ISBN of Book you want to delete: ";
    cin >> SearchISBN;

    while (Library.good()) {

        while (getline(Library, Attribute)) {
            row.clear();
            istringstream s(Attribute);
            for (int i = 0; i < 6; i++) {
                getline(s, Words, ',');

                row.push_back(Words);
            }
            GotISBN = stoi(row[0]);
            if (GotISBN == SearchISBN) {
                row[5] = "0";
                NewLibrary << row[0] << "," << row[1] << "," << row[2] << "," << row[3] << "," << row[4] << "," << row[5] << endl;
                count = 1;
                cout << "\n\tBook Deleted Successfully" << endl;
                break;
            }
            else {
                NewLibrary << row[0] << "," << row[1] << "," << row[2] << "," << row[3] << "," << row[4] << "," << row[5] << endl;
            }
        }
        
        if (count == 0) {
            cout << "\n\tISBN not found\n";
        }

        NewLibrary.close();
        Library.close();
        remove("booklist.csv");
        rename("newbooklist.csv", "booklist.csv");
        break;
    }
    cout << "\n\n\tPress any key to go to Main menu...";
    system("pause>0");
}
void Book::LowStock() {
    system("cls");
    screenmainheader();
    cout << endl << std::setw(77) << right << "---------------------" << endl;
    cout << std::setw(77) << right << "|  LOW STOCK BOOKS  |" << endl;
    cout << std::setw(77) << right << "---------------------" << endl << endl << endl << endl;
    ifstream Library;
    int count = 0;
    vector<string>row;
    string Attribute, Words;
    Library.open("booklist.csv");
    cout << "\n\n\n\t\t      " << std::setw(8) << right << "ISBN" << std::setw(25) << left << "\t    TITLE" << std::setw(17) << left << " CATEGORY" << std::setw(16) << left << "AUTHOR" << std::setw(8) << left << "PRICE" << std::setw(10) << right << "COPIES" << endl;
    cout << "\t\t     -------------------------------------------------------------------------------------------" << endl;
    while (Library.good()) {
        while (getline(Library, Attribute)) {
            row.clear();
            istringstream s(Attribute);
            for (int i = 0; i < 6; i++) {
                getline(s, Words, ',');

                row.push_back(Words);
            }
            int x = stoi(row[5]);
            if (x < 10 && x>0) {

                // Print the found data
                count = 1;
                cout << "\t\t\t  " << row[0];
                cout << "\t   " << std::setw(23) << left << row[1];
                cout << std::setw(14) << left << row[2];
                cout << std::setw(18) << left << row[3];
                cout << std::setw(13) << left << row[4];
                cout << row[5];
                cout << endl;
            }
        }
        if (count == 0) {
            cout << "\n\n\tNo Low Stock Books\n";
        }
        break;
    }
    Library.close();
    cout << "\n\n\n\tPress any key to go to Main menu...";
    system("pause>0");
}

void Customer::Order() {
    system("cls");
    //Call Search and Then Edit this Update function to Order by creating new file called Order//
    ifstream Library; ofstream NewLibrary; ofstream Order;
    Order.open("orderlist.csv",ios::app);
    NewLibrary.open("newbooklist.csv", ios::app);
    int count = 0;
    vector<string>row;
    string Attribute, Words;
    Library.open("booklist.csv");
    int SearchISBN, GotISBN, Quantity, CurrentUantity;
    screenmainheader();
    cout << endl << std::setw(75) << right << "-----------------" << endl;
    cout << std::setw(75) << right << "|  ORDER BOOKS  |" << endl;
    cout << std::setw(75) << right << "-----------------" << endl << endl << endl << endl;
    cout << "\tEnter the Book ISBN: ";
    cin >> SearchISBN;
    cout << "\tEnter Order Quantity: ";
    cin >> Quantity;
    cout << endl << endl;
    while (Library.good()) {

        while (getline(Library, Attribute)) {
            row.clear();
            
            istringstream s(Attribute);
            for (int i = 0; i < 6; i++) {
                getline(s, Words, ',');

                row.push_back(Words);
            }
            GotISBN = stoi(row[0]);
            CurrentUantity = stoi(row[5]);
            if (GotISBN == SearchISBN) {
                if (CurrentUantity - Quantity >= 0) {
                    row[5] = to_string(CurrentUantity - Quantity);
                    NewLibrary << row[0] << "," << row[1] << "," << row[2] << "," << row[3] << "," << row[4] << "," << row[5] << endl;
                    count = 1;
                   
                }
                else {
                    count = 2;
                    NewLibrary << row[0] << "," << row[1] << "," << row[2] << "," << row[3] << "," << row[4] << "," << row[5] << endl;
                    
                }
            }
            else {
                NewLibrary << row[0] << "," << row[1] << "," << row[2] << "," << row[3] << "," << row[4] << "," << row[5] << endl;
            }
        }
        
        break;
    }

        if (count == 2) { cout << "\n\tInsufficient Quantity" << endl; }
        else if (count == 1) {
            cout << "\n\tBook Ordered Successfully" << endl;
        }
        else {
            cout << "\n\tISBN Not Found" << endl;
        }

        Order << row[1] << "," << Quantity << "," << row[4] << endl;
        NewLibrary.close();
        Library.close();
        Order.close();
        remove("booklist.csv");
        rename("newbooklist.csv", "booklist.csv");
        
    
    OrderAgain();
}


void Customer::Billing() {
    system("cls");
    vector<string>row;
    int Total = 0;
    screenmainheader();
    cout << endl << std::setw(73) << right << "-------------" << endl;
    cout << std::setw(73) << right << "|  BILLING  |" << endl;
    cout << std::setw(73) << right << "-------------" << endl << endl << endl << endl;
    string Attribute, Words;
    ifstream Order;
    Order.open("orderlist.csv");
    while (Order.good()) {
        while (getline(Order, Attribute)) {
            row.clear();
            istringstream s(Attribute);
            for (int i = 0; i < 3; i++) {
                getline(s, Words, ',');
                row.push_back(Words);
            }
            int CurrentP = stoi(row[2]);
            int CurrentU = stoi(row[1]);
            // Print the found data
            cout << "\tBook Title: " << row[0] << "\n";
            cout << "\tQuantity: " << row[1] << "\n";
            cout << "\tPrice: " << row[2] << "\n";
            Total += CurrentP * CurrentU;
            cout << endl;

        }
    }
    Order.close();
    cout << "\tTotal:" << Total;
    remove("orderlist.csv");
    cout << "\n\n\n\tPress any key to go to Main menu...";
    system("pause>0");
}
void Customer::OrderAgain() {
    string Answer; cout << "\n\n\tPress Y to Order Again and N to continue to Checkout: "; cin >> Answer; if (Answer == "Y") { Order(); }
    else {};
}
void screenchangeFont(float x) {
    static CONSOLE_FONT_INFOEX fontex;
    fontex.cbSize = sizeof(CONSOLE_FONT_INFOEX);
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    GetCurrentConsoleFontEx(hOut, 0, &fontex);
    fontex.FontWeight = 50;
    fontex.dwFontSize.X = x;
    fontex.dwFontSize.Y = x;
    SetCurrentConsoleFontEx(hOut, NULL, &fontex);
}
void screenloginheader(){
    cout <<endl<< std::setw(88) << right << "=========================================" << endl;
    cout << std::setw(88) << right << "WELCOME TO BOOKSHOP INVENTORY SYSTEM!  " << endl;
    cout << std::setw(88) << right << "=========================================" << endl << endl << endl << endl;
}
void screenmainheader() {
    cout <<endl<< std::setw(81) << right << "=============================" << endl;
    cout << std::setw(81) << right << "BOOKSHOP INVENTORY SYSTEM  " << endl;
    cout << std::setw(81) << right << "=============================" << endl << endl << endl;
}
void screenmainmenu() {
    cout << endl << std::setw(74) << right << "---------------" << endl;
    cout << std::setw(74) << right << "|  MAIN MENU  |" << endl;
    cout << std::setw(74) << right << "---------------" << endl << endl << endl << endl;
}