#include "MessageStudentsCommand.h"

MessageStudentsCommand::MessageStudentsCommand(const char* buffer, Context& ctx)
    : buffer(buffer), ctx(ctx) {}

void MessageStudentsCommand::execute()
{
    char* courseName = getCourseNameFromBuffer(buffer);
    char* content = getMessageContentFromBuffer(buffer);

    Course* currentCourse = ctx.collection.getCoursePointer(courseName);
    if (currentCourse != nullptr)
    {
        if (currentCourse->getTeacherId() == ctx.loggedId)
        {
            Message newMessage(ctx.loggedId, content, time(nullptr));
            int size = ctx.container.getSize();

            for (int i = 0; i < size; i++)
            {
                User* user = ctx.container.getUserPointer(i);
                if (user != nullptr)
                {
                    int userId = user->getId();
                    if (currentCourse->isStudentIdInCourse(userId))
                    {
                        user->addMessage(newMessage);
                    }
                }
            }
            std::cout << "Message was sent successfuly!" << std::endl;
        }
        else
        {
            std::cout << "You are not the teacher for this course." << std::endl;
        }
    }
    else
    {
        std::cout << "Invalid course name" << std::endl;
    }

    delete[] courseName;
    delete[] content;

}

char* MessageStudentsCommand::getCourseNameFromBuffer(const char* buffer) const
{
    const char* prefix = "message_students ";
    buffer += stringLength(prefix);

    int nameLen = 0;
    while (buffer[nameLen] != ' ' && buffer[nameLen] != '\0')
    {
        nameLen++;
    }

    char* courseName = new char[nameLen + 1];
    for (int i = 0; i < nameLen; i++)
    {
        courseName[i] = buffer[i];
    }
    courseName[nameLen] = '\0';

    return courseName;
}
char* MessageStudentsCommand::getMessageContentFromBuffer(const char* buffer) const
{
    const char* prefix = "message_students ";
    buffer += stringLength(prefix);

    // Прескачаме courseName
    while (*buffer != ' ' && *buffer != '\0')
    {
        buffer++;
    }

    if (*buffer == ' ')
        buffer++;  // преминаваме към съдържанието

    // Сега buffer сочи към content
    int contentLen = stringLength(buffer);
    char* content = new char[contentLen + 1];
    for (int i = 0; i < contentLen; i++)
    {
        content[i] = buffer[i];
    }
    content[contentLen] = '\0';

    return content;
}
