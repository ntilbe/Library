#include <iostream>
#include "Book.h"
#include <string>
#include "inventory.h"

int main()
{
    int choice;
    Inventory inventory; //class and object

    do
    {
        std::cout << "1. Create New Book\n2.Check Out a New Book\n3.Check In a Book\n4.List of Books from Inventory:\n5.Exit" << std::endl;
        std::cin >> choice;
        std::cin.ignore();

        switch (choice)
        {
        case 1:
        {
            std::cout << "Book Title:\n";
            std::string bookTitle;
            std::getline(std::cin, bookTitle);

            std::cout << "Book Author:\n";
            std::string bookAuthor;
            std::getline(std::cin, bookAuthor);

            Book book(bookTitle, bookAuthor); //constructor
            inventory.AddBook(book); //sends the whole book to the inventory
            break;
        }
        case 2:
            
            break;
        case 3:
            
            break;
        case 4:

            break;
        case 5:
            std::cout << "Thank you. Goodbye.\n";
            break;
        }
    } while (choice != 4);


}