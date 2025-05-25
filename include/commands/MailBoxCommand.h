#pragma once
#include <iostream>
#include "Utils.h"
#include "Context.h"
#include "Command.h"

using namespace Utils;

class MailBoxCommand : public Command
{
public:
	MailBoxCommand(const char* buffer, Context& ctx);

	void execute() override;

private:
	const char* buffer;
	Context& ctx;
};

