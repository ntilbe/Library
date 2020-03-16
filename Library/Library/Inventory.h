#include "book.h"
#include <iostream>
#include <vector>
#include <string>
#pragma once
class Inventory
{
public:
	std::vector<Book> Books;

private:
	void AddBook();
	void RemoveBook();
	Book FindBookByTitle();
	void CheckOutBook();
	void CheckInBook();
};

