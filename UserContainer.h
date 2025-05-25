#pragma once
#include <iostream>
#include <fstream>
#include <ctime>
#include "Utils.h"
#include "User.h"
#include "UserFactory.h"

using namespace Utils;

class UserContainer
{
public:
	UserContainer();
	UserContainer(const User* arr, int size);
	UserContainer(const char* fileName);
	UserContainer(const UserContainer& other);
	UserContainer& operator=(const UserContainer& other);
	~UserContainer();

	void readFromBinaryFile(const char* fileName);
	void writeToBinaryFile(const char* fileName) const;

	int getSize() const;
	User* getUserPointer(int index) const;
	bool isUserInTheContainer(int userId) const;

	void addAdministrator(const char* name, const char* surname, const char* password);
	void addTeacher(const char* name, const char* surname, const char* password);
	void addStudent(const char* name, const char* surname, const char* password);
	void removeUser(int id);
	void messageAll(int senderId, const char* content);

private:
	void copyFrom(const UserContainer& other);
	void free();

	void resize(int newCapacity);
	int calculateCapacity(int size) const;

	User** arr;
	int size;
	int capacity;
};

