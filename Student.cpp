#include "Student.h"

Student::Student(const char* name, const char* surname, int id, const Mail& inbox, const char* password)
    : User(name, surname, id, inbox, password) {}
Student::Student(const char* name, const char* surname, int id, const char* password)
	: User(name, surname, id, password) {}

UserType Student::getUserType() const
{
	return UserType::Student;
}
User* Student::clone() const 
{
	return new Student(*this);
}
void Student::writeToBinaryFile(std::ofstream& ofs) const
{
	UserType type = UserType::Student;
	ofs.write((const char*)&type, sizeof(type));

	unsigned nameLength = stringLength(name);
	ofs.write((const char*)(&nameLength), sizeof(nameLength));
	ofs.write((const char*)name, nameLength);

	unsigned surnameLength = stringLength(surname);
	ofs.write((const char*)&surnameLength, sizeof(surnameLength));
	ofs.write((const char*)surname, surnameLength);

	ofs.write((const char*)&id, sizeof(id));

	inbox.writeToBinaryFile(ofs);

	unsigned passwordLength = stringLength(password);
	ofs.write((const char*)&passwordLength, sizeof(passwordLength));
	ofs.write((const char*)password, passwordLength);
}
void Student::printUser() const
{
	std::cout << name << ' ' << surname << " | Student | " << id << std::endl;
}

