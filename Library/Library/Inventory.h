#pragma once

#include "book.h"
#include <vector>

class Inventory
{
public:
	std::vector<Book> Books;
	void AddBook(Book book); // Add a book to the library
	void RemoveBook(Book book); // Remove a book from the library
	int FindBookByTitle(std::string title); //For this project we are going to assume there are no duplicate named books
	void CheckOutBook(Book &book); // Check out a book from the library
	void CheckInBook(Book &book); // Check in a book to the library
};
