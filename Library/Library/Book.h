#pragma once
#include <iostream>

class Book
{
public:
	int Id;
	std::string Title;
	std::string Author;
	bool CheckedOut;
	std::string LastCheckedOutDate;

	Book();
	Book(int id, std::string title, std::string author); //constructor

	bool operator==(const Book &book) const
	{
		if (Title.compare(book.Title) == 0)
			return true;
		else
			return false;
	}

};

