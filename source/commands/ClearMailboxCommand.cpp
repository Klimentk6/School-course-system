#include "ClearMailboxCommand.h"

ClearMailboxCommand::ClearMailboxCommand(const char* buffer, Context& ctx)
	: buffer(buffer), ctx(ctx) {}

void ClearMailboxCommand::execute()
{
	ctx.container.getUserPointer(ctx.loggedId)->clearMailbox();
	std::cout << "Mailbox cleared successfully!" << std::endl;
}
