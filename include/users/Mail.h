#pragma once
#include <iostream>
#include <fstream>
#include <ctime>
#include "Utils.h"
#include "Message.h"

using namespace Utils;

class Mail
{
public:
	Mail();
	Mail(const Message* arr, int size);
	Mail(const Mail& other);
	Mail& operator=(const Mail& other);
	~Mail();
	
	void readFromBinaryFile(std::ifstream& ifs);
	void writeToBinaryFile(std::ofstream& ofs) const;

	void addNewMessage(const Message& newMessage);
	void printMail() const;
	void clear();

private:
	void copyFrom(const Mail& other);
	void free();

	int calculateCapacity(int size);
	void resize(int newCapacity);

	Message* arr;
	int size;
	int capacity;
};

