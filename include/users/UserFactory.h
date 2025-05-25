#pragma once
#include "Utils.h"
#include "Administrator.h"
#include "Teacher.h"
#include "Student.h"

using namespace Utils;

class UserFactory
{
public:
	static User* create(UserType type);
	static User* createWithParameters(UserType type, const char* name, const char* surname, int id, const char* password);
};

