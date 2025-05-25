#pragma once
#include <iostream>
#include "Utils.h"
#include "Context.h"
#include "Command.h"

using namespace Utils;

class ChangePasswordCommand : public Command
{
public:
	ChangePasswordCommand(const char* buffer, Context& ctx);

	void execute() override;

private:
	char* getOldPasswordFromBuffer(const char* buffer) const;
	char* getNewPasswordFromBuffer(const char* buffer) const;

	const char* buffer;
	Context& ctx;
};

