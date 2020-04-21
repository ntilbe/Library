#pragma once
#include <iostream>
#include "Role.h"
#include <vector>

class User
{
public:
	int Id;
	std::string FirstName;
	std::string LastName;
	std::string Username;
	Role Role;

	bool operator==(const User& user) const // overload == operator, allows comparison of two users
	{
		if (Username.compare(user.Username) == 0) // looking to see if username 1 is equal to username 2
			return true;
		else
			return false;
	}
};


