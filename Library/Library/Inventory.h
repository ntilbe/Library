#pragma once

#include "book.h"
#include <vector>
#include "CheckInOrOutResult.h"

class Inventory // Inventory = name of class
{
private:
	std::vector<Book> Books; // vector of data type Book, stores Books (vector of Books);

public:

	void DisplayAllBooks(); // displays all books in the library's inventory
	void DisplayCheckedOutBooks(); // shows books that are checked out
	int NumberOfBooks(); // displays the number of books in library's inventory
	Book GetBookByIndex(int index); // Book = vector
	void AddBook(Book book); // Add a book to the library
	void LoadBooks(); // this function loads books into vector
	void RemoveBook(std::string title); // Remove a book from the library
	int FindBookByTitle(std::string title); //For this project we are going to assume there are no duplicate named books
	CheckInOrOutResult CheckInOrOutBook(std::string title, bool checkOut); // Check out a book from the library

};
