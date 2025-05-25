#include "CreateCourseCommand.h"

CreateCourseCommand::CreateCourseCommand(const char* buffer, Context& ctx)
	: buffer(buffer), ctx(ctx) {}

void CreateCourseCommand::execute()
{
	char* name = getNameFromBuffer(buffer);
	char* password = getPasswordFromBuffer(buffer);
	Course newCourse(name, password, ctx.loggedId);
	ctx.collection.addCourse(newCourse);
	std::cout << "Course was succesfuly created!" << std::endl;
	delete[] name;
	delete[] password;
}

char* CreateCourseCommand::getNameFromBuffer(const char* buffer) const
{
	const char* prefix = "create_course ";
	buffer += stringLength(prefix);
	int nameLen = 0;
	while (buffer[nameLen] != ' ')
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
char* CreateCourseCommand::getPasswordFromBuffer(const char* buffer) const
{
	const char* prefix = "create_course ";
	buffer += stringLength(prefix);
	while (*buffer != ' ')
	{
		buffer++;
	}
	buffer++; 
	int passLen = 0;
	while (buffer[passLen] != '\0')
	{
		passLen++;
	}
	char* password = new char[passLen + 1];
	for (int i = 0; i < passLen; i++)
	{
		password[i] = buffer[i];
	}
	password[passLen] = '\0';
	return password;
}

