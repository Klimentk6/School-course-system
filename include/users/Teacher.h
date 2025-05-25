#pragma once
#include <iostream>
#include <fstream>
#include "Utils.h"
#include "User.h"

using namespace Utils;

class Teacher : public User
{
public:
	Teacher() = default;
	Teacher(const char* name, const char* surname, int id, const Mail& inbox, const char* password);
	Teacher(const char* name, const char* surname, int id, const char* password);
	Teacher(const Teacher& other) = default;
	Teacher& operator=(const Teacher& other) = default;
	~Teacher() = default;

	UserType getUserType() const override;
	User* clone() const override;
	void writeToBinaryFile(std::ofstream& ofs) const override;
	void printUser() const override;
};

