#pragma once
#include "MyString.h"
#include "MyVector.hpp"
#include "Comment.h"
class Post
{
	MyString _title;
	MyString _information;
	unsigned _id;
	MyVector<Comment> comments;

	bool isCommentIdUnique(unsigned id) const;
	
public:
	Post();
	Post(const MyString& title, const MyString& information, unsigned id);
	void savePostInFile(std::ofstream& ofs) const;
	void readPostFromFile(std::ifstream& ifs);
	void addComment(const Comment& comment);
	void addComment(Comment&& comment);
	const MyString& getTitle() const;
	unsigned getId() const;
	unsigned generateRandomCommentId() const;
	void replyToComment(unsigned commentId, const MyString& creator, const MyString& replyContent, unsigned id);
	void upvoteToComment(unsigned commentId, unsigned userId);
	void downvoteToComment(unsigned commentId, unsigned userId);
	void commentsUnderPost() const;
	
};

