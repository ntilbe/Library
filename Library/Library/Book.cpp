#include "Book.h"
#include <string>

Book::Book(){} //allows you to create a book with no parameters

Book::Book(std::string title, std::string author) //constructor
{
	Book::Title = title;
	Book::Author = author;
	Book::CheckedOut = false;
}

void Book::CheckInOrOut(bool checkOut) // setter; doing this because bool checkedOut is private
{
	CheckedOut = checkOut;
}

void Book::DisplayBook()
{
	std::cout << Id << "\t" << Title << "\t" << Author << std::endl; // cout book ID, Title, and Author, seperated by a tab; the actual book
}

bool Book::IsCheckedOut() // getter
{
	return CheckedOut;
}

std::string Book::GetBookFileData()
{

	return std::to_string(Id) + " | " + Title + " | " + Author + " | " + (CheckedOut ? "1" : "0");
}