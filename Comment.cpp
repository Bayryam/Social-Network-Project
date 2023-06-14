#include "Comment.h"

Comment::Comment()
{
	_author = "unknown";
	_commentContent = "none";
	_id = 0;

}
Comment::Comment(const MyString& author, const MyString& commentContent, unsigned id):_author(author),_commentContent(commentContent),_id(id){}

void Comment::saveReplysInFile(std::ofstream& ofs) const
{
	unsigned replysCount = replys.getSize();
	ofs.write((const char*)&replysCount, sizeof(replysCount));
	for (size_t i = 0; i < replysCount; i++)
	{
		replys[i].saveCommentInFile(ofs);
	}
}
void Comment::readReplysFromFile(std::ifstream& ifs)
{
	unsigned replysCount;
	ifs.read((char*)&replysCount, sizeof(replysCount));
	for (size_t i = 0; i < replysCount; i++)
	{
		Comment newReply;
		newReply.readCommentFromFile(ifs);
		replys.pushBack(std::move(newReply));
	}
}

unsigned Comment::getId() const {
	return _id;
}

void Comment::saveVotes(std::ofstream& ofs, const MyVector<unsigned>& votes) const
{
	unsigned votesCount = votes.getSize();
	ofs.write((const char*)&votesCount, sizeof(votesCount));
	for (size_t i = 0; i < votesCount; i++)
	{
		ofs.write((const char*)&votes[i], sizeof(votes[i]));
	}
}
void Comment::readVotes(std::ifstream& ifs, MyVector<unsigned>& votes)
{
	unsigned votesCount;
	ifs.read((char*)&votesCount, sizeof(votesCount));
	for (size_t i = 0; i < votesCount; i++)
	{
		unsigned voteToAdd;
		ifs.read((char*)&voteToAdd, sizeof(voteToAdd));
		votes.pushBack(voteToAdd);
	}
}

void Comment::saveUpAndDownVotesInFile(std::ofstream& ofs) const
{
	saveVotes(ofs, upvotes);
	saveVotes(ofs, downvotes);
}
void Comment::readUpAndDownVotesFromFile(std::ifstream& ifs)
{
	readVotes(ifs, upvotes);
	readVotes(ifs, downvotes);
}

void Comment::saveCommentInFile(std::ofstream& ofs) const
{
	_author.saveMyStringToFile(ofs);
	_commentContent.saveMyStringToFile(ofs);
	ofs.write((const char*)&_id, sizeof(_id));
	saveReplysInFile(ofs);
	saveUpAndDownVotesInFile(ofs);
}
void Comment::readCommentFromFile(std::ifstream& ifs)
{
	_author.readMyStringFromFile(ifs);
	_commentContent.readMyStringFromFile(ifs);
	ifs.read((char*)&_id, sizeof(_id));
	readReplysFromFile(ifs);
	readUpAndDownVotesFromFile(ifs);
}

void Comment::addReply(const Comment& reply)
{
	replys.pushBack(reply);
}
bool Comment::addReplyToCommentOrReply(unsigned commentId, const MyString& creator, const MyString& replyContent, unsigned id)
{
	if (_id == commentId)
	{
		Comment newReply(creator, replyContent, id);
		addReply(std::move(newReply));
		std::cout << "Posted!" << std::endl;
		return true;
		
	}
	size_t repliesCount = replys.getSize();
	for (size_t i = 0; i < repliesCount; i++)
	{
		if (replys[i].addReplyToCommentOrReply(commentId, creator, replyContent, id))
		{
			std::cout << "Posted!" << std::endl;
			return true;
			
		}
	}
	return false;
}
void Comment::addReply(Comment&& reply)
{
	replys.pushBack(std::move(reply));
}

void Comment::printReply() const
{
	std::cout << "    - " << _commentContent << " { " << _id << " }" << std::endl;
	if (replys.getSize() != 0)
	{
		std::cout << "   Replays: " << std::endl;
	}

	printReplys();
}
void Comment::printReplys() const
{

	size_t replysCount = replys.getSize();
	for (size_t i = 0; i < replysCount; i++)
	{
		replys[i].printReply();
	}
}
void Comment::printComment() const
{
	std::cout << "Comment: " << _commentContent << " { " << _id << " }" << std::endl;
	if (replys.getSize() != 0)
	{
		std::cout << "Replays: " << std::endl;
	}

	printReplys();
}

bool Comment::upvoteOnReplysOrComment(unsigned commentId, unsigned userId)
{
	if (commentId == _id)
	{
		upvote(userId);
		return true;
	}

	size_t repliesCount = replys.getSize();
	for (size_t i = 0; i < repliesCount; i++)
	{
		if (replys[i].upvoteOnReplysOrComment(commentId, userId))
		{
			return true;
		}
	}
	return false;

}
bool Comment::downvoteOnReplysOrComment(unsigned commentId, unsigned userId)
{
	if (commentId == _id)
	{
		downvote(userId);
		return true;
	}

	size_t repliesCount = replys.getSize();
	for (size_t i = 0; i < repliesCount; i++)
	{
		if (replys[i].downvoteOnReplysOrComment(commentId, userId))
		{
			return true;
		}
	}
	return false;

}

void Comment::upvote(unsigned userId)
{
	if (upvotes.contains(userId))
		upvotes.remove(userId);
	else
		upvotes.pushBack(userId);

}
void Comment::downvote(unsigned userId)
{
	if (downvotes.contains(userId))
		downvotes.remove(userId);
	else
		downvotes.pushBack(userId);
}