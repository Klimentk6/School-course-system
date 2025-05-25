#include "RemoveUserCommand.h"

RemoveUserCommand::RemoveUserCommand(const char* buffer, Context& ctx)
    : buffer(buffer), ctx(ctx) {}

void RemoveUserCommand::execute()
{
    int id = getIdFromBuffer(buffer);
    if (ctx.container.getSize() <= id || ctx.container.getUserPointer(id) == nullptr)
    {
        std::cout << "User does not exist" << std::endl;
    }
    else if (id == ctx.loggedId)
    {
        std::cout << "Cannot remove the administrator" << std::endl;
    }
    else
    {
        ctx.container.removeUser(id);
        std::cout << "Removed user with ID " << id << std::endl;
    }
}

int RemoveUserCommand::getIdFromBuffer(const char* buffer) const
{
    int result = 0;
    buffer += stringLength("remove_user ");
    while (*buffer)
    {
        result *= 10;
        result += convertCharToInt(*buffer);
        ++buffer; 
    }
    return result;
}