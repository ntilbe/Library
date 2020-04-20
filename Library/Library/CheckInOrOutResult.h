#pragma once
enum class CheckInOrOutResult // list of like/similar objects
{
	Success, // options to use for book is checked in or out result
	BookNotFound,
	AlreadyCheckedIn,
	AlreadyCheckedOut,
	Failure
};