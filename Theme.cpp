#include "Theme.h"

bool Theme::isPostIdUnique(unsigned id) const 
{
	size_t postsCount = posts.getSize();
	for (size_t i = 0; i < postsCount; i++)
	{
		if (posts[i].getId() == id)
		{
			return false;
		}
	}
	return true;
}

Theme::Theme():_headline("unknown"),_creator("Unknown"),_description("none"),_id(0){}
Theme::Theme(const MyString& headline, const MyString& creator, const MyString& description, unsigned id): _headline(headline),
_creator(creator),_description(description),_id(id){}

void Theme::saveThemeInFile(std::ofstream& ofs) const
{
	_headline.saveMyStringToFile(ofs);
	_creator.saveMyStringToFile(ofs);
	_description.saveMyStringToFile(ofs);
	ofs.write((const char*)&_id, sizeof(_id));
	size_t postsCount = posts.getSize();
	ofs.write((const char*)&postsCount, sizeof(postsCount));
	for (size_t i = 0; i < postsCount; i++)
	{
		posts[i].savePostInFile(ofs);
	}
}
void Theme::readThemeFromFile(std::ifstream& ifs)
{
	_headline.readMyStringFromFile(ifs);
	_creator.readMyStringFromFile(ifs);
	_description.readMyStringFromFile(ifs);
	ifs.read((char*)&_id, sizeof(_id));
	size_t postsCount;
	ifs.read((char*)&postsCount, sizeof(postsCount));
	for (size_t i = 0; i < postsCount; i++)
	{
		Post postToAdd;
		postToAdd.readPostFromFile(ifs);
		posts.pushBack(std::move(postToAdd));
	}
}

unsigned Theme::getId() const 
{
	return _id;
}
const MyString& Theme::getHeadline() const {
	return _headline;
}

void Theme::addPost(const Post& post)
{
	posts.pushBack(post);
}
void Theme::addPost(Post&& post)
{
	posts.pushBack(std::move(post));
}

void Theme::printPosts() const 
{
	size_t postsCount = posts.getSize();
	for (size_t i = 0; i < postsCount; i++)
	{
		std::cout << "-> " << posts[i].getTitle() << " { " << posts[i].getId() << " }"<<std::endl;
	}
}

unsigned Theme::generateRandomPostId() const {
	unsigned result = generateRandomNumber();
	while (!isPostIdUnique(result))
	{
		result = generateRandomNumber();
	}
	return result;
}

Post* Theme::findPostInTheme(const MyString& title) 
{
	size_t postsCount = posts.getSize();
	for (size_t i = 0; i < postsCount; i++)
	{
		if (posts[i].getTitle() == title)
		{
			return (&posts[i]);
		}
	}
	return nullptr;
}
Post* Theme::findPostInTheme(unsigned id) 
{
	size_t postsCount = posts.getSize();
	for (size_t i = 0; i < postsCount; i++)
	{
		if (id == posts[i].getId())
		{
			return &posts[i];
		}
	}
	return nullptr;
}

void Theme::printAboutTheme() const
{
	std::cout << "Name: " << _headline << std::endl;
	std::cout << "Descriptions: " << _description << std::endl;
	std::cout << "Creator: " << _creator << std::endl;
	std::cout << "Questions asked: " << posts.getSize() << std::endl;

}