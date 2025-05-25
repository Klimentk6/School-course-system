#include "AddTeacherCommand.h"

AddTeacherCommand::AddTeacherCommand(const char* buffer, Context& ctx)
    : buffer(buffer), ctx(ctx) {}

void AddTeacherCommand::execute()
{
    const char* name = getNameFromBuffer(buffer);
    const char* surname = getSurnameFromBuffer(buffer);
    const char* password = getPasswordFromBuffer(buffer);
    ctx.container.addTeacher(name, surname, password);
	std::cout << "Added teacher " << name << ' ' << surname << " with ID " << ctx.container.getSize() - 1 << "!" << std::endl;
    delete[] name;
    delete[] surname;
    delete[] password;
}

char* AddTeacherCommand::getNameFromBuffer(const char* buffer) const
{
	buffer += stringLength("add_teacher ");
	const char* start = buffer;
	while (*buffer && *buffer != ' ')
	{
		++buffer;
	}
	int len = buffer - start;
	char* name = new char[len + 1];
	for (int i = 0; i < len; ++i)
	{
		name[i] = start[i];
	}
	name[len] = '\0';
	return name;
}
char* AddTeacherCommand::getSurnameFromBuffer(const char* buffer) const
{
	buffer += stringLength("add_teacher ");
	while (*buffer && *buffer != ' ')
	{
		++buffer;
	}
	++buffer;
	const char* start = buffer;
	while (*buffer && *buffer != ' ')
	{
		++buffer;
	}
	int len = buffer - start;
	char* surname = new char[len + 1];
	for (int i = 0; i < len; ++i)
	{
		surname[i] = start[i];
	}
	surname[len] = '\0';
	return surname;
}
char* AddTeacherCommand::getPasswordFromBuffer(const char* buffer) const
{
	buffer += stringLength("add_teacher ");
	while (*buffer && *buffer != ' ')
	{
		++buffer;
	}
	++buffer;
	while (*buffer && *buffer != ' ')
	{
		++buffer;
	}
	++buffer;
	const char* start = buffer;
	int len = 0;
	while (buffer[len])
	{
		++len;
	}
	char* password = new char[len + 1];
	for (int i = 0; i < len; ++i)
	{
		password[i] = start[i];
	}
	password[len] = '\0';
	return password;
}
