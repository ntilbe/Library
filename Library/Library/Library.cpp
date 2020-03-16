#include <iostream>
#include "Book.h"

int main()
{
    int choice;

    do
    {
        std::cout << "1. Create New Book\n2.Check Out a New Book\n3.Check In a Book\n4.Exit";
        std::cin >> choice;

        switch (choice)
        {
        case 1:
            
            break;
        case 2:
            
            break;
        case 3:
            
            break;
        case 4:
            std::cout << "Thank you. Goodbye.\n";
            break;
        }
    } while (choice != 4);


}