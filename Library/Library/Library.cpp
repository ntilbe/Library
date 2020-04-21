#include <iostream>
#include "Book.h"
#include <string>
#include "inventory.h"
#include "User.h"
#include <fstream>

Inventory inventory; //class and object
std::vector<User> _users; // vector to store user info (from user.h file)
User _loggedInUser; // stores the info regarding who's logged  in; uses _ to show its a global variable listed at top of program to use 
int choice; // for switch statement

Role GetRoleFromIntVal(int roleVal) // roleVal = a number given to roles (Ex. 0 = Admin), input a number and depending on role will be given different abilities
{
	Role outRole;
	if (roleVal == 0) // inputs number, outputs role type
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
	std::ifstream inFile("users.txt"); // opening txt file

	std::string lineData[2]; // 2 lines of data ( lineData[0] and lineData[1] )
	// lineData[0] = username
	// lineData[1] = role int val (Ex: 0 = Admin)

	std::string userLine; // used to get entire line of user info
	while (getline(inFile, userLine)) // gets and loads user info 
	{
		size_t index = userLine.find('|');
		lineData[0] = userLine.substr(0, index); // index 0 to | will be saved in lineData[0]
		lineData[1] = userLine.substr(index + 1); // | to end of line will be saved in lineData[1]


		User loadedUser; //  lineData [0] and [1] saved to loadedUser
		loadedUser.Username = lineData[0]; // lineData[0] set to Username
		loadedUser.Role = GetRoleFromIntVal(stoi(lineData[1])); // lineData[1] set to role; convert int to role

		_users.push_back(loadedUser); // push_back pushes loadedUser into the last place in vector
	}
}

int GetIntValFromRole(Role role)
{
	int roleVal = -1; // will come back -1 if roleVal doesn't equal 0, 1, or 2.
	if (role == Role::Admin) // input role type, output int
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
	User newUser; // newUser = username, role

	//std::cout << "First Name: " << std::endl;
	//std::string firstName;
	//getline(std::cin, firstName);

	//std::cout << "Last Name: " << std::endl;
	//std::string lastName;
	//getline(std::cin, lastName);

	std::cout << "Username: " << std::endl;
	getline(std::cin, newUser.Username); //saves username entered as newUser.Username

	//TODO: search vector for username, if found send error saying "username already exists"

	std::cout << "Choose a role: " << std::endl; // choose number 1, 2, or 3 to be assigned role to specific username
	std::cout << "1. Admin " << std::endl;
	std::cout << "2. Employee " << std::endl;
	std::cout << "3. Member " << std::endl;
	// TODO: check for valid input, otherwise bump back to menu and enter appropriate value

	int roleOption; 
	std::cin >> roleOption; // number 1, 2, or 3 stored 
	std::cin.ignore(); // connected to getline function; grabs the entire line
	newUser.Role = GetRoleFromIntVal(roleOption - 1); // stores newUser.Role as selected role 

	_users.push_back(newUser); // stores newUser in _users vector

	std::ofstream oFile("users.txt", std::ios_base::app); // opening users.txt file, append newUser data to end of file
	oFile << newUser.Username << "|" << GetIntValFromRole(newUser.Role) << std::endl; // this is what is printed in txt file; GetIntValFromRole converts role to int
	oFile.close(); // closes file

}

void Login()
{
	while (true) // while loop 1
	{
		std::cout << "Choose an option: " << std::endl;
		std::cout << "1. Log In " << std::endl;
		std::cout << "2. Create an account " << std::endl;
		std::cout << "\n";
		//TODO: check for valid input, otherwise bump back to menu and enter appropriate value

		int option;
		std::cin >> option; // option = 1 or 2
		std::cout << "\n"; // empty line
		std::cin.ignore(); // used with getline

		if (option == 2) // if 2 is selected, make an account
		{
			CreateAccount();
		}

		while (true) // while loop 2; if 1 is chosen, skips if and goes directly to "Enter username:"
		{
			std::cout << "Enter username (or \"Exit\"): ";
			std::string username; // user input saved as username
			getline(std::cin, username); // reads/saves entire line
			std::cout << "\n";

			if (username == "Exit" || username == "exit") 
			{
				break; // breaks out of while loop 2
			}

			User user; // class and object OR data type and variable
			user.Username = username; // data type string

			std::vector<User>::iterator it = find(_users.begin(), _users.end(), user); // searching for username; iterator represents a location within a vector

			if (it != _users.end()) // checking to see if it found the username
			{
				_loggedInUser = _users[it - _users.begin()]; // if username is found, sets it equal to _loggedInUser
				return; // exits void Login function
			}
		}
	}
}

void DisplayMainMenu() // menu displayed after logging in
{
	std::cout << " [  M A I N    M E N U  ] \n";
	std::cout << "\n";
	std::cout << "\n";
	std::cout << "Choose an option: " << std::endl;

	std::cout << "1. List all books\n"; // these options will show up for every role
	std::cout << "2. Check out a book\n";
	std::cout << "3. Check in a book\n";

	if (_loggedInUser.Role == Role::Employee || _loggedInUser.Role == Role::Admin) //_loggedInUser only being used because of checking role
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
	std::getline(std::cin, bookTitle); // user input saved as bookTitle

	std::cout << "Enter Book Author:\n";
	std::string bookAuthor;
	std::getline(std::cin, bookAuthor); // user input saved as bookAuthor

	Book newBook(bookTitle, bookAuthor); //constructor; newBook stores bookTitle and bookAuthor and CheckedOut = False (refer to book.cpp)

	inventory.AddBook(newBook); //sends the whole book to the inventory

	std::cout << "\nYou have added a new book to the library.\n";
}

void ListAllBooks() // Case 2
{
	inventory.DisplayAllBooks(); // refer to Inventory.cpp DisplayAllBooks function
}

void CheckInOrOutBook(bool checkOut) // Case 3 & 4
{
	std::string inOrOut; // "in" or "out"
	if (checkOut) // if bool = true, "out" will be used
	{
		inOrOut = "out";
	}
	else
	{
		inOrOut = "in";
	}

	std::cout << "Enter a Book Title to Check " + inOrOut + ": "; // uses inOrOut from above if statement to insert in ot out into this cout 
	std::string bookTitle;
	std::getline(std::cin, bookTitle); // stores user input as bookTitle

	CheckInOrOutResult result = inventory.CheckInOrOutBook(bookTitle, checkOut); //checkOut = true or false; 

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
	int numBooks = inventory.NumberOfBooks(); // stores number of books in vector as numBooks
	if (numBooks > 0) // looking to see if numBooks is greater than 0
	{
		std::cout << std::endl; // new line
		std::cout << "\nThere are " << numBooks << " books in our library.\n"; // if so, it will print the number found here
	}
	else
	{
		std::cout << std::endl; // new line
		std::cout << "\nThere are no books to display.\n"; // if there is 0 books or less than 0 books in the vector, it will print this statement
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

void DisplayCheckedOutBooks() // case 7
{
	inventory.DisplayCheckedOutBooks(); // inventory = object
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