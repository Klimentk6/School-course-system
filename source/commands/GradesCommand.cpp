#include "GradesCommand.h"

GradesCommand::GradesCommand(const char* buffer, Context& ctx)
    : buffer(buffer), ctx(ctx) {}

void GradesCommand::execute()
{
    bool hasGrades = false;
    int coursesCount = ctx.collection.getSize();
    for (int i = 0; i < coursesCount; i++)
    {
        Course* course = ctx.collection.getCourseFromArr(i);
        if (course->isStudentIdInCourse(ctx.loggedId))
        {
            int assignmentCount = course->getAssignmentSize();
            for (int j = 0; j < assignmentCount; j++)
            {
                Assignment* assignment = course->getAssignmentFromArr(j);
                if (assignment->hasAStudentSubmited(ctx.loggedId))
                {
                    Submission* submission = assignment->getSubmissionPointer(ctx.loggedId);
                    if (submission->getGrade() > 0)
                    {
                        hasGrades = true;
                        std::cout << course->getName() << " | " << assignment->getName() << " | " << submission->getGrade() << std::endl;
                    }
                }
            }
        }
    }
    if (!hasGrades)
    {
        std::cout << "You have no graded submissions." << std::endl;
    }
}
