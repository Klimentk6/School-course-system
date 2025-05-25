#include "MailBoxCommand.h"

MailBoxCommand::MailBoxCommand(const char* buffer, Context& ctx)
	: buffer(buffer), ctx(ctx) {}

void MailBoxCommand::execute()
{
	ctx.container.getUserPointer(ctx.loggedId)->printInbox();
}
