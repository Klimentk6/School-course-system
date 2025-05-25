#pragma once
#include <iostream>
#include <fstream>
#include "Utils.h"
#include "Mail.h"

using namespace Utils;

class User
{
public:
	User();
	User(const char* name, const char* surname, int id, const Mail& inbox, const char* password);
	User(const char* name, const char* surname, int id, const char* password);
	User(const User& other);
	User& operator=(const User& other);
	virtual ~User();

	virtual UserType getUserType() const = 0;
	virtual User* clone() const = 0;
	virtual void writeToBinaryFile(std::ofstream& ofs) const = 0;
	virtual void printUser() const = 0;

	int getId() const;
	void readFromBinaryFile(std::ifstream& ifs);
	bool isPasswordCorrect(const char* checkPassword) const;
	void changePassword(const char* newPassword);
	void addMessage(const Message& newMessage);
	void printInbox() const;
	void clearMailbox();

protected:
	char* name;
	char* surname;
	int id;
	Mail inbox;
	char* password;

	void copyFrom(const User& other);
	void free();
};

