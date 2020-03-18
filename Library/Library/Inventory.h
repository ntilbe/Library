#pragma once

#include "book.h"
#include <vector>

class Inventory
{
public:
	std::vector<Book> Books;
	void AddBook(Book book);
	void RemoveBook(Book book);
	bool FindBookByTitle(std::string title, Book &book); //For this project we are going to assume there are no duplicate named books
	void CheckOutBook(Book &book);
	void CheckInBook(Book &book);
};

