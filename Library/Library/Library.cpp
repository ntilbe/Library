#include <iostream>
#include "Book.h"
#include <string>
#include "inventory.h"
#include "User.h"
#include <fstream>

Inventory inventory; //class and object
std::vector<User> _users;
User _loggedInUser;
int choice;

Role GetRoleFromIntVal(int roleVal)
{
	Role outRole;
	if (roleVal == 0)
	{
		outRole = Role::Admin;
	}
	else if (roleVal == 1)
	{
		outRole = Role::Employee;
	}
	else
	{
		outRole = Role::Member;
	}


	return outRole;
}

void LoadUsers()
{
	std::ifstream inFile("users.txt");

	std::string lineData[2];
	// lineData[0] = username
	// lineData[1] = role int val

	std::string userLine;
	while (getline(inFile, userLine))
	{
		size_t index = userLine.find(' | ');
		lineData[0] = userLine.substr(0, index);
		lineData[1] = userLine.substr(index + 1);

		User loadedUser;
		loadedUser.Username = lineData[0];
		loadedUser.Role = GetRoleFromIntVal(stoi(lineData[1]));

		_users.push_back(loadedUser);
	}
}

int GetIntValFromRole(Role role)
{
	int roleVal = -1;
	if (role == Role::Admin)
	{
		roleVal = 0;
	}
	else if (role == Role::Employee)
	{
		roleVal = 1;
	}
	else if (role == Role::Member)
	{
		roleVal = 2;
	}

	return roleVal;
}

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

	std::ofstream oFile("users.txt", std::ios_base::app);
	oFile << newUser.Username << "|" << GetIntValFromRole(newUser.Role) << std::endl;
	oFile.close();

}

void Login()
{
	while (true) // while loop 1
	{
		std::cout << "Choose an option: " << std::endl;
		std::cout << "1. Log In " << std::endl;
		std::cout << "2. Create an account " << std::endl;
		std::cout << "\n";

		int option;
		std::cin >> option;
		std::cout << "\n";
		std::cin.ignore();

		if (option == 2)
		{
			CreateAccount();
		}

		while (true) // while loop 2
		{
			std::cout << "1. Enter username: \n";
			std::cout << "2. Exit\n";
			std::cout << "\n";
			std::cout << "\n";
			std::string username;
			getline(std::cin, username);
			std::cout << "\n";

			if (username == "Exit" || username == "exit")
			{
				break; // breaks out of while loop 2
			}

			User user;
			user.Username = username;

			std::vector<User>::iterator it = find(_users.begin(), _users.end(), user);

			if (it != _users.end()) // looking for the username
			{
				_loggedInUser = _users[it - _users.begin()];
				return; // exits void Login function
			}
		}
	}
}

void DisplayMainMenu()
{
	std::cout << " [  M A I N    M E N U  ] \n";
	std::cout << "\n";
	std::cout << "\n";
	std::cout << "Choose an option: " << std::endl;

	std::cout << "1. List all books\n"; // these options will show up for every role
	std::cout << "2. Check out a book\n";
	std::cout << "3. Check in a book\n";

	if (_loggedInUser.Role == Role::Employee || _loggedInUser.Role == Role::Admin)
	{
		std::cout << "4. Add a book to the library\n"; // the following options will only show if you login as an employee or admin
		std::cout << "5. Display number of books in the library\n";
		std::cout << "6. Remove a book from the inventory";
		std::cout << "7. List all checked out books\n";
	}
	std::cout << "8. Log Out\n";
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
	else if (result == CheckInOrOutResult::Success)
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
	if (numBooks > 0)
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
	inventory.LoadBooks();
	LoadUsers();
	while (true)
	{
		Login();

		bool isLoggedIn = true;
		while (isLoggedIn)
		{
			DisplayMainMenu();

			std::cin >> choice; // User enters 1-6; otherwise comes back invalid input
			std::cin.ignore(); // This is for the getline, need it to grab the entire line

			switch (choice) // keeps the code clean and organized; could use if statement as well (not as clean though)
			{
			case 0:
				std::cout << "Thank you. Goodbye.\n"; // exits out of menu
				return 0; // breaks out of main
			case 1:
				ListAllBooks(); // lists all books in the library currently
				break; // exits the switch statement
			case 2:
				CheckInOrOutBook(true); // case to check out a book
				break;
			case 3:
				CheckInOrOutBook(false); // case to check in a book
				break;
			case 4:
				AddNewBook(); // adds a book to the library's inventory and is stored there
				break;
			case 5:
				DisplayNumBooks(); // displays number of books in library's inventory (option only for admin or employee)
				break;
			case 6:
				RemoveBook(); // removes a book from the inventory permeanently (option only for admin or employee)
				break;
			case 7:
				DisplayCheckedOutBooks(); // lists all books that are currently checked out (option only for admin or employee)
				break;
			case 8:
				isLoggedIn = false;
				break;
			default: // equivalent to "else" statement
				std::cout << std::endl;
				std::cout << "Invalid Selection. Please try again." << std::endl; // user entered something other than number 0-7 and needs to re-enter a valid number/option
			}
		}
	}
	return 0;
}