#pragma once
#include "MyString.h"


class User
{
	MyString _firstName;
	MyString _lastName;
	MyString _password;
	unsigned _id;
	unsigned _points;
public:
	User();
	User(const MyString& firstName, const MyString& lastName, const MyString& password, unsigned id);
	void saveUserInFile(std::ofstream& ofs) const;
	void readUserFromFile(std::ifstream& ifs);
	void printUser() const;
	unsigned getId() const;
	const MyString& getFirstName() const;
	const MyString& getLastName() const;
	bool isPasswordCorrect(const MyString& password) const;
	void vote();
};

