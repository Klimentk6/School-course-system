#pragma once
#include <iostream>
#include "Utils.h"
#include "Context.h"
#include "Command.h"

using namespace Utils;

class SubmitAssignmentCommand : public Command
{
public:
	SubmitAssignmentCommand(const char* buffer, Context& ctx);

	void execute() override;

private:
	char* getCourseFromBuffer(const char* buffer) const;
	char* getAssignmentFromBuffer(const char* buffer) const;
	char* getContentFromBuffer(const char* buffer) const;

	const char* buffer;
	Context& ctx;
};

