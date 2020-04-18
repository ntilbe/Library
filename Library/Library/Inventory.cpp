#include "Inventory.h"
#include <vector>
#include <fstream>
#include <string>


int Inventory::NumberOfBooks()
{
	return Inventory::Books.size();
}

Book Inventory::GetBookByIndex(int index) // Book* Inventory is the pointer that gives access to the book
{
	return Inventory::Books[index]; // &Inventory will return the memory address
}

void Inventory::AddBook(Book book)
{
	int nextBookId = 0;
	if (Books.size() > 0)
		nextBookId = Books.back().Id + 1;

	book.Id = nextBookId + 1;

	Inventory::Books.push_back(book);

	std::ofstream oFile("books.txt", std::ios_base::app);
	oFile << book.GetBookFileData() << std::endl;
	oFile.close();
}

void Inventory::LoadBooks()
{
	std::ifstream inFile("books.txt");

	std::string bookData[4];
	// bookData[0] = Id
	// bookData[1] = Title
	// bookData[2] = Author
	// bookData[3] = checked out

	std::string bookLine;
	while (getline(inFile, bookLine))
	{
		size_t nextIndex = bookLine.find('|');
		bookData[0] = bookLine.substr(0, nextIndex);

		size_t prevIndex = nextIndex;
		nextIndex = bookLine.find('|', prevIndex + 1);

		bookData[1] = bookLine.substr(prevIndex + 1, nextIndex - prevIndex - 1);
		prevIndex = nextIndex;
		nextIndex = bookLine.find('|', prevIndex + 1);

		bookData[2] = bookLine.substr(prevIndex + 1, nextIndex - prevIndex - 1);
		prevIndex = nextIndex;
		nextIndex = bookLine.find('|', prevIndex + 1);

		bookData[3] = bookLine.substr(prevIndex + 1, nextIndex - prevIndex - 1);

		Book loadedBook(bookData[1], bookData[2]);
		loadedBook.Id = stoi(bookData[0]);
		loadedBook.CheckInOrOut(stoi(bookData[3]));

		Books.push_back(loadedBook);
	}
}

void Inventory::RemoveBook(std::string title)
{

	std::vector<Book>::iterator it = std::find(Inventory::Books.begin(), Inventory::Books.end(), Book(title, ""));

	if (it != Inventory::Books.end())
	{
		Inventory::Books.erase(it);
	}
}

int Inventory::FindBookByTitle(std::string title)
{
	std::vector<Book>::iterator it = std::find(Inventory::Books.begin(), Inventory::Books.end(), Book(title, ""));

	if (it == Inventory::Books.end())
	{
		return -1;
	}

	int index = it - Inventory::Books.begin();

	return index;
}

CheckInOrOutResult Inventory::CheckInOrOutBook(std::string title, bool checkOut)
{
	int foundBookIndex = FindBookByTitle(title);

	if (foundBookIndex < 0)
	{
		return CheckInOrOutResult::BookNotFound;
	}
	else if (checkOut == Books[foundBookIndex].IsCheckedOut())
	{

		if (checkOut)
		{
			return CheckInOrOutResult::AlreadyCheckedOut;
		}
		else
		{
			return CheckInOrOutResult::AlreadyCheckedIn;
		}
	}
	

	Books[foundBookIndex].CheckInOrOut(checkOut);

	std::ofstream oFile("books.txt"); // don't need the ios_base::app (append) because we want to overwrite this whether it is checked in or out
	for (int i = 0; i < Books.size(); i++) // loop to find book and to see if it is checked in or out
	{
		oFile << Books[i].GetBookFileData() << std::endl; //the GetBookFileData seperates the info with pipes ( | ) and will be shown in the txt file with this line
	}

	return CheckInOrOutResult::Success;
}

void Inventory::DisplayAllBooks()
{
	std::cout << "\nID\tTitle\tAuthor" << std::endl;
	for (int i = 0; i < NumberOfBooks(); i++) // Goes from 0 to the size of the vector (ex. if there are 10 elements in the vector, it will be 10
	{
		Books[i].DisplayBook();
	}
	std::cout << std::endl;
}

void Inventory::DisplayCheckedOutBooks()
{
	std::cout << "\nID\tTitle\tAuthor" << std::endl;
	for (int i = 0; i < NumberOfBooks(); i++) // Goes from 0 to the size of the vector (ex. if there are 10 elements in the vector, it will be 10
	{
		if (GetBookByIndex(i).IsCheckedOut())
		{
			Books[i].DisplayBook();
		}
	}
	std::cout << std::endl;
}
