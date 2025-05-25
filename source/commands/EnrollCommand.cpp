#include "EnrollCommand.h"

EnrollCommand::EnrollCommand(const char* buffer, Context& ctx)
	: buffer(buffer), ctx(ctx) {}

void EnrollCommand::execute()
{
	char* name = getNameFromBuffer(buffer);
	char* password = getPasswordFromBuffer(buffer);
	Course* currentCourse = ctx.collection.getCoursePointer(name);
	if (currentCourse != nullptr)
	{
		if (currentCourse->isPasswordCorrect(password))
		{
			if (!currentCourse->isStudentIdInCourse(ctx.loggedId))
			{
				currentCourse->addStudentId(ctx.loggedId);
				std::cout << "Successfully enrolled in the course!" << std::endl;
			}
			else
			{
				std::cout << "You are already in this course" << std::endl;
			}
		}
		else
		{
			std::cout << "Incorrect password" << std::endl;
		}
	}
	else
	{
		std::cout << "Invalid course name" << std::endl;
	}
	delete[] name;
	delete[] password;
}

char* EnrollCommand::getNameFromBuffer(const char* buffer) const
{
	const char* prefix = "enroll ";
	buffer += stringLength(prefix);
	int nameLen = 0;
	while (buffer[nameLen] != '\0' && buffer[nameLen] != ' ')
	{
		nameLen++;
	}
	char* name = new char[nameLen + 1];
	for (int i = 0; i < nameLen; i++)
	{
		name[i] = buffer[i];
	}
	name[nameLen] = '\0';
	return name;
}
char* EnrollCommand::getPasswordFromBuffer(const char* buffer) const
{
	const char* prefix = "enroll ";
	buffer += stringLength(prefix);
	while (*buffer && *buffer != ' ')
	{
		buffer++;
	}
	if (*buffer == ' ')
	{
		buffer++;
	}
	int len = stringLength(buffer);
	char* password = new char[len + 1];
	stringCopy(password, buffer);
	return password;
}

