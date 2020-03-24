#pragma once
enum class CheckInOrOutResult
{
	Success,
	BookNotFound,
	AlreadyCheckedIn,
	AlreadyCheckedOut,
	Failure
};