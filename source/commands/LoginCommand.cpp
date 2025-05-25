#include "LoginCommand.h"

LoginCommand::LoginCommand(const char* buffer, Context& ctx)
    : buffer(buffer), ctx(ctx) {}

void LoginCommand::execute()
{
    int id = getIdFromBuffer(buffer);
    char* password = getPasswordFromBuffer(buffer);

    if (ctx.container.getSize() > id && ctx.container.getUserPointer(id) != nullptr && ctx.container.getUserPointer(id)->isPasswordCorrect(password))
    {
        ctx.logged = ctx.container.getUserPointer(id)->getUserType();
        ctx.loggedId = id;
        std::cout << "Login successful!" << std::endl;
		ctx.container.getUserPointer(id)->printUser();
    }
    else
    {
        std::cout << "Invalid id or password" << std::endl;
    }
    delete[] password;
}

int LoginCommand::getIdFromBuffer(const char* buffer) const
{
	int result = 0;
	buffer += stringLength("login ");
	while (isCharDigit(*buffer))
	{
		result *= 10;
		result += convertCharToInt(*buffer);
		buffer++;
	}
	return result;
}
char* LoginCommand::getPasswordFromBuffer(const char* buffer) const
{
	buffer += stringLength("login ");
	while (isCharDigit(*buffer))
	{
		++buffer;
	}
	if (*buffer == ' ')
	{
		++buffer;
	}
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
