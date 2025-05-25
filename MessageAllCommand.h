#pragma once
#include <iostream>
#include "Utils.h"
#include "Context.h"
#include "Command.h"

using namespace Utils;

class MessageAllCommand : public Command
{
public:
	MessageAllCommand(const char* buffer, Context& ctx);

	void execute() override;

private:
	char* getMessageContent(const char* buffer) const;

	const char* buffer;
	Context& ctx;
};

