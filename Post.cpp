#include "Post.h"

bool Post::isCommentIdUnique(unsigned id) const
{
	size_t commentsCount = comments.getSize();
	for (size_t i = 0; i < commentsCount; i++)
	{
		if (comments[i].getId() == id)
		{
			return false;
		}
	}
	return true;
}

Post::Post()
{
	_title = "unknown";
	_information = "none";
	_id = 0;
}
Post::Post(const MyString& title, const MyString& information, unsigned id) :_title(title), _information(information), _id(id) {}

void Post::savePostInFile(std::ofstream& ofs) const
{
	_title.saveMyStringToFile(ofs);
	_information.saveMyStringToFile(ofs);
	ofs.write((const char*)&_id, sizeof(_id));
	size_t commentsCount = comments.getSize();
	ofs.write((const char*)&commentsCount, sizeof(commentsCount));
	for (size_t i = 0; i < commentsCount; i++)
	{
		comments[i].saveCommentInFile(ofs);
	}

}
void Post::readPostFromFile(std::ifstream& ifs)
{
	_title.readMyStringFromFile(ifs);
	_information.readMyStringFromFile(ifs);
	ifs.read((char*)&_id, sizeof(_id));
	size_t commentsCount;
	ifs.read((char*)&commentsCount, sizeof(commentsCount));
	for (size_t i = 0; i < commentsCount; i++)
	{
		Comment commentToAdd;
		commentToAdd.readCommentFromFile(ifs);
		comments.pushBack(std::move(commentToAdd));
	}
}

void Post::addComment(const Comment& comment)
{
	comments.pushBack(comment);
}
void Post::addComment(Comment&& comment)
{
	comments.pushBack(std::move(comment));
}

const MyString& Post::getTitle() const
{
	return _title;
}
unsigned Post::getId() const {
	return _id;
}

unsigned Post::generateRandomCommentId() const
{
	unsigned result = generateRandomNumber();
	while (!isCommentIdUnique(result))
	{
		result = generateRandomNumber();
	}
	return result;
}
void Post::replyToComment(unsigned commentId, const MyString& creator, const MyString& replyContent, unsigned id)
{
	size_t commentsCount = comments.getSize();
	for (size_t i = 0; i < commentsCount; i++)
	{
		if (comments[i].addReplyToCommentOrReply(commentId, creator, replyContent, id)) 
		{
			return;
		}
	}
	std::cout << "Invalid comment id!" << std::endl;

	/*size_t commentsCount = comments.getSize();
	for (size_t i = 0; i < commentsCount; i++)
	{
		if (comments[i].getId() == commentId)
		{
			Comment newReply(creator, replyContent, id);
			comments[i].addReply(std::move(newReply));
			std::cout << "Posted!" << std::endl;
			return;
		}
		
	}
	std::cout << "Invalid comment id!" << std::endl;*/
}

void Post::upvoteToComment(unsigned commentId, unsigned userId)
{
	/*size_t commentsCount = comments.getSize();
	for (size_t i = 0; i < commentsCount; i++)
	{
		if (comments[i].getId() == commentId)
		{
			comments[i].upvote(userId);
			return;
		}
	}
	std::cout << "Invalid comment id!" << std::endl;*/

	size_t commentsCount = comments.getSize();
	for (size_t i = 0; i < commentsCount; i++)
	{
		if (comments[i].upvoteOnReplysOrComment(commentId,userId))
		{
			return;
		}
	}
	std::cout << "Invalid comment id!" << std::endl;

}
void Post::downvoteToComment(unsigned commentId, unsigned userId)
{
	/*size_t commentsCount = comments.getSize();
	for (size_t i = 0; i < commentsCount; i++)
	{
		if (comments[i].getId() == commentId)
		{
			comments[i].downvote(userId);
			return;
		}
	}
	std::cout << "Invalid comment!" << std::endl;*/

	size_t commentsCount = comments.getSize();
	for (size_t i = 0; i < commentsCount; i++)
	{
		if (comments[i].downvoteOnReplysOrComment(commentId, userId))
		{
			return;
		}
	}
	std::cout << "Invalid comment id!" << std::endl;
}

void Post::commentsUnderPost() const
{
	size_t commentsCount = comments.getSize();
	for (size_t i = 0; i < commentsCount; i++)
	{
		comments[i].printComment();
	}
}