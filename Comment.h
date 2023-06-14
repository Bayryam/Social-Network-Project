#pragma once
#include "MyString.h"
#include "MyVector.hpp"

class Comment
{
	MyString _author;
	MyString _commentContent;
	unsigned _id;
	MyVector<Comment> replys;
	MyVector<unsigned> upvotes;
	MyVector<unsigned> downvotes;

	void saveReplysInFile(std::ofstream& ofs) const;
	void readReplysFromFile(std::ifstream& ifs);

	void saveVotes(std::ofstream& ofs,const MyVector<unsigned>& votes) const;
	void readVotes(std::ifstream& ifs,MyVector<unsigned>& votes);
	void saveUpAndDownVotesInFile(std::ofstream& ofs) const;
	void readUpAndDownVotesFromFile(std::ifstream& ifs);
	void printReplys() const;
	void printReply() const;

	
public:

	//added not only replaying and voting on comments but also to replays
	//printing of comments and their replays when it is very complicated is not printed as it should be but we have to save
	//some kind of spaces which will just complicate the program so i decided not to put
	bool addReplyToCommentOrReply(unsigned commentId, const MyString& creator, const MyString& replyContent, unsigned id);
	bool upvoteOnReplysOrComment(unsigned commentId, unsigned userId);
	bool downvoteOnReplysOrComment(unsigned commentId, unsigned userId);
	Comment();
	Comment(const MyString& author, const MyString& commentContent, unsigned id);
	void saveCommentInFile(std::ofstream& ofs) const;
	void readCommentFromFile(std::ifstream& ifs);
	unsigned getId() const;
	void addReply(const Comment& reply);
	void addReply(Comment&& reply);
	void printComment() const;
	void upvote(unsigned userId);
	void downvote(unsigned userId);

};

