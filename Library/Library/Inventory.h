#pragma once

#include "book.h"
#include <vector>
#include "CheckInOrOutResult.h"

class Inventory
{
private:
	std::vector<Book> Books;

public:

	void DisplayAllBooks();
	void DisplayCheckedOutBooks();
	int NumberOfBooks();
	Book GetBookByIndex(int index);
	void AddBook(Book book); // Add a book to the library
	void LoadBooks();
	void RemoveBook(std::string title); // Remove a book from the library
	int FindBookByTitle(std::string title); //For this project we are going to assume there are no duplicate named books
	CheckInOrOutResult CheckInOrOutBook(std::string title, bool checkOut); // Check out a book from the library

};
