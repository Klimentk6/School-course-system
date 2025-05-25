#pragma once
#include <iostream>
#include "Utils.h"
#include "Context.h"
#include "Command.h"

using namespace Utils;

class LogoutCommand : public Command
{
public:
    LogoutCommand(const char* buffer, Context& ctx);

    void execute() override;

private:
    const char* buffer;
    Context& ctx;
};
