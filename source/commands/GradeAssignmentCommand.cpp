#include "GradeAssignmentCommand.h"

GradeAssignmentCommand::GradeAssignmentCommand(const char* buffer, Context& ctx)
	: buffer(buffer), ctx(ctx) {}

void GradeAssignmentCommand::execute()
{
    char* courseName = getCourseFromBuffer(buffer);
    char* assignmentName = getAssignmentFromBuffer(buffer);
    int studentId = getStudentIdFromBuffer(buffer);
    double grade = getGradeFromBuffer(buffer);
    Course* course = ctx.collection.getCoursePointer(courseName);
    if (course != nullptr)
    {
        if (course->getTeacherId() == ctx.loggedId)
        {
            Assignment* assignment = course->getAssignmentPointer(assignmentName);
            if (assignment != nullptr)
            {
                if (assignment->hasAStudentSubmited(studentId))
                {
                    assignment->getSubmissionPointer(studentId)->setGrade(grade);
                    std::cout << "You have succesfuly graded the submission" << std::endl;
                }
                else
                {
                    std::cout << "This student has not submitted the assignment" << std::endl;
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
}

char* GradeAssignmentCommand::getCourseFromBuffer(const char* buffer) const
{
    const char* prefix = "grade_assignment ";
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
char* GradeAssignmentCommand::getAssignmentFromBuffer(const char* buffer) const
{
    const char* prefix = "grade_assignment ";
    buffer += stringLength(prefix);

    while (*buffer && *buffer != ' ') buffer++;
    buffer++; 

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
int GradeAssignmentCommand::getStudentIdFromBuffer(const char* buffer) const
{
    const char* prefix = "grade_assignment ";
    buffer += stringLength(prefix);

    while (*buffer && *buffer != ' ') buffer++;
    buffer++;

    while (*buffer && *buffer != ' ') buffer++;
    buffer++;

    return stringToInt(buffer);
}
double GradeAssignmentCommand::getGradeFromBuffer(const char* buffer) const
{
    const char* prefix = "grade_assignment ";
    buffer += stringLength(prefix);

    while (*buffer && *buffer != ' ') buffer++;
    buffer++;

    while (*buffer && *buffer != ' ') buffer++;
    buffer++;

    while (*buffer && *buffer != ' ') buffer++;
    buffer++;

    return stringToDouble(buffer);
}

