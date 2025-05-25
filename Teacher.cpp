#include "Teacher.h"

Teacher::Teacher(const char* name, const char* surname, int id, const Mail& inbox, const char* password) 
	: User(name, surname, id, inbox, password) {};
Teacher::Teacher(const char* name, const char* surname, int id, const char* password)
	: User(name, surname, id, password) {}

UserType Teacher::getUserType() const
{
	return UserType::Teacher;
}
User* Teacher::clone() const
{
	return new Teacher(*this);
}
void Teacher::writeToBinaryFile(std::ofstream& ofs) const
{
	UserType type = UserType::Teacher;
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
void Teacher::printUser() const
{
	std::cout << name << " " << surname << " | Teacher | " << id << std::endl;
}
