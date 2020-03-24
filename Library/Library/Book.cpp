#include "Book.h"


Book::Book(){} //allows you to create a book with no parameters

Book::Book(std::string title, std::string author) //constructor
{
	Book::Title = title;
	Book::Author = author;
	Book::CheckedOut = false;
}

void Book::CheckInOrOut(bool checkOut) // setter
{
	CheckedOut = checkOut;
}

void Book::DisplayBook()
{
	std::cout << Id << "\t" << Title << "\t" << Author << std::endl; // Displays all books in inventory
}

bool Book::IsCheckedOut()
{
	return CheckedOut;
}

void Book::SetBookId(int id)
{
	Id = id;
}