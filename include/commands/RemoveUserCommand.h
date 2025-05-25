#pragma once
#include <iostream>
#include "Utils.h"
#include "Context.h"
#include "Command.h"

using namespace Utils;

class RemoveUserCommand : public Command
{
public:
	RemoveUserCommand(const char* buffer, Context& ctx);

	void execute() override;

private:
	int getIdFromBuffer(const char* buffer) const; 

	const char* buffer;
	Context& ctx;
};

