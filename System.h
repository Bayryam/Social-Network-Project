#pragma once
#include "MyVector.hpp"
#include "User.h"
#include "Theme.h"
#include "HelperFunctions.h"
class System
{
	MyVector<User> users;
	MyVector<Theme> themes;
	//the following three poiters can be replaced by indexes of the user/theme/post in the vector they are in and jus call users[index] for example
	User* userUsingTheSystem = nullptr;
	Theme* currentTheme = nullptr;
	Post* currentPost = nullptr;

	void readUsersFromFile(std::ifstream& ifs);
	void saveUsersInFile(std::ofstream& ofs) const;
	void readThemesFromFile(std::ifstream& ifs);
	void saveThemesInFile(std::ofstream& ofs) const;

	bool isUserIdUnique(unsigned id) const;
	unsigned generateRandomUserId() const;
	bool isThemeIdUnique(unsigned id) const;
	unsigned generateRandomThemeId() const;

	User* findUser(const MyString& firstName, const MyString& password);
	Theme* findTheme(const MyString& headline);
	Theme* findTheme(unsigned id);

	void readSystemFromFile();
	void saveSystemInFile() const;

public:
	System();
	~System();
	

	void addUser(const User& user);
	void addUser(User&& user);
	void addTheme(const Theme& theme);
	void addTheme(Theme&& theme);

	void signup();
	void login();
	void searchThemeByKeyword(const MyString& pattern) const;
	void createTheme();
	void openTheme(const MyString& input);
	void listPostsOfCurrentTheme() const;
	void post();
	void openPost(const MyString& input);
	void comment();
	void comments() const;
	void reply(unsigned idOfComment);
	void upvote(unsigned id);
	void downvote(unsigned id);
	void quitPost();
	void quit();
	void logout();
	void whoami() const;
	void about(unsigned themeId);
};

