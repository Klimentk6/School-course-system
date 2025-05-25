#pragma once
#include <iostream>
#include <fstream>
#include <ctime>
#include <iomanip>
#include "Utils.h"

using namespace Utils;

class Message
{
public:
	Message();
	Message(int senderId, const char* content, std::time_t timeSent);
	Message(const Message& other);
	Message& operator=(const Message& other);
	~Message();

	void readFromBinaryFile(std::ifstream& ifs);
	void writeToBinaryFile(std::ofstream& ofs) const;
	void printMessage() const;

private:
	void copyFrom(const Message& other);
	void free();

	int senderId;
	char* content;
	std::time_t timeSent;
};

