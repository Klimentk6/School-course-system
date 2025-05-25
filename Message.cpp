#include "Message.h"

Message::Message()
{
	senderId = -1;
	content = nullptr;
	timeSent = 0;
}
Message::Message(int senderId, const char* content, std::time_t timeSent)
{
	this->senderId = senderId;
	this->content = new char[stringLength(content) + 1];
	stringCopy(this->content, content);
	this->timeSent = timeSent;
}
Message::Message(const Message& other)
{
	copyFrom(other);
}
Message& Message::operator=(const Message& other)
{
	if (this != &other)
	{ 
		free();
		copyFrom(other);
	}
	return *this;
}
Message::~Message()
{
	free();
}

void Message::copyFrom(const Message& other)
{
	senderId = other.senderId;
	content = new char[stringLength(other.content) + 1];
	stringCopy(content, other.content);
	timeSent = other.timeSent;
}
void Message::free()
{
	delete[] content;
}

void Message::readFromBinaryFile(std::ifstream& ifs)
{
	free();

	ifs.read((char*)&senderId, sizeof(senderId));

	unsigned contentLength = 0;
	ifs.read((char*)&contentLength, sizeof(contentLength));
	content = new char[contentLength + 1];
	ifs.read(content, contentLength);
	content[contentLength] = '\0';

	ifs.read((char*)&timeSent, sizeof(timeSent));
}
void Message::writeToBinaryFile(std::ofstream& ofs) const
{
	ofs.write((const char*)&senderId, sizeof(senderId));

	unsigned contentLength = stringLength(content);
	ofs.write((const char*)&contentLength, sizeof(contentLength));
	ofs.write((const char*)content, contentLength);

	ofs.write((const char*)&timeSent, sizeof(timeSent));
}

void Message::printMessage() const
{
	std::tm timeInfo;
	localtime_s(&timeInfo, &timeSent); 
	std::cout << "   " << std::put_time(&timeInfo, "%H:%M %d.%m.%Y") << std::endl;
	std::cout << "   Sent by ID " << senderId << std::endl;
	std::cout << "   " << content << std::endl;
}




