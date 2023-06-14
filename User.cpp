#include "User.h"



User::User() :_firstName("unknown"), _lastName("unknown"), _password("pass"), _id(0), _points(0){}
User::User(const MyString& firstName, const MyString& lastName, const MyString& password, unsigned id) : _firstName(firstName),
_lastName(lastName), _password(password), _id(id), _points(0) {}


void User::saveUserInFile(std::ofstream& ofs) const
{
	_firstName.saveMyStringToFile(ofs);
	_lastName.saveMyStringToFile(ofs);
	_password.saveMyStringToFile(ofs);

	ofs.write((const char*)&_id, sizeof(_id));
	ofs.write((const char*)&_points, sizeof(_points));
}
void User::readUserFromFile(std::ifstream& ifs)
{
	_firstName.readMyStringFromFile(ifs);
	_lastName.readMyStringFromFile(ifs);
	_password.readMyStringFromFile(ifs);

	ifs.read((char*)&_id, sizeof(_id));
	ifs.read((char*)&_points, sizeof(_points));
}

void User::printUser() const
{
	std::cout << "User: " << _firstName << " " << _lastName << std::endl;
	std::cout << "User has " << _points << " points!" << std::endl;
}

unsigned User::getId() const
{
	return _id;
}
const MyString& User::getFirstName() const
{
	return _firstName;
}
const MyString& User::getLastName() const
{
	return _lastName;
}

bool User::isPasswordCorrect(const MyString& password) const
{
	return password == _password;
}

void User::vote()
{
	_points++;
}
