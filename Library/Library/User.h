#include <iostream>
#include "Role.h"
#include <vector>
#pragma once

class User
{
public:
	int Id;
	std::string Name;
	Role Role;
	int vector CheckedOutBooks;

	User();
};



