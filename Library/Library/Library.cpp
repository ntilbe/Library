#include <iostream>
#include "Book.h"
#include <string>
#include "inventory.h"

Inventory inventory; //class and object

void DisplayMainMenu()
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
    std::cout << "7. List all checked out books\n";
    std::cout << "8. Exit the library\n";
}

void AddNewBook() // Case 1
{
    std::cout << "Enter Book Title:\n";
    std::string bookTitle;
    std::getline(std::cin, bookTitle);
    
    std::cout << "Enter Book Author:\n";
    std::string bookAuthor;
    std::getline(std::cin, bookAuthor);

    Book newBook(bookTitle, bookAuthor); //constructor

    inventory.AddBook(newBook); //sends the whole book to the inventory

    std::cout << "\nYou have added a new book to the library.\n";
}


void ListAllBooks() // Case 2
{
    inventory.DisplayAllBooks();
}


void CheckInOrOutBook(bool checkOut) // Case 3 & 4
{
    std::string inOrOut;
    if (checkOut)
    {
        inOrOut = "out";
    }
    else
    {
        inOrOut = "in";
    }

    std::cout << "Enter a Book Title to Check " + inOrOut + ": ";
    std::string bookTitle;
    std::getline(std::cin, bookTitle);

  CheckInOrOutResult result = inventory.CheckInOrOutBook(bookTitle, checkOut);

    if (result == CheckInOrOutResult::BookNotFound)
    {
        std::cout << "Book not found";
    }
    else if(result == CheckInOrOutResult::Success)
    {
        std::cout << "Book checked " + inOrOut + "!" << std::endl;
    }
    else
    {
        std::cout << "Book failed checking " + inOrOut + "!" << std::endl;
    }
  
}


void DisplayNumBooks() // Case 5
{
    int numBooks = inventory.NumberOfBooks(); 
    if(numBooks > 0)
    {
        std::cout << std::endl;
        std::cout << "\nThere are " << numBooks << " books in our library.\n";
    }
    else
    {
        std::cout << std::endl;
        std::cout << "\nThere are no books to display.\n";
    }
}

void RemoveBook() // Case 6
{
    std::cout << "Enter Book Title:\n";
    std::string bookTitle;
    std::getline(std::cin, bookTitle);

    std::cout << std::endl;
    std::cout << "You have removed a book from the library." << std::endl;
}

void DisplayCheckedOutBooks()
{
    inventory.DisplayCheckedOutBooks();
}

int main()
{
    int choice;
    do
    {
        DisplayMainMenu();

        std::cin >> choice; // User enters 1-6; otherwise comes back invalid input
        std::cin.ignore(); // This is for the getline, need it to grab the entire line

        switch (choice)
        {
        case 1: 
            AddNewBook();
            break;
        case 2:
            ListAllBooks();
            break;
        case 3:
            CheckInOrOutBook(false);
            break;
        case 4:
            CheckInOrOutBook(true);
            break;
        case 5:
            DisplayNumBooks();
            break;
        case 6:
            RemoveBook();
            break;
        case 7:
            void DisplayCheckedOutBooks();
            break;
        case 8:
            std::cout << "Thank you. Goodbye.\n";
            break;

        default:
            std::cout << std::endl;
            std::cout << "Invalid Selection. Please try again." << std::endl;
        }
    } while (choice != 8); //this will loop until you select #6 to exit the library

    return 0;
}