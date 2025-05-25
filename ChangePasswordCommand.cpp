#include "ChangePasswordCommand.h"

ChangePasswordCommand::ChangePasswordCommand(const char* buffer, Context& ctx)
	: buffer(buffer), ctx(ctx) {}

void ChangePasswordCommand::execute()
{
	char* oldPassword = getOldPasswordFromBuffer(buffer);
	if (ctx.container.getUserPointer(ctx.loggedId)->isPasswordCorrect(oldPassword))
	{
		char* newPassword = getNewPasswordFromBuffer(buffer);
		ctx.container.getUserPointer(ctx.loggedId)->changePassword(newPassword);
		std::cout << "Password changed successfully!" << std::endl;
		delete[] newPassword;
	}
	else
	{
		std::cout << "Incorect password" << std::endl;
	}
	delete[] oldPassword;
}

char* ChangePasswordCommand::getOldPasswordFromBuffer(const char* buffer) const
{
	const char* prefix = "change_password ";
	buffer += stringLength(prefix);
	int length = 0;
	while (buffer[length] && buffer[length] != ' ')
	{
		length++;
	}
	char* oldPassword = new char[length + 1];
	for (int i = 0; i < length; i++)
	{
		oldPassword[i] = buffer[i];
	}
	oldPassword[length] = '\0';
	return oldPassword;
}
char* ChangePasswordCommand::getNewPasswordFromBuffer(const char* buffer) const
{
	const char* prefix = "change_password ";
	buffer += stringLength(prefix);

	while (*buffer && *buffer != ' ')
		buffer++;
	if (*buffer == ' ') buffer++;

	int length = 0;
	while (buffer[length] && buffer[length] != ' ')
		length++;

	char* newPassword = new char[length + 1];
	for (int i = 0; i < length; ++i)
		newPassword[i] = buffer[i];
	newPassword[length] = '\0';

	return newPassword;
}

