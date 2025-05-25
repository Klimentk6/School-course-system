#include "MessageAllCommand.h"

MessageAllCommand::MessageAllCommand(const char* buffer, Context& ctx)
	: buffer(buffer), ctx(ctx) {}

void MessageAllCommand::execute()
{
	char* content = getMessageContent(buffer);
	ctx.container.messageAll(ctx.loggedId, content);
	std::cout << "Message was sent successfuly!" << std::endl;
	delete[] content;
}

char* MessageAllCommand::getMessageContent(const char* buffer) const
{
	const char* prefix = "message_all ";
	buffer += stringLength(prefix);
	unsigned length = stringLength(buffer);
	char* result = new char[length + 1];
	for (unsigned i = 0; i <= length; ++i)
	{
		result[i] = buffer[i];
	}
	return result;
}
