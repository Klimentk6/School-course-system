#include "LogoutCommand.h"

LogoutCommand::LogoutCommand(const char* buffer, Context& ctx)
    : buffer(buffer), ctx(ctx) {}

void LogoutCommand::execute()
{
    ctx.logged = UserType::None;
    ctx.loggedId = -1;
    std::cout << std::endl << std::endl;
}