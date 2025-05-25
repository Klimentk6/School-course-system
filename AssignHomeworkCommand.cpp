#include "AssignHomeworkCommand.h"

AssignHomeworkCommand::AssignHomeworkCommand(const char* buffer, Context& ctx)
	: buffer(buffer), ctx(ctx) {}

void AssignHomeworkCommand::execute()
{
	char* courseName = getCourseNameFromBuffer(buffer);
	char* assignmentName = getAssignmentNameFromBuffer(buffer);
	Course* currentCourse = ctx.collection.getCoursePointer(courseName);
	if (currentCourse != nullptr)
	{
		if (currentCourse->getTeacherId() == ctx.loggedId)
		{
			Assignment assignmentToAdd(assignmentName);
			currentCourse->addAssignment(assignmentToAdd);
			std::cout << "Successfully created a new assignment!" << std::endl;
		}
		else
		{
			std::cout << "You are not the teacher for this course" << std::endl;
		}
	}
	else
	{
		std::cout << "Invalid course name" << std::endl;
	}
	delete[] courseName;
	delete[] assignmentName;
}

char* AssignHomeworkCommand::getCourseNameFromBuffer(const char* buffer) const
{
	const char* prefix = "assign_homework ";
	buffer += stringLength(prefix);

	int nameLen = 0;
	while (buffer[nameLen] != ' ' && buffer[nameLen] != '\0')
	{
		nameLen++;
	}

	char* name = new char[nameLen + 1];
	for (int i = 0; i < nameLen; i++)
	{
		name[i] = buffer[i];
	}
	name[nameLen] = '\0';

	return name;
}
char* AssignHomeworkCommand::getAssignmentNameFromBuffer(const char* buffer) const
{
	const char* prefix = "assign_homework ";
	buffer += stringLength(prefix);
	int i = 0;
	while (buffer[i] != ' ') {
		i++;
	}
	i++; 
	int nameLen = 0;
	while (buffer[i + nameLen] != '\0') {
		nameLen++;
	}
	char* assignment = new char[nameLen + 1];
	for (int j = 0; j < nameLen; j++) {
		assignment[j] = buffer[i + j];
	}
	assignment[nameLen] = '\0';
	return assignment;
}



