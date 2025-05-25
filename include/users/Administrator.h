#pragma once
#include <iostream>
#include <fstream>
#include "Utils.h"
#include "User.h"

using namespace Utils;

class Administrator : public User
{
public:
	Administrator() = default;
	Administrator(const char* name, const char* surname, int id, const Mail& inbox, const char* password);
	Administrator(const char* name, const char* surname, int id, const char* password);
	Administrator(const Administrator& other) = default;
	Administrator& operator=(const Administrator& other) = default;
	~Administrator() = default;

	UserType getUserType() const override;
	User* clone() const override;
	void writeToBinaryFile(std::ofstream& ofs) const override;
	void printUser() const override;
};

