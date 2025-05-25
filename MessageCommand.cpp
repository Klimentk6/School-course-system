#include "MessageCommand.h"

MessageCommand::MessageCommand(const char* buffer, Context& ctx)
    : buffer(buffer), ctx(ctx) {}

void MessageCommand::execute()
{
    int id = getIdFromBuffer(buffer);
    char* content = getContentFromBuffer(buffer);
    if (id >= ctx.container.getSize() || ctx.container.getUserPointer(id) == nullptr)
    {
        std::cout << "Invalid id" << std::endl;
    }
    else
    {
        Message newMessage(ctx.loggedId, content, time(nullptr));
        ctx.container.getUserPointer(id)->addMessage(newMessage);
        std::cout << "Message succesfuly sent!" << std::endl;
    }
    delete[] content;
}

int MessageCommand::getIdFromBuffer(const char* buffer) const
{
    const char* prefix = "message ";
    if (!isPrefix(prefix, buffer))
        return -1;

    buffer += stringLength(prefix);
    int id = 0;
    while (*buffer && *buffer != ' ')
    {
        if (!isCharDigit(*buffer))
            return -1;
        id = id * 10 + (*buffer - '0');
        ++buffer;
    }
    return id;
}
char* MessageCommand::getContentFromBuffer(const char* buffer) const
{
    const char* prefix = "message ";
    buffer += stringLength(prefix);
    while (*buffer && *buffer != ' ')
    {
        ++buffer;
    }

    if (*buffer == '\0') return nullptr;
    ++buffer;

    int len = stringLength(buffer);
    char* content = new char[len + 1];
    stringCopy(content, buffer);
    return content;
}
