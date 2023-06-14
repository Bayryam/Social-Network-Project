#include "System.h"

System::System()
{
	readSystemFromFile();
}

void System::readUsersFromFile(std::ifstream& ifs)
{
	size_t usersCount;
	ifs.read((char*)&usersCount, sizeof(usersCount));
	for (size_t i = 0; i < usersCount; i++)
	{
		User userToAdd;
		userToAdd.readUserFromFile(ifs);
		users.pushBack(std::move(userToAdd));
	}
}
void System::saveUsersInFile(std::ofstream& ofs) const
{
	size_t usersCount = users.getSize();
	ofs.write((const char*)&usersCount, sizeof(usersCount));
	for (size_t i = 0; i < usersCount; i++)
	{
		users[i].saveUserInFile(ofs);
	}
}
void System::readThemesFromFile(std::ifstream& ifs)
{
	size_t themesCount;
	ifs.read((char*)&themesCount, sizeof(themesCount));
	for (size_t i = 0; i < themesCount; i++)
	{
		Theme themeToAdd;
		themeToAdd.readThemeFromFile(ifs);
		themes.pushBack(std::move(themeToAdd));
	}
}
void System::saveThemesInFile(std::ofstream& ofs) const
{
	size_t themesCount = themes.getSize();
	ofs.write((const char*)&themesCount, sizeof(themesCount));
	for (size_t i = 0; i < themesCount; i++)
	{
		themes[i].saveThemeInFile(ofs);
	}
}

bool System::isUserIdUnique(unsigned id) const
{
	size_t usersCount = users.getSize();
	for (size_t i = 0; i < usersCount; i++)
	{
		if (users[i].getId() == id)
		{
			return false;
		}
	}
	return true;
}
unsigned System::generateRandomUserId() const
{
	unsigned result = generateRandomNumber();
	while (!isUserIdUnique(result))
	{
		result = generateRandomNumber();
	}
	return result;
}
bool System::isThemeIdUnique(unsigned id) const
{
	size_t ThemesCount = themes.getSize();
	for (size_t i = 0; i < ThemesCount; i++)
	{
		if (themes[i].getId() == id)
		{
			return false;
		}
	}
	return true;
}
unsigned System::generateRandomThemeId() const
{
	unsigned result = generateRandomNumber();
	while (!isThemeIdUnique(result))
	{
		result = generateRandomNumber();
	}
	return result;
}

User* System::findUser(const MyString& firstName, const MyString& password)
{
	for (size_t i = 0; i < users.getSize(); i++)
	{
		if (firstName == users[i].getFirstName() && users[i].isPasswordCorrect(password))
		{
			return &users[i];
		}
	}
	return nullptr;
}
Theme* System::findTheme(const MyString& headline)
{
	size_t themesCount = themes.getSize();
	for (size_t i = 0; i < themesCount; i++)
	{
		if (headline == themes[i].getHeadline())
		{
			return &themes[i];
		}
	}
	return nullptr;
}
Theme* System::findTheme(unsigned id)
{
	size_t themesCount = themes.getSize();
	for (size_t i = 0; i < themesCount; i++)
	{
		if (id == themes[i].getId())
		{
			return &themes[i];
		}
	}
	return nullptr;
}


void System::readSystemFromFile()
{
	std::ifstream ifs("fileForUsrs.txt", std::ios::in | std::ios::binary);
	if (!ifs.is_open())
	{
		std::cout << "Error openning the file!" << std::endl;
	}
	readUsersFromFile(ifs);
	readThemesFromFile(ifs);
	ifs.clear();
	ifs.close();
}
void System::saveSystemInFile() const
{
	std::ofstream ofs("fileForUsrs.txt", std::ios::out | std::ios::binary);
	if (!ofs.is_open())
	{
		std::cout << "Error openning the file!" << std::endl;
	}
	saveUsersInFile(ofs);
	saveThemesInFile(ofs);
	ofs.clear();
	ofs.close();
}

void System::addUser(const User& user)
{
	users.pushBack(user);
}
void System::addUser(User&& user)
{
	users.pushBack(std::move(user));
}

void System::addTheme(const Theme& theme)
{
	themes.pushBack(theme);
}
void System::addTheme(Theme&& theme)
{
	themes.pushBack(std::move(theme));
}

void System::signup()
{
	std::cout << "Sign up!" << std::endl;
	MyString firstName;
	MyString lastName;
	MyString password;
	std::cout << "Enter firstname: ";
	std::cin >> firstName;
	std::cout << "Enter lastname: ";
	std::cin >> lastName;
	std::cout << "Enter password: ";
	std::cin >> password;
	unsigned id = generateRandomUserId();
	User newUser(firstName, lastName, password, id);
	addUser(std::move(newUser));
	std::cout << "Account created!" << std::endl;
}
void System::login()
{
	std::cout << "Login!" << std::endl;
	MyString firstName;
	MyString password;
	std::cout << "Enter firstname: ";
	std::cin >> firstName;
	std::cout << "Enter password: ";
	std::cin >> password;
	userUsingTheSystem = findUser(firstName, password);
	if (userUsingTheSystem != nullptr)
		std::cout << "Welcome " << userUsingTheSystem->getFirstName() << ' ' << userUsingTheSystem->getLastName() << std::endl;
	else
		std::cout << "Incorrect login data!" << std::endl;
}
void System::searchThemeByKeyword(const MyString& pattern) const
{
	if (userUsingTheSystem == nullptr)
	{
		std::cout << "Not logged!" << std::endl;
		return;
	}
	bool isFound = false;
	for (size_t i = 0; i < themes.getSize(); i++)
	{
		if (isSubstr(pattern, themes[i].getHeadline()))
		{
			std::cout << "  #" << themes[i].getHeadline() << " { " << themes[i].getId() << " }" << std::endl;
			isFound = true;
		}
	}

	if (!isFound)
	{
		std::cout << "Nothing found!" << std::endl;
	}
}
void System::createTheme()
{
	if (userUsingTheSystem == nullptr)
	{
		std::cout << "Not logged!" << std::endl;
		return;
	}
	std::cout << "Enter headline: ";
	char buff[BUFF_SIZE];
	std::cin.getline(buff, BUFF_SIZE);
	MyString headline(buff);
	std::cout << "Enter description: ";

	std::cin.getline(buff, 1024);
	MyString description(buff);
	unsigned id = generateRandomThemeId();
	Theme newTheme(headline, userUsingTheSystem->getFirstName(), description, id);
	addTheme(std::move(newTheme));
	std::cout << "Theme " << newTheme.getHeadline() << " added!" << std::endl;

}
void System::openTheme(const MyString& input)
{
	if (userUsingTheSystem == nullptr)
	{
		std::cout << "Not logged!" << std::endl;
		return;
	}
	if (input.isNumber())
		currentTheme = findTheme(input.toNumber());
	else
		currentTheme = findTheme(input);

	if (currentTheme == nullptr)
		std::cout << "Such theme doesn't exist!" << std::endl;
	else
		std::cout << "Welcome to " << currentTheme->getHeadline() << "!" << std::endl;
}
void System::listPostsOfCurrentTheme() const
{
	if (userUsingTheSystem == nullptr)
	{
		std::cout << "Not logged!" << std::endl;
		return;
	}
	if (currentTheme == nullptr)
		std::cout << "You haven't opened a theme!" << std::endl;
	else
		currentTheme->printPosts();
}
void System::post()
{
	if (currentTheme == nullptr)
	{
		std::cout << "You haven't opened a theme!" << std::endl;
		return;
	}
	std::cout << "Enter title: ";
	char buff[BUFF_SIZE];
	std::cin.getline(buff, BUFF_SIZE);
	MyString title(buff);
	std::cout << "Enter information: ";
	std::cin.getline(buff, BUFF_SIZE);
	MyString information(buff);
	unsigned id = currentTheme->generateRandomPostId();
	Post postToAdd(title, information, id);
	std::cout << title << "added!" << std::endl;
	currentTheme->addPost(std::move(postToAdd));

}
void System::openPost(const MyString& input)
{
	if (currentTheme == nullptr)
	{
		std::cout << "You haven't opened a theme!" << std::endl;
		return;
	}

	if (input.isNumber())
		currentPost = currentTheme->findPostInTheme(input.toNumber());
	else
		currentPost = currentTheme->findPostInTheme(input);

	if (currentPost == nullptr)
		std::cout << "Such post doesn't exist!" << std::endl;
	else
		std::cout << "Welcome to " << currentPost->getTitle() << " !" << std::endl;
}
void System::comment()
{
	if (currentPost == nullptr)
	{
		std::cout << "You haven't opened a post!" << std::endl;
		return;
	}
	std::cout << "Say something: ";
	char buff[BUFF_SIZE];
	std::cin.getline(buff, BUFF_SIZE);
	MyString commentContent(buff);
	unsigned id = currentPost->generateRandomCommentId();
	Comment newComment(userUsingTheSystem->getFirstName(), commentContent, id);
	currentPost->addComment(std::move(newComment));
	std::cout << "Posted!" << std::endl;
}
void System::comments() const
{
	if (currentPost == nullptr)
	{
		std::cout << "You haven't opened a post!" << std::endl;
		return;
	}
	currentPost->commentsUnderPost();
}
void System::reply(unsigned idOfComment)
{
	if (currentPost == nullptr)
	{
		std::cout << "You haven't opened a post!" << std::endl;
		return;
	}
	std::cout << "Say something: ";
	char buff[BUFF_SIZE];
	std::cin.getline(buff, BUFF_SIZE);
	MyString replyContent(buff);
	unsigned id = currentPost->generateRandomCommentId();
	currentPost->replyToComment(idOfComment, userUsingTheSystem->getFirstName(), replyContent, id);
}
void System::upvote(unsigned id)
{
	currentPost->upvoteToComment(id, userUsingTheSystem->getId());
	userUsingTheSystem->vote();
}
void System::downvote(unsigned id)
{
	currentPost->downvoteToComment(id, userUsingTheSystem->getId());
	userUsingTheSystem->vote();
}
void System::quitPost()
{
	if (currentPost == nullptr)
	{
		std::cout << "You haven't opened a post!" << std::endl;
		return;
	}
	std::cout << "You exited from " << currentPost->getTitle() << "!" << std::endl;
	currentPost = nullptr;

}
void System::quit()
{
	if (currentTheme == nullptr)
	{
		std::cout << "You haven't opened a theme!" << std::endl;
		return;
	}
	std::cout << "You exited from " << currentTheme->getHeadline() << "!" << std::endl;
	currentTheme = nullptr;
	quitPost();
}
void System::logout()
{
	if (userUsingTheSystem == nullptr)
	{
		std::cout << "Not logged!" << std::endl;
		return;
	}
	std::cout << "Bye " << userUsingTheSystem->getFirstName() << "!" << std::endl;
	userUsingTheSystem = nullptr;
	quit();
}
void System::whoami() const
{
	if (userUsingTheSystem == nullptr)
	{
		std::cout << "Not logged!" << std::endl;
		return;
	}
	userUsingTheSystem->printUser();
}
void System::about(unsigned themeId)
{
	if (userUsingTheSystem == nullptr)
	{
		std::cout << "Not logged!" << std::endl;
		return;
	}
	Theme* th = findTheme(themeId);
	th->printAboutTheme();
}

System::~System()
{
	currentPost = nullptr;
	currentTheme = nullptr;
	userUsingTheSystem = nullptr;
	saveSystemInFile();
}