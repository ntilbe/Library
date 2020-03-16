#include <iostream>
#pragma once
class Book
{
public:
	int Id;
	std::string Title;
	std::string Author;
	bool CheckedOut;
	std::string LastCheckedOutDate;

	Book(std::string title, std::string author);
};

