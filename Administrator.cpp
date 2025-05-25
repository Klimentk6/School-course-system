#include "Administrator.h"

Administrator::Administrator(const char* name, const char* surname, int id, const Mail& inbox, const char* password)
	: User(name, surname, id, inbox, password) {}
Administrator::Administrator(const char* name, const char* surname, int id, const char* password)
	: User(name, surname, id, password) {}

UserType Administrator::getUserType() const
{
	return UserType::Administrator;
}
User* Administrator::clone() const 
{
	return new Administrator(*this);
}
void Administrator::writeToBinaryFile(std::ofstream& ofs) const
{
	UserType type = UserType::Administrator;
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
void Administrator::printUser() const
{
	std::cout << name << ' ' << surname << " | Administrator | " << id << std::endl;
}