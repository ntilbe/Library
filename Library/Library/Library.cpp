#include <iostream>
#include "Book.h"
#include <string>
#include "inventory.h"


Inventory inventory; //class and object


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
        std::cout << "6. Exit the library\n"; 


        std::cin >> choice;
        std::cin.ignore(); // This is for the getline

        switch (choice)
        {
        case 1: 
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
            break;
        }
        case 2:
        {
            std::cout << "\nID\tTitle\tAuthor" << std::endl;
            for (int i = 0; i < inventory.Books.size(); i++)
            {
                std::cout << inventory.Books[i].Id << "\t" << inventory.Books[i].Title << "\t" << inventory.Books[i].Author << std::endl;
            }
            std::cout << std::endl;
            break;
        }
        case 3:
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
                    break;
                }
                inventory.Books[index].CheckedOut = true;
                std::cout << "\nYou have checked out a new book.\n";
            }
            else
            {
                std::cout << "Book not Found" << std::endl;
            }
            break;
        }
        case 4:
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
                    break;
                }
                inventory.Books[index].CheckedOut = false;
                std::cout << "\nYou have checked in a book.\n";
            }
            else
            {
                std::cout << "Book not Found" << std::endl;
            }
            break;
        }
        case 5:
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

            break;
        }
        case 6:
        {
            std::cout << "Thank you. Goodbye.\n";
            break;
        }

        Default:
            std::cout << "Invalid Selection. Please try again." << std::endl;
        }
    } while (choice != 6);

    return 0;
}