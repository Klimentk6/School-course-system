#include "Utils.h"
#include "User.h"

using namespace Utils;

User::User() : inbox()
{
	name = nullptr;
	surname = nullptr;
	id = -1;
	password = nullptr;
}
User::User(const char* name, const char* surname, int id, const Mail& inbox, const char* password) : inbox(inbox)
{
	this->name = new char[stringLength(name) + 1];
	stringCopy(this->name, name);

	this->surname = new char[stringLength(surname) + 1];
	stringCopy(this->surname, surname);

	this->id = id;

	this->password = new char[stringLength(password) + 1];
	stringCopy(this->password, password);
}
User::User(const char* name, const char* surname, int id, const char* password) : inbox()
{
	this->name = new char[stringLength(name) + 1];
	stringCopy(this->name, name);

	this->surname = new char[stringLength(surname) + 1];
	stringCopy(this->surname, surname);

	this->id = id;

	this->password = new char[stringLength(password) + 1];
	stringCopy(this->password, password);
}
User::User(const User& other)
{
	copyFrom(other);
}
User& User::operator=(const User& other)
{
	if (this != &other)
	{
		free();
		copyFrom(other);
	}
	return *this;
}
User::~User()
{
	free();
}

void User::copyFrom(const User& other)
{
	name = new char[stringLength(other.name) + 1];
	stringCopy(name, other.name);

	surname = new char[stringLength(other.surname) + 1];
	stringCopy(surname, other.surname);

	id = other.id;

	inbox = other.inbox;

	password = new char[stringLength(other.password) + 1];
	stringCopy(password, other.password);
}
void User::free()
{
	delete[] name;
	delete[] surname;
	delete[] password;
}

int User::getId() const
{
	return id;
}
void User::readFromBinaryFile(std::ifstream& ifs)
{
	free();

	unsigned nameLength = 0;
	ifs.read((char*)&nameLength, sizeof(nameLength));
	name = new char[nameLength + 1];
	ifs.read((char*)name, nameLength);
	name[nameLength] = '\0';

	unsigned surnameLength = 0;
	ifs.read((char*)&surnameLength, sizeof(surnameLength));
	surname = new char[surnameLength + 1];
	ifs.read((char*)surname, surnameLength);
	surname[surnameLength] = '\0';

	ifs.read((char*)&id, sizeof(id));

	inbox.readFromBinaryFile(ifs);

	unsigned passwordLength = 0;
	ifs.read((char*)&passwordLength, sizeof(passwordLength));
	password = new char[passwordLength + 1];
	ifs.read((char*)password, passwordLength);
	password[passwordLength] = '\0';

}
bool User::isPasswordCorrect(const char* checkPassword) const
{
	return areStringsEqual(checkPassword, password);
}
void User::changePassword(const char* newPassword)
{
	delete[] password;
	password = new char[stringLength(newPassword) + 1];
	stringCopy(password, newPassword);
}
void User::addMessage(const Message& newMessage)
{
	inbox.addNewMessage(newMessage);
}
void User::printInbox() const
{
	inbox.printMail();
}

void User::clearMailbox()
{
	inbox.clear();
}
