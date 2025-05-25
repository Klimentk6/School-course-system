#include "UserContainer.h"

UserContainer::UserContainer()
{
	size = 0;
	capacity = MIN_CONTAINER_CAPACITY;
	arr = new User * [capacity];
}
UserContainer::UserContainer(const User* arr, int size)
{
	this->size = size;
	this->capacity = calculateCapacity(size);
	this->arr = new User*[capacity];
	for (int i = 0; i < size; i++)
	{
		this->arr[i] = arr[i].clone();
	}
}
UserContainer::UserContainer(const char* fileName)
{
	try
	{
		readFromBinaryFile(fileName);
	}
	catch (std::exception)
	{
		size = 0;
		capacity = MIN_CONTAINER_CAPACITY;
		arr = new User * [capacity];
		addAdministrator(DEFAULT_ADMINISTRATOR_NAME, DEFAULT_ADMINISTRATOR_SURNAME, DEFAULT_ADMINISTRATOR_PASSWORD);
	}
}
UserContainer::UserContainer(const UserContainer& other)
{
	copyFrom(other);
}
UserContainer& UserContainer::operator=(const UserContainer& other)
{
	if (this != &other)
	{
		free();
		copyFrom(other);
	}
	return *this;
}
UserContainer::~UserContainer()
{
	free();
}

void UserContainer::copyFrom(const UserContainer& other)
{
	size = other.size;
	capacity = other.capacity;
	arr = new User*[capacity];
	for (int i = 0; i < size; i++)
	{
		arr[i] = other.arr[i]->clone();
	}
}
void UserContainer::free()
{
	for (int i = 0; i < size; i++)
	{
		delete arr[i];
	}
	delete[] arr;
}

int UserContainer::getSize() const
{
	return size;
}
User* UserContainer::getUserPointer(int index) const
{
	return arr[index];
}
bool UserContainer::isUserInTheContainer(int userId) const
{
	for (int i = 0; i < size; i++)
	{
		if (arr[i]->getId() == userId)
		{
			return true;
		}
	}
	return false;
}

void UserContainer::readFromBinaryFile(const char* fileName)
{
	std::ifstream ifs(fileName, std::ios::binary);
	if (!ifs.is_open())
	{
		throw std::runtime_error("Could not open file for reading");
	}

	free();

	ifs.read((char*)&size, sizeof(size));
	capacity = calculateCapacity(size);
	arr = new User * [capacity];

	for (int i = 0; i < size; i++)
	{
		bool isUserNullptr = false;
		ifs.read((char*)&isUserNullptr, sizeof(isUserNullptr)); 

		if (!isUserNullptr)
		{
			arr[i] = nullptr;
			continue;
		}
		else
		{
			UserType type;
			ifs.read((char*)&type, sizeof(type));

			arr[i] = UserFactory::create(type);
			arr[i]->readFromBinaryFile(ifs);
		}
	}

	ifs.close();
}
void UserContainer::writeToBinaryFile(const char* fileName) const
{
	std::ofstream ofs(fileName, std::ios::binary);
	if (!ofs.is_open())
	{
		throw std::runtime_error("Could not open file for writing");
	}

	ofs.write((const char*)&size, sizeof(size));

	for (int i = 0; i < size; i++)
	{
		bool isUserNullptr = (arr[i] != nullptr);
		ofs.write((const char*)&isUserNullptr, sizeof(isUserNullptr));
		if (isUserNullptr)
		{
			arr[i]->writeToBinaryFile(ofs); 
		}
	}

	ofs.close();
}

void UserContainer::resize(int newCapacity)
{
	capacity = newCapacity;
	User** temp = new User * [capacity];
	for (int i = 0; i < size; i++) 
	{
		temp[i] = arr[i];
	}
	delete[] arr;
	arr = temp;
}
int UserContainer::calculateCapacity(int size) const
{
	int result = MIN_CONTAINER_CAPACITY;
	while (result < size)
	{
		result *= RESIZE_COEFF;
	}
	return result;
}

void UserContainer::addAdministrator(const char* name, const char* surname, const char* password)
{
	if (size == capacity)
	{
		resize(capacity * RESIZE_COEFF);
	}
	arr[size] = UserFactory::createWithParameters(UserType::Administrator, name, surname, size, password);
	size++;
}
void UserContainer::addTeacher(const char* name, const char* surname, const char* password)
{
	if (size == capacity)
	{
		resize(capacity * RESIZE_COEFF);
	}
	arr[size] = UserFactory::createWithParameters(UserType::Teacher, name, surname, size, password);
	size++;
}
void UserContainer::addStudent(const char* name, const char* surname, const char* password)
{
	if (size == capacity)
	{
		resize(capacity * RESIZE_COEFF);
	}
	arr[size] = UserFactory::createWithParameters(UserType::Student, name, surname, size, password);
	size++;
}
void UserContainer::removeUser(int id)
{
	delete arr[id];
	arr[id] = nullptr;
}
void UserContainer::messageAll(int senderId, const char* content)
{
	Message newMessage(senderId, content, time(nullptr));
	for (int i = 1; i < size; i++)
	{
		if (arr[i] != nullptr)
		{
			arr[i]->addMessage(newMessage);
		}
	}
}