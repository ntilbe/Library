#include "Inventory.h"
#include <vector>

void Inventory::AddBook(Book book)
{
	Inventory::Books.push_back(book);
}

int Inventory::FindBookByTitle(std::string title)
{
	std::vector<Book>::iterator it = std::find(Inventory::Books.begin(), Inventory::Books.end(), Book(0, title, ""));

	int index = it - Books.begin();

	return false;
}

void Inventory::CheckOutBook(Book &book)
{
	book.CheckedOut = true;
}
void Inventory::CheckInBook(Book &book)
{
	book.CheckedOut = false;
}

void Inventory::RemoveBook(Book book)
{
	int index = FindBookByTitle(book.Title);
	Inventory::Books.erase(Books.begin() + index);
}