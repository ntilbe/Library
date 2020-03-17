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
        std::cout << "1. Add a book to the library\n";
        std::cout << "2. Check out a new book\n";
        std::cout << "3. Check in a book\n";
        std::cout << "4. Display list of books from inventory : \n";
        std::cout << "5. Display number of books in the library.\n";
        std::cout << "6. Exit the library\n"; 



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

            int bookId = inventory.Books.size() + 1;

            Book book(bookId, bookTitle, bookAuthor); //constructor
            inventory.AddBook(book); //sends the whole book to the inventory

            std::cout << "\nYou have added a new book to the library.\n";
            break;
        }
        case 2:

                std::cout << "\nYou have checked out a new book.\n";
            
            break;
        case 3:
            

            std::cout << "\nYou have checked in a book.\n";
            break;
        case 4:
            void print_vector(std::vector<int> data);
            {
                for(int i = 0; inventory.Books.size(); i++)
                {
                    std::cout << inventory.Books[i].Id << "" << inventory.Books[i].Title << "" << inventory.Books[i].Author << std::endl;
                }
            }
       
            break;
        case 5:
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
        case 6:
            std::cout << "Thank you. Goodbye.\n";
            break;
        }
    } while (choice != 4);


}