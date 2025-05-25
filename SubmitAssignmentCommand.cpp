#include "SubmitAssignmentCommand.h"

SubmitAssignmentCommand::SubmitAssignmentCommand(const char* buffer, Context& ctx)
    : buffer(buffer), ctx(ctx) {}

void SubmitAssignmentCommand::execute()
{
    char* courseName = getCourseFromBuffer(buffer);
    char* assignmentName = getAssignmentFromBuffer(buffer);
    char* content = getContentFromBuffer(buffer);
    Course* course = ctx.collection.getCoursePointer(courseName);
    if (course != nullptr)
    {
        if (course->isStudentIdInCourse(ctx.loggedId))
        {
            Assignment* assignment = course->getAssignmentPointer(assignmentName);
            if (assignment != nullptr)
            {
                if (!assignment->hasAStudentSubmited(ctx.loggedId))
                {
                    Submission newSubmission(ctx.loggedId, content);
                    assignment->addSubmission(newSubmission);
                    std::cout << "You have successfully added a new submission!" << std::endl;
                }
                else
                {
                    std::cout << "You have already submited" << std::endl;
                }
            }
            else
            {
                std::cout << "Invalid assignment name" << std::endl;
            }
        }
        else
        {
            std::cout << "You are not in this course" << std::endl;
        }
    }
    else
    {
        std::cout << "Invalid course name" << std::endl;
    }
    delete[] courseName;
    delete[] assignmentName;
    delete[] content;
}

char* SubmitAssignmentCommand::getCourseFromBuffer(const char* buffer) const
{
    const char* prefix = "submit_assignment ";
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
char* SubmitAssignmentCommand::getAssignmentFromBuffer(const char* buffer) const
{
    const char* prefix = "submit_assignment ";
    buffer += stringLength(prefix);

    // Пропусни <course>
    while (*buffer && *buffer != ' ')
    {
        buffer++;
    }
    buffer++; // прескочи интервала

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
char* SubmitAssignmentCommand::getContentFromBuffer(const char* buffer) const
{
    const char* prefix = "submit_assignment ";
    buffer += stringLength(prefix);

    // Пропусни <course>
    while (*buffer && *buffer != ' ')
    {
        buffer++;
    }
    buffer++; // интервал

    // Пропусни <assignment>
    while (*buffer && *buffer != ' ')
    {
        buffer++;
    }
    buffer++; // интервал

    // Копирай останалото
    int len = stringLength(buffer);
    char* result = new char[len + 1];
    stringCopy(result, buffer);
    return result;
}

