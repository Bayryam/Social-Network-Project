#pragma once
#include "MyString.h"
#include "MyVector.hpp"
#include "Post.h"
class Theme
{
	MyString _headline;
	MyString _creator;
	MyString _description;
	unsigned _id;
	MyVector<Post> posts;
	bool isPostIdUnique(unsigned id) const;
	
public:
	Theme();
	Theme(const MyString& headline, const MyString& creator, const MyString& description, unsigned id);

	void saveThemeInFile(std::ofstream& ofs) const;
	void readThemeFromFile(std::ifstream& ifs);

	unsigned getId() const;
	const MyString& getHeadline() const;

	void addPost(const Post& post);
	void addPost(Post&& post);
	void printPosts() const;
	unsigned generateRandomPostId() const;
	void printAboutTheme() const;
	
	Post* findPostInTheme(const MyString& title) ;
	Post* findPostInTheme(unsigned id) ;


};

