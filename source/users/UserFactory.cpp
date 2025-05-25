#include "UserFactory.h"

User* UserFactory::create(UserType type)
{
	switch (type)
	{
	case UserType::Administrator:
		return new Administrator();
	case UserType::Teacher:
		return new Teacher();
	case UserType::Student:
		return new Student();
	default:
		throw std::logic_error("Unknown type");
	}
}

User* UserFactory::createWithParameters(UserType type, const char* name, const char* surname, int id, const char* password)
{
	switch (type)
	{
	case UserType::Administrator:
		return new Administrator(name, surname, id, password);
	case UserType::Teacher:
		return new Teacher(name, surname, id, password);
	case UserType::Student:
		return new Student(name, surname, id, password);
	default:
		throw std::logic_error("Unknown type");
	}
}