#include "Mail.h"

Mail::Mail()
{
	size = 0;
	capacity = MIN_MAIL_CAPACITY;
	arr = new Message[capacity];
}
Mail::Mail(const Message* arr, int size)
{
	this->size = size;
	this->capacity = calculateCapacity(size);
	this->arr = new Message[capacity];
	for (int i = 0; i < size; i++)
	{
		this->arr[i] = arr[i];
	}
}
Mail::Mail(const Mail& other)
{
	copyFrom(other);
}
Mail& Mail::operator=(const Mail& other)
{
	if (this != &other)
	{
		free();
		copyFrom(other);
	}
	return *this;
}
Mail::~Mail()
{
	free();
}

void Mail::copyFrom(const Mail& other)
{
	size = other.size;
	capacity = other.capacity;
	arr = new Message[capacity];
	for (int i = 0; i < size; i++)
	{
		arr[i] = other.arr[i];
	}
}
void Mail::free()
{
	delete[] arr;
}

void Mail::readFromBinaryFile(std::ifstream& ifs)
{
	free();

	ifs.read((char*)&size, sizeof(size));
	capacity = calculateCapacity(size);

	arr = new Message[capacity];
	for (int i = 0; i < size; i++) 
	{
		arr[i].readFromBinaryFile(ifs);
	}
}
void Mail::writeToBinaryFile(std::ofstream& ofs) const
{
	ofs.write((const char*)&size, sizeof(size));
	for (int i = 0; i < size; i++) 
	{
		arr[i].writeToBinaryFile(ofs);
	}
}

void Mail::addNewMessage(const Message& newMessage)
{
	if (size == capacity)
	{
		resize(capacity * RESIZE_COEFF);
	}
	arr[size] = newMessage;
	size++;
}

int Mail::calculateCapacity(int size)
{
	int result = MIN_MAIL_CAPACITY;
	while (result < size)
	{
		result *= RESIZE_COEFF;
	}
	return result;
}
void Mail::resize(int newCapacity)
{
	capacity = newCapacity;
	Message* temp = new Message[capacity];
	for (int i = 0; i < size; i++)
	{
		temp[i] = arr[i];
	}
	free();
	arr = temp;
}

void Mail::printMail() const
{
	if (size == 0)
	{
		std::cout << "No messages to show" << std::endl;
	}
	for (int i = 0; i < size; i++)
	{
		arr[i].printMessage();
	}
}
void Mail::clear()
{
	free();
	size = 0;
	capacity = MIN_MAIL_CAPACITY;
	arr = new Message[capacity];
}