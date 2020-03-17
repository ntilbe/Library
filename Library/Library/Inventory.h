#pragma once
#include "book.h"
#include <vector>

class Inventory
{
public:
	std::vector<Book> Books;
	void AddBook(Book book);
	void RemoveBook();
	Book FindBookByTitle();
	void CheckOutBook();
	void CheckInBook();
};

