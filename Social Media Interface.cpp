#include "System.h"
#include <iostream>

//Bonus: searching faster by id can be done by sortig the users/themes/posts/comments by id and aplying binary search!

int main()
{

	/* System socialMedia;

	 User user("Ivan", "Ivanov", "ssd", 10);
	 User user1("Ivo", "Asenov", "ssd", 3);
	 User user2("Pesho", "Petrov", "ssd", 5);
	 User user3("Krasi", "Arabadjiev", "ssd", 9);
	 socialMedia.addUser(user);
	 socialMedia.addUser(user1);
	 socialMedia.addUser(user2);
	 socialMedia.addUser(user3);

	 Comment example("Ivan", "I want to participate!", 1);
	 Comment reply1("Georgi", "You cannot!", 2);
	 Comment reply2("Misho", "We accept you!", 3);

	 Theme theme("PROGRAMMING", "Joro", "Best forum", 19);
	 Post post2("What is java", "Discussion about jvav", 5);
	 theme.addPost(post2);

	 Theme theme1("OOP", "Ivancho", "Learning", 4);
	 Theme theme2("Farming", "Lora", "animals", 14);
	 Theme theme3("Fishing", "Iva", "fish", 22);

	 socialMedia.addTheme(theme);
	 socialMedia.addTheme(theme1);
	 socialMedia.addTheme(theme2);
	 socialMedia.addTheme(theme3);
	 */


	 //   System socialMedia2;
	 //   //socialMedia2.signup();
	 //   
	 //   socialMedia2.login();
	 //   //socialMedia2.search("F");
	 //   //socialMedia2.create();
	 //   socialMedia2.searchThemeByKeyword("F");
	 //   socialMedia2.openTheme("PROGRAMMING");
	 //   //socialMedia2.post();
	 //   socialMedia2.listPostsOfCurrentTheme();
	 //   socialMedia2.openPost("5");
	 //   //socialMedia2.comment();
	 //   socialMedia2.comments();
	 //   socialMedia2.reply(9756);
	 //   socialMedia2.upvote(9756);
	 //   socialMedia2.whoami();
	 //   socialMedia2.about(19);
	 //   

	 //   socialMedia.search("O");
	 //   socialMedia.login();
	 //   socialMedia.create();
	 //   socialMedia.signup();
	 //   socialMedia.login();*/
	 //   std::cout << "ok";


		/*
	   // MyVector<User> users;

		User user("Ivan", "Asenov", "ssd",3);
		std::ofstream ofs("fileForUsrs.txt");
		std::ifstream ifs("fileForUsrs.txt");
		user.saveUserToFile(ofs);
		ofs.close();
		User us;
		us.readUserFromFile(ifs);
		User user2("Iv0", "Asen", "ssd", 3);
		user.printUser();
		user2.printUser();
		us.printUser();
		//users.pushBack(user);
		//users.pushBack(user);
		//users.pushBack(user);
		//Theme th;
		//Theme ths;
		*/

		//std::ofstream ofs("fileForUsrs.txt");
		//Comment example("Ivan","I want to participate!",1);
		//Comment reply1("Georgi","You cannot!",2);
		//Comment reply2("Misho","We accept you!",3);
		//example.addReply(reply1);
		//example.addReply(reply2);
		////example.saveCommentInFile(ofs);
		//Comment example1("Ivo", "I want to parsssticipate!", 9);
		//Comment reply3("awdwa", "You canwwwnot!", 2);
		//reply3.addReply(example);
		//Comment reply4("adwawd", "We accewwwpt you!", 3);
		//example1.addReply(reply3);
		//example1.addReply(reply4);
		//example1.addReply(example);
		//example1.addReply(example);
		//example.printComment();
		//example1.printComment();
		//ofs.close();
		//std::ifstream ifs("fileForUsrs.txt");
		//example1.readCommentFromFile(ifs);
		/*
		std::ofstream ofs("fileForUsrs.txt");
		Comment example("Ivan", "I want to participate!", 1);
		Comment reply1("Georgi", "You cannot!", 2);
		Comment reply2("Misho", "We accept you!", 3);
		example.addReply(reply1);
		example.addReply(reply2);
		Post post("What is OOP", "Discussion about OOP", 3);
		post.addComment(example);
		//post.savePostInFile(ofs);
		*/
		/*
		std::ifstream ifs("fileForUsrs.txt");
		Post post2("What is java", "Discussion about jvav", 5);
		//post2.readPostFromFile(ifs);
		Theme theme("PROGRAMMING", "Joro", "Best forum", 19);
		theme.addPost(post);
		theme.addPost(post2);
		theme.saveThemeInFile(ofs);
		ofs.close();
		Theme theme2("PROGRAMM2222ING", "J222oro", "B222est foru22m", 19);
		theme2.readThemeFromFile(ifs);
		std::cout << "OK";
		*/

// this can be extracted in a function in the class sytem as run(); but i decided to put it here
	System system;
	std::cout<<"Welcome to our Social Media!" << std::endl;
	std::cout << "Enter command: ";
	MyString command;
	std::cin >> command;
	while (command != "CLOSE")
	{
		//switch alternative solution
		if (command == "signup")
		{
			system.signup();
		}
		else if (command == "login")
		{
			system.login();
		}
		else if (command == "search")
		{
			std::cout << "Search for: ";
			char pattern[BUFF_SIZE];
			std::cin.getline(pattern, BUFF_SIZE);
			system.searchThemeByKeyword(pattern);
		}
		else if (command == "create")
		{
			system.createTheme();
		}
		else if (command == "open")
		{
			std::cout << "Enter theme id or name: ";
			char text[BUFF_SIZE];
			std::cin.getline(text, BUFF_SIZE);
			system.openTheme(text);
		}
		else if (command == "list")
		{
			system.listPostsOfCurrentTheme();
		}
		else if (command == "post")
		{
			system.post();
		}
		else if (command == "open_p")
		{
			std::cout << "Enter post id or name: ";
			char text[BUFF_SIZE];
			std::cin.getline(text, BUFF_SIZE);
			system.openPost(text);
		}
		else if (command == "comment")
		{
			system.comment();
		}
		else if (command == "comments")
		{
			system.comments();
		}
		else if (command == "reply")
		{
			std::cout << "Enter comment id: ";
			unsigned id;
			std::cin >> id;
			std::cin.ignore();
			system.reply(id);
		}
		else if (command == "upvote")
		{
			std::cout << "Enter comment id: ";
			unsigned id;
			std::cin >> id;
			std::cin.ignore();
			system.upvote(id);
		}
		else if (command == "downvote")
		{
			std::cout << "Enter comment id: ";
			unsigned id;
			std::cin >> id;
			std::cin.ignore();
			system.downvote(id);
		}
		else if (command == "p_quit" || command == "p_close")
		{
			system.quitPost();
		}
		else if (command == "quit")
		{
			system.quit();
		}
		else if (command == "logout")
		{
			system.logout();
		}
		else if (command == "whoami")
		{
			system.whoami();
		}
		else if (command == "about")
		{
			std::cout << "Enter theme id: ";
			unsigned id;
			std::cin >> id;
			std::cin.ignore();
			system.about(id);
		}
		else {
			std::cout << "Invalid command!" << std::endl;
		}
		

		std::cout << "Enter command: ";
		std::cin >> command;
	}






}
