#pragma once
#include <iostream>
#include "Utils.h"
#include "Context.h"
#include "Command.h"

using namespace Utils;

class AddTeacherCommand : public Command
{
public:
	AddTeacherCommand(const char* buffer, Context& ctx);

	void execute() override;

private:
	char* getNameFromBuffer(const char* buffer) const;
	char* getSurnameFromBuffer(const char* buffer) const;
	char* getPasswordFromBuffer(const char* buffer) const;

	const char* buffer;
	Context& ctx;
};

