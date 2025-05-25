#include "ViewAssignmentSubmissionsCommand.h"

ViewAssignmentSubmissionsCommand::ViewAssignmentSubmissionsCommand(const char* buffer, Context& ctx)
    : buffer(buffer), ctx(ctx) {}

void ViewAssignmentSubmissionsCommand::execute()
{
    char* courseName = getCourseFromBuffer(buffer);
    char* assignmentName = getAssignmentFromBuffer(buffer);
    Course* course = ctx.collection.getCoursePointer(courseName);
    if (course != nullptr)
    {
        if (course->getTeacherId() == ctx.loggedId)
        {
            Assignment* assignment = course->getAssignmentPointer(assignmentName);
            if (assignment != nullptr)
            {
                assignment->printSubmissions();
            }
            else
            {
                std::cout << "Invalid assignment name" << std::endl;
            }
        }
        else
        {
            std::cout << "You are not the teacher of this course" << std::endl;
        }
    }
    else
    {
        std::cout << "Invalid course name" << std::endl;
    }
    delete[] courseName;
    delete[] assignmentName;
}

char* ViewAssignmentSubmissionsCommand::getCourseFromBuffer(const char* buffer) const
{
    const char* prefix = "view_assignment_submissions ";
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
char* ViewAssignmentSubmissionsCommand::getAssignmentFromBuffer(const char* buffer) const
{
    const char* prefix = "view_assignment_submissions ";
    buffer += stringLength(prefix);

    
    while (*buffer && *buffer != ' ')
    {
        buffer++;
    }
    if (*buffer == '\0') return nullptr;
    buffer++;

    int len = stringLength(buffer);
    char* result = new char[len + 1];
    stringCopy(result, buffer);
    return result;
}

