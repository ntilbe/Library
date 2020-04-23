#pragma once
#include <iostream>

class Book
{

private: //set to private so no changes can be made
	std::string Title; 
	std::string Author;
	bool CheckedOut;
	// can use setter/getter for private data ONLY within the class
public:
	int Id; // book ID

	Book(); //constructor with no parameters - also called default constructor
	Book(std::string title, std::string author); //constructor

	void CheckInOrOut(bool checkout);
	void DisplayBook();
	bool IsCheckedOut();
	std::string GetBookFileData();

	bool operator==(const Book &book) const // syntax for operator operator 
	{
		if (Title.compare(book.Title) == 0) // comparing two book titles, if they match or not
			return true;
		else
			return false;
	}

};

