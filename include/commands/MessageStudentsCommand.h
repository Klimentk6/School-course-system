#pragma once
#include <iostream>
#include "Utils.h"
#include "Context.h"
#include "Command.h"

using namespace Utils;

class MessageStudentsCommand : public Command
{
public:
	MessageStudentsCommand(const char* buffer, Context& ctx);

	void execute() override;

private:
	char* getCourseNameFromBuffer(const char* buffer) const;
	char* getMessageContentFromBuffer(const char* buffer) const;

	const char* buffer;
	Context& ctx;
};

