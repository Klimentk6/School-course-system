#pragma once
#include <iostream>
#include "Utils.h"
#include "Context.h"
#include "Command.h"

using namespace Utils;

class GradeAssignmentCommand : public Command
{
public:
	GradeAssignmentCommand(const char* buffer, Context& ctx);

	void execute() override;

private:
	char* getCourseFromBuffer(const char* buffer) const;
	char* getAssignmentFromBuffer(const char* buffer) const;
	int getStudentIdFromBuffer(const char* buffer) const;
	double getGradeFromBuffer(const char* buffer) const;

	const char* buffer;
	Context& ctx;
};

