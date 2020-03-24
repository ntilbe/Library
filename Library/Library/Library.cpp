#include <iostream>
#include "Book.h"
#include <string>
#include "inventory.h"
#include "User.h"

Inventory inventory; //class and object
std::vector<User> _users;
User _loggedInUser;

void CreateAccount()
{
    User newUser;

    //std::cout << "First Name: " << std::endl;
    //std::string firstName;
    //getline(std::cin, firstName);

    //std::cout << "Last Name: " << std::endl;
    //std::string lastName;
    //getline(std::cin, lastName);

    std::cout << "Username: " << std::endl;
    getline(std::cin, newUser.Username);

    std::cout << "Choose a role: " << std::endl;
    std::cout << "1. Admin " << std::endl;
    std::cout << "2. Employee " << std::endl;
    std::cout << "3. Member " << std::endl;

    int roleOption;
    std::cin >> roleOption;
    std::cin.ignore();

    if (roleOption == 1)
        newUser.Role = Role::Admin;
    else if (roleOption == 2)
        newUser.Role = Role::Employee;
    else
        newUser.Role = Role::Member;

    _users.push_back(newUser);
}

void Login()
{
    std::cout << "Choose an option: " << std::endl;
    std::cout << "1. Log In " << std::endl;
    std::cout << "2. Create an account " << std::endl;

    int option;
    std::cin >> option;
    std::cin.ignore();

    if (option == 2)
    {
        CreateAccount();
    }


    std::cout << "Enter username: ";
    std::string username;
    getline( std::cin, username);


    User user;
    user.Username = username;

    std::vector<User>::iterator it = find(_users.begin(), _users.end(), user);

    if (it != _users.end())
    {
        _loggedInUser = _users[it - _users.begin()];
    }

}

void DisplayMainMenu()
{
    std::cout << " [  M A I N    M E N U  ] \n";
    std::cout << "\n";
    std::cout << "\n";
    std::cout << "Choose an option: " << std::endl;

    if (_loggedInUser.Role == Role::Employee || _loggedInUser.Role == Role::Admin)
    {
        std::cout << "1. Add a book to the library\n";
        std::cout << "2. Display number of books in the library\n";
        std::cout << "3. Remove a book from the inventory";
        std::cout << "4. List all checked out books\n";
    }

    std::cout << "5. List all books\n";
    std::cout << "6. Check out a book\n";
    std::cout << "7. Check in a book\n";

    std::cout << "0. Exit the library\n";
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
        std::cout << "Book not found" << std::endl;
    }
    else if(result == CheckInOrOutResult::Success)
    {
        std::cout << "Book checked " + inOrOut + "!" << std::endl;
    }
    else if (result == CheckInOrOutResult::AlreadyCheckedIn || result == CheckInOrOutResult::AlreadyCheckedOut)
    {
        std::cout << "Book already checked " + inOrOut + "!" << std::endl;
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
    Login();
    int choice;
    do
    {
        DisplayMainMenu();

        std::cin >> choice; // User enters 1-6; otherwise comes back invalid input
        std::cin.ignore(); // This is for the getline, need it to grab the entire line

        switch (choice)
        {
        case 0:
            std::cout << "Thank you. Goodbye.\n";
            break;
        case 1: 
            AddNewBook();
            break;
        case 2:
            ListAllBooks();
            break;
        case 3:
            CheckInOrOutBook(true);
            break;
        case 4:
            CheckInOrOutBook(false);
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

        default:
            std::cout << std::endl;
            std::cout << "Invalid Selection. Please try again." << std::endl;
        }
    } while (choice != 0); //this will loop until you select #6 to exit the library

    return 0;
}