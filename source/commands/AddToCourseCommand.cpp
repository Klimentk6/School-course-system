#include "AddToCourseCommand.h"

AddToCourseCommand::AddToCourseCommand(const char* buffer, Context& ctx)
    : buffer(buffer), ctx(ctx) {}

void AddToCourseCommand::execute()
{
    char* courseName = getCourseNameFromBuffer(buffer);
    int studentId = getStudentIdFromBuffer(buffer);
    Course* coursePtr = ctx.collection.getCoursePointer(courseName);
    if (coursePtr == nullptr)
    {
        std::cout << "Invalid course name" << std::endl;
    }
    else if (coursePtr->isStudentIdInCourse(studentId))
    {
        std::cout << "This user is already enrolled in the course." << std::endl;
    }
    else if (!ctx.container.isUserInTheContainer(studentId) || ctx.container.getUserPointer(studentId)->getUserType() != UserType::Student)
    {
        std::cout << "Invalid user id" << std::endl;
    }
    else
    {
        coursePtr->addStudentId(studentId);
        std::cout << "User was successfully added to the course!" << std::endl;
    }
    delete[] courseName;
}

char* AddToCourseCommand::getCourseNameFromBuffer(const char* buffer) const
{
    const char* prefix = "add_to_course ";
    buffer += stringLength(prefix);
    int len = 0;
    while (buffer[len] && buffer[len] != ' ')
    {
        len++;
    }
    char* result = new char[len + 1];
    for (int i = 0; i < len; i++)
    {
        result[i] = buffer[i];
    }
    result[len] = '\0';
    return result;
}
int AddToCourseCommand::getStudentIdFromBuffer(const char* buffer) const
{
    const char* prefix = "add_to_course ";
    buffer += stringLength(prefix);
    while (*buffer && *buffer != ' ')
    {
        buffer++;
    }

    if (*buffer == ' ')
    {
        buffer++;
    }
    int result = 0;
    while (*buffer)
    {
        result *= 10;
        result += *buffer - '0';
        buffer++;
    }
    return result;
}
