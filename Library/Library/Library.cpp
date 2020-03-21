#include <iostream>
#include "Book.h"
#include <string>
#include "inventory.h"

Inventory inventory; //class and object

void AddBook() // Case 1
{
    std::cout << "Enter Book Title:\n";
    std::string bookTitle;
    std::getline(std::cin, bookTitle);

    std::cout << "Enter Book Author:\n";
    std::string bookAuthor;
    std::getline(std::cin, bookAuthor);

    int bookId = inventory.Books.size() + 1;

    Book newBook(bookId, bookTitle, bookAuthor); //constructor

    inventory.AddBook(newBook); //sends the whole book to the inventory

    std::cout << "\nYou have added a new book to the library.\n";
}


void DisplayAllBooks() // Case 2
{
    std::cout << "\nID\tTitle\tAuthor" << std::endl;
     for (int i = 0; i < inventory.Books.size(); i++) // Goes from 0 to the size of the vector (ex. if there are 10 elements in the vector, it will be 10
     {
             std::cout << inventory.Books[i].Id << "\t" << inventory.Books[i].Title << "\t" << inventory.Books[i].Author << std::endl; // Displays all books in inventory
     }
            std::cout << std::endl;
}

void CheckOutBook() // Case 3
{
    std::cout << "Enter a Book Title to Check Out: ";
    std::string bookTitle;
    std::getline(std::cin, bookTitle);

    int index = (inventory.FindBookByTitle(bookTitle));

    if (index >= 0)
    {
        if (inventory.Books[index].CheckedOut)
        {
            std::cout << "Book already Checked Out." << std::endl;
            return;
        }
        inventory.Books[index].CheckedOut = true;
        std::cout << "\nYou have checked out a new book.\n";
    }
    else
    {
        std::cout << "Book not Found" << std::endl;
    }
}

void CheckInBook() //Case 4
{
    std::cout << "Enter a Book Title to Check In: ";
    std::string bookTitle;
    std::getline(std::cin, bookTitle);

    int index = inventory.FindBookByTitle(bookTitle);

    if (index >= 0)
    {
        Book foundBook = inventory.Books[index];

        if (!foundBook.CheckedOut)
        {
            std::cout << "Book already checked in." << std::endl;
            return;
        }
        inventory.Books[index].CheckedOut = false;
        std::cout << "\nYou have checked in a book.\n";
    }
    else
    {
        std::cout << "Book not Found" << std::endl;
    }
}

void DisplayNumBooks() // Case 5
{
    int numBooks = inventory.Books.size();
    if (numBooks > 0)
    {
        std::cout << "\nThere are " << numBooks << " books in our library.\n";
    }
    else
    {
        std::cout << "\nThere are no books to display.\n";
    }
}

void RemoveBook() // Case 6
{


}

int main()
{
    int choice;

    do
    {
        std::cout << " [  M A I N    M E N U  ] \n";
        std::cout << "\n";
        std::cout << "\n";
        std::cout << "1. Add a book to the library\n";
        std::cout << "2. Display list of books from inventory\n";
        std::cout << "3. Check out a book\n";
        std::cout << "4. Check in a book\n";
        std::cout << "5. Display number of books in the library\n";
        std::cout << "6. Remove a book from the inventory";
        std::cout << "7. Exit the library\n"; 


        std::cin >> choice; // User enters 1-6; otherwise comes back invalid
        std::cin.ignore(); // This is for the getline, need it to grab the entire line

        switch (choice)
        {
        case 1: 
        {
            AddBook();
            break;
        }
        case 2:
        {
            void DisplayAllBooks();
            break;
        }
        case 3:
        {
            void CheckOutBook();
            break;
        }
        case 4:
        {
            void CheckInBook();
            break;
        }
        case 5:
        {
            void DisplayNumBooks();
            break;
        }
        case 6:
        {
            void RemoveBook();
            break;
        }
        case 7:
        {
            std::cout << "Thank you. Goodbye.\n";
            break;
        }

        Default:
            std::cout << "Invalid Selection. Please try again." << std::endl;
        }
    } while (choice != 7); //this will loop until you select #6 to exit the library

    return 0;
}