#include "Inventory.h"
#include <vector>
#include <fstream>
#include <string>


int Inventory::NumberOfBooks()
{
	return Inventory::Books.size(); // returns number of books in current inventory
}

Book Inventory::GetBookByIndex(int index) // Book* Inventory is the pointer that gives access to the book
{
	return Inventory::Books[index]; // &Inventory will return the memory address
}

void Inventory::AddBook(Book book)
{
	int nextBookId = 0; // needs an intital value
	if (Books.size() > 0) // checking to see if the size of the vector is greater than 0
		nextBookId = Books.back().Id; // Books.back function checks ID of the last book in the vector 

	book.Id = nextBookId + 1; // sets book.Id equal to nextBookId(last book in vector) and adds 1 to set next book ID

	Inventory::Books.push_back(book); // push_back adds book added to last place in the vector

	std::ofstream oFile("books.txt", std::ios_base::app); // opens txt file, setting file to append next book
	oFile << book.GetBookFileData() << std::endl; // writing book data to file using GetBookFileData function (refer to Book.cpp)
	oFile.close(); // closes file
}
// ofstream = writing to file
// ifstream = reading file

void Inventory::LoadBooks()
{
	std::ifstream inFile("books.txt"); //opens file to be read

	std::string bookData[4];
	// bookData[0] = Id
	// bookData[1] = Title
	// bookData[2] = Author
	// bookData[3] = checked out

	std::string bookLine;
	while (getline(inFile, bookLine)) // reading file line by line, stores line in bookLine
	{
		size_t nextIndex = bookLine.find('|'); // finds the first | in line
		bookData[0] = bookLine.substr(0, nextIndex); // grabs data from index 0 to | and stores it as bookData[0] (this line is the book ID)

		size_t prevIndex = nextIndex; // saves index of first | as prevIndex
		nextIndex = bookLine.find('|', prevIndex + 1); // starts at prevIndex and finds location of next |

		bookData[1] = bookLine.substr(prevIndex + 1, nextIndex - prevIndex - 1); // finds first | and finds how many characters are between the first and second | (this is the book title)
		prevIndex = nextIndex; // first | now is equal to second |
		nextIndex = bookLine.find('|', prevIndex + 1); //  starts at the second | and finds the location of the next | 

		bookData[2] = bookLine.substr(prevIndex + 1, nextIndex - prevIndex - 1); // finds second | and finds how many characters are between the second and third | (this is the book author)

		bookData[3] = bookLine.substr(nextIndex + 1); // grabs data from the third | to the end of that line

		Book loadedBook(bookData[1], bookData[2]); // creating a new book variable with bookData[1] and [2] (title and author)
		loadedBook.Id = stoi(bookData[0]); // bookData[0] (which is a book ID) will be stored as loadedBook.Id
		loadedBook.CheckInOrOut(stoi(bookData[3])); // bookData[3] (which is checked out status) will be stored as loadedBook.CheckInOrOut
		//CheckInOrOut has bool parameter, file stores bookData[3] as 0 or 1, converts 0 to false and 1 to true

		Books.push_back(loadedBook); // pushes loadedBook data to last place in the vector
	}
}

void Inventory::RemoveBook(std::string title)
{
	//TODO: switch void to bool and remove cout in library.cpp, use if statement here to return something to library.cpp and cout something
	std::vector<Book>::iterator it = std::find(Inventory::Books.begin(), Inventory::Books.end(), Book(title, "")); // searches vector by book title

	if (it != Inventory::Books.end()) // book was found in vector
	{
		Inventory::Books.erase(it); // removes said book from vector
	}
	std::ofstream oFile("books.txt"); // don't need the ios_base::app (append) because we want to overwrite this; rewrites txt file which will remove said book
	for (int i = 0; i < Books.size(); i++) // loops through entire vector
	{
		oFile << Books[i].GetBookFileData() << std::endl; //the GetBookFileData seperates the info with pipes ( | ) and will be shown in the txt file with this line
	}
}

int Inventory::FindBookByTitle(std::string title)
{
	std::vector<Book>::iterator it = std::find(Inventory::Books.begin(), Inventory::Books.end(), Book(title, "")); // searches vector by book title 

	if (it == Inventory::Books.end()) // if it gets to the end of the book vector, returns -1, no title found
	{
		return -1;
	}

	int index = it - Inventory::Books.begin();
	// it = the location of where the book was found within the vector
	// calculates where it is located in reference from the beginning (ex. 4th book in would be index location = 3)
	return index;
}

CheckInOrOutResult Inventory::CheckInOrOutBook(std::string title, bool checkOut)
{
	int foundBookIndex = FindBookByTitle(title); // FindBookByTitle searches vector by Book title, gives location of index in vector

	if (foundBookIndex < 0) // if index is less than 0, Book was not found
	{
		return CheckInOrOutResult::BookNotFound;
	}
	else if (checkOut == Books[foundBookIndex].IsCheckedOut()) // checkOut will equal true or false && IsCheckedOut will equal true or false, enters if statement if both are true or both are false
	{

		if (checkOut) // if checkOut equals true then book is already checked out
		{
			return CheckInOrOutResult::AlreadyCheckedOut;
		}
		else // else it is checked in
		{
			return CheckInOrOutResult::AlreadyCheckedIn;
		}
	}	

	Books[foundBookIndex].CheckInOrOut(checkOut); 
	// getting the book from the index of foundBookIndex and calling CheckInOrOut function
	// making it to this function means the above "else if" was not equal to eadch other (i.e. true = true, false = false), this will check in if it is checked out or vice versa

	std::ofstream oFile("books.txt"); // don't need the ios_base::app (append) because we want to overwrite this whether it is checked in or out
	for (int i = 0; i < Books.size(); i++) // loops through entire Book vector
	{
		oFile << Books[i].GetBookFileData() << std::endl; //the GetBookFileData seperates the info with pipes ( | ) and will be shown in the txt file with this line
	}

	return CheckInOrOutResult::Success; // means book was found and wasn't already set to status currently trying to be set
}

void Inventory::DisplayAllBooks()
{
	std::cout << "\nID\tTitle\tAuthor" << std::endl; // seperates ID, Title, and Author by tab
	for (int i = 0; i < NumberOfBooks(); i++) // Goes from 0 to the size of the vector (ex. if there are 10 elements in the vector, it will be 10
	{
		Books[i].DisplayBook(); // vector of Books, displays books one by one in DisplayBook format (refer to book.cpp)
	}
	std::cout << std::endl;
}

void Inventory::DisplayCheckedOutBooks()
{
	std::cout << "\nID\tTitle\tAuthor" << std::endl;
	for (int i = 0; i < NumberOfBooks(); i++) // Goes from 0 to the size of the vector (ex. if there are 10 elements in the vector, it will be 10
	{
		if (GetBookByIndex(i).IsCheckedOut()) // finding book by index and whether it is checked out
		{
			Books[i].DisplayBook(); // displays book checked out
		}
	}
	std::cout << std::endl;
}
