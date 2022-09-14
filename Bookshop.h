#ifndef BOOKSHOP_H
#define BOOKSHOP_H
#include <iostream>
#include<iomanip>
#include<Windows.h>
using namespace std;
class User {
    string Username;
    string Password;
public:
    virtual void Login();
    string getUsername();
    string getPassword();

    User();
};
class Book {
    string Title;
    string Category;
    string Author;
    string ISBN; //4 Digit BookNumber//
    int Copies;
    int Price;
public:
    Book();
    void DisplayBook();
    void SearchBookISBN();
    void SearchBookTitle();
    void SearchBookCategory();
    void SearchBookAuthor();
    void SearchBookMenu();
    void LowStock();
    void AddBook();
    void UpdateBook();
    void DeleteBook();
};
class Admin :public User {
    Book BA;
public:
    
    void Login();
    void MainMenu();

};
class Customer :public User {
    Book BU;
public:
    void Login();
    void MainMenu();
    void Order();
    void OrderAgain();
    void Billing();
};
void screenchangeFont(float);
void screenloginheader();
void screenmainheader();
void screenmainmenu();
#endif