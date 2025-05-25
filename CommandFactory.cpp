#include "Utils.h"
#include "Context.h"
#include "Command.h"
#include "LoginCommand.h"
#include "LogoutCommand.h"
#include "AddTeacherCommand.h"
#include "AddStudentCommand.h"
#include "RemoveUserCommand.h"
#include "ChangePasswordCommand.h"
#include "MessageAllCommand.h"
#include "MailBoxCommand.h"
#include "CreateCourseCommand.h"
#include "AddToCourseCommand.h"
#include "EnrollCommand.h"
#include "AssignHomeworkCommand.h"
#include "MessageStudentsCommand.h"
#include "ClearMailboxCommand.h"
#include "SubmitAssignmentCommand.h"
#include "ViewAssignmentSubmissionsCommand.h"
#include "GradeAssignmentCommand.h"
#include "GradesCommand.h"
#include "MessageCommand.h"
#include "CommandFactory.h"

using namespace Utils;

bool isValidLoginInput(const char* buffer)
{
	const char* prefix = "login ";
	if (!isPrefix(prefix, buffer))
	{
		return false;
	}
	buffer += stringLength(prefix);
	while (isCharDigit(*buffer))
	{
		++buffer;
	}
	if (*buffer != ' ')
	{
		return false;
	}
	++buffer;
	if (!*buffer)
	{
		return false;
	}
	while (*buffer)
	{
		if (!isPasswordCharValid(*buffer))
		{
			return false;
		}
		++buffer;
	}
	return *buffer == '\0';
}
bool isValidLogoutInput(const char* buffer)
{
	const char* prefix = "logout";
	if (!isPrefix(prefix, buffer))
	{
		return false;
	}
	buffer += stringLength(prefix);
	return *buffer == '\0';
}
bool isValidExitInput(const char* buffer)
{
	const char* prefix = "exit";
	if (!isPrefix(prefix, buffer))
	{
		return false;
	}
	buffer += stringLength(prefix);
	return *buffer == '\0';
}
bool isValidAddTeacherInput(const char* buffer)
{
	const char* prefix = "add_teacher ";
	if (!isPrefix(prefix, buffer))
	{
		return false;
	}
	buffer += stringLength(prefix);
	if (!isCharLetter(*buffer))
	{
		return false;
	}
	while (isCharLetter(*buffer))
	{
		++buffer;
	}
	if (*buffer != ' ')
	{
		return false;
	}
	++buffer;
	if (!isCharLetter(*buffer))
	{
		return false;
	}
	while (isCharLetter(*buffer))
	{
		++buffer;
	}
	if (*buffer != ' ')
	{
		return false;
	}
	++buffer;
	if (!*buffer)
	{
		return false;
	}
	while (*buffer)
	{
		if (!isPasswordCharValid(*buffer))
		{
			return false;
		}
		++buffer;
	}
	return *buffer == '\0';
}
bool isValidAddStudentInput(const char* buffer)
{
	const char* prefix = "add_student ";
	if (!isPrefix(prefix, buffer))
	{
		return false;
	}
	buffer += stringLength(prefix);
	if (!isCharLetter(*buffer))
	{
		return false;
	}
	while (isCharLetter(*buffer))
	{
		++buffer;
	}
	if (*buffer != ' ')
	{
		return false;
	}
	++buffer;
	if (!isCharLetter(*buffer))
	{
		return false;
	}
	while (isCharLetter(*buffer))
	{
		++buffer;
	}
	if (*buffer != ' ')
	{
		return false;
	}
	++buffer;
	if (!*buffer)
	{
		return false;
	}
	while (*buffer)
	{
		if (!isPasswordCharValid(*buffer))
		{
			return false;
		}
		++buffer;
	}
	return *buffer == '\0';
}
bool isValidRemoveUserInput(const char* buffer)
{
	const char* prefix = "remove_user ";
	int prefixLen = stringLength(prefix);
	for (int i = 0; i < prefixLen; ++i)
	{
		if (buffer[i] != prefix[i])
			return false;
	}
	buffer += prefixLen;
	if (*buffer == '\0') return false;
	while (*buffer)
	{
		if (!isCharDigit(*buffer))
			return false;
		++buffer;
	}
	return true;
}
bool isValidChangePasswordInput(const char* buffer)
{
	const char* prefix = "change_password ";

	if (!isPrefix(prefix, buffer))
		return false;

	const char* ptr = buffer + stringLength(prefix);
	const char* oldPassStart = ptr;
	while (*ptr && *ptr != ' ')
	{
		if (!isPasswordCharValid(*ptr))
			return false;
		ptr++;
	}
	if (ptr == oldPassStart || *ptr != ' ')
		return false; 

	ptr++; 
	const char* newPassStart = ptr;
	while (*ptr)
	{
		if (!isPasswordCharValid(*ptr))
			return false;
		ptr++;
	}
	if (ptr == newPassStart)
		return false; 

	return true;
}
bool isValidMessageAllInput(const char* buffer)
{
	const char* prefix = "message_all ";
	if (!isPrefix(prefix, buffer))
	{
		return false;
	}
	buffer += stringLength(prefix);
	return *buffer != '\0';
}
bool isValidMailboxInput(const char* buffer)
{
	const char* prefix = "mailbox";
	return areStringsEqual(prefix, buffer);
}
bool isValidCreateCourseInput(const char* buffer)
{
	const char* prefix = "create_course ";
	if (!isPrefix(prefix, buffer))
	{
		return false;
	}
	buffer += stringLength(prefix);
	while (*buffer && *buffer != ' ')
	{
		buffer++;
	}
	if (*buffer != ' ')
	{
		return false;
	}
	buffer++; 
	while (*buffer)
	{
		if (!isPasswordCharValid(*buffer))
		{
			return false;
		}
		buffer++;
	}
	return true;
}
bool isValidAddToCourseInput(const char* buffer)
{
	const char* prefix = "add_to_course ";
	if (!isPrefix(prefix, buffer))
	{
		return false;
	}
	buffer += stringLength(prefix);
	if (*buffer == '\0')
	{
		return false;
	}
	int nameLen = 0;
	while (buffer[nameLen] != '\0' && buffer[nameLen] != ' ')
	{
		nameLen++;
	}
	if (buffer[nameLen] == '\0')
	{
		return false;
	}
	buffer += nameLen + 1;
	if (*buffer == '\0')
	{
		return false;
	}
	while (*buffer)
	{
		if (*buffer < '0' || *buffer > '9')
			return false;
		buffer++;
	}
	return true;
}
bool isValidEnrollInput(const char* buffer)
{
	const char* prefix = "enroll ";
	if (!isPrefix(prefix, buffer))
	{
		return false;
	}
	buffer += stringLength(prefix);
	while (*buffer != ' ' && *buffer != '\0')
	{
		buffer++;
	}
	if (*buffer != ' ')
	{
		return false;
	}
	buffer++;
	if (*buffer == '\0')
	{
		return false;
	}
	while (*buffer != '\0')
	{
		if (!isPasswordCharValid(*buffer))
		{
			return false;
		}
		buffer++;
	}
	return true;
}
bool isValidAssignHomeworkInput(const char* buffer)
{
	const char* prefix = "assign_homework ";
	if (!isPrefix(prefix, buffer)) 
	{
		return false;
	}
	buffer += stringLength(prefix);
	if (*buffer == '\0')
	{
		return false;
	}
	while (*buffer != ' ' && *buffer != '\0') 
	{
		buffer++;
	}
	if (*buffer != ' ')
	{
		return false;
	}
	buffer++;
	if (*buffer == '\0')
	{
		return false;
	}
	return true;
}
bool isValidMessageStudentsInput(const char* buffer)
{
	const char* prefix = "message_students ";
	int prefixLen = stringLength(prefix);
	for (int i = 0; i < prefixLen; i++)
	{
		if (buffer[i] != prefix[i])
		{
			return false;
		}
	}
	buffer += prefixLen;
	int i = 0;
	while (buffer[i] != ' ' && buffer[i] != '\0')
	{
		i++;
	}
	if (i == 0) 
	{
		return false;
	}
	buffer += i;
	if (*buffer == ' ')
	{
		buffer++;
	}
	return *buffer != '\0';
}
bool isValidClearMailboxInput(const char* buffer)
{
	return areStringsEqual(buffer, "clear_mailbox");
}
bool isValidSubmitAssignmentInput(const char* buffer)
{
	if (!buffer) return false;
	const char* prefix = "submit_assignment ";
	unsigned prefixLen = stringLength(prefix);
	for (unsigned i = 0; i < prefixLen; i++) 
	{
		if (buffer[i] != prefix[i]) 
		{
			return false;
		}
	}

	const char* ptr = buffer + prefixLen;

	if (*ptr == ' ' || *ptr == '\0') return false;

	while (*ptr && *ptr != ' ') 
	{
		ptr++;
	}
	if (*ptr != ' ') return false;
	ptr++; 

	if (*ptr == ' ' || *ptr == '\0') return false;

	while (*ptr && *ptr != ' ') {
		ptr++;
	}
	if (*ptr != ' ') return false;
	ptr++; 

	if (*ptr == '\0') return false; 

	return true;
}
bool isValidViewAssignmentSubmissionsInput(const char* buffer)
{
	if (!buffer) return false;

	const char* prefix = "view_assignment_submissions ";
	unsigned prefixLen = stringLength(prefix);

	for (unsigned i = 0; i < prefixLen; i++) {
		if (buffer[i] != prefix[i]) {
			return false;
		}
	}

	const char* ptr = buffer + prefixLen;

	if (*ptr == ' ' || *ptr == '\0') return false;
	while (*ptr && *ptr != ' ')
	{
		ptr++;
	}

	if (*ptr != ' ') return false;
	ptr++;

	if (*ptr == ' ' || *ptr == '\0') return false;
	while (*ptr && *ptr != ' ')
	{
		ptr++;
	}

	if (*ptr != '\0') return false;

	return true;
}
bool isValidGradeAssignmentInput(const char* buffer)
{
	const char* prefix = "grade_assignment ";
	int prefixLen = stringLength(prefix);

	for (int i = 0; i < prefixLen; i++)
	{
		if (buffer[i] != prefix[i]) return false;
	}

	buffer += prefixLen;

	if (*buffer == ' ' || *buffer == '\0') return false;
	while (*buffer && *buffer != ' ') buffer++;
	if (*buffer != ' ') return false;
	buffer++; 

	if (*buffer == ' ' || *buffer == '\0') return false;
	while (*buffer && *buffer != ' ') buffer++;
	if (*buffer != ' ') return false;
	buffer++;

	if (*buffer < '0' || *buffer > '9') return false;
	while (*buffer >= '0' && *buffer <= '9') buffer++;
	if (*buffer != ' ') return false;
	buffer++;

	bool seenDot = false;
	if (*buffer < '0' || *buffer > '9') return false;
	while (*buffer)
	{
		if (*buffer == '.')
		{
			if (seenDot) return false;
			seenDot = true;
		}
		else if (*buffer < '0' || *buffer > '9')
		{
			return false;
		}
		buffer++;
	}

	return true;
}
bool isValidGradesInput(const char* buffer)
{
	return areStringsEqual(buffer, "grades");
}

bool isValidMessageInput(const char* buffer)
{
	const char* prefix = "message ";
	if (!Utils::isPrefix(prefix, buffer))
		return false;

	buffer += Utils::stringLength(prefix);

	if (!*buffer) return false;

	bool foundDigit = false;
	while (*buffer && *buffer != ' ')
	{
		if (!Utils::isCharDigit(*buffer))
			return false;
		foundDigit = true;
		++buffer;
	}

	if (!foundDigit) return false;

	
	if (*buffer != ' ')
		return false;
	++buffer;

	if (!*buffer) return false;

	return true;
}

Command* createCommand(const char* buffer, Context& ctx)
{
	if (ctx.logged == UserType::None && isValidLoginInput(buffer))
	{
		return new LoginCommand(buffer, ctx);
	}
	else if (ctx.logged != UserType::None && isValidLogoutInput(buffer))
	{
		return new LogoutCommand(buffer, ctx);
	}
	else if (ctx.logged == UserType::Administrator && isValidAddTeacherInput(buffer))
	{
		return new AddTeacherCommand(buffer, ctx);
	}
	else if (ctx.logged == UserType::Administrator && isValidAddStudentInput(buffer))
	{
		return new AddStudentCommand(buffer, ctx);
	}
	else if(ctx.logged == UserType::Administrator && isValidRemoveUserInput(buffer))
	{
		return new RemoveUserCommand(buffer, ctx);
	}
	else if (ctx.logged != UserType::None && isValidChangePasswordInput(buffer))
	{
		return new ChangePasswordCommand(buffer, ctx);
	}
	else if (ctx.logged == UserType::Administrator && isValidMessageAllInput(buffer))
	{
		return new MessageAllCommand(buffer, ctx);
	}
	else if (ctx.logged != UserType::None && isValidMailboxInput(buffer))
	{
		return new MailBoxCommand(buffer, ctx);
	}
	else if (ctx.logged == UserType::Teacher && isValidCreateCourseInput(buffer))
	{
		return new CreateCourseCommand(buffer, ctx);
	}
	else if (ctx.logged == UserType::Teacher && isValidAddToCourseInput(buffer))
	{
		return new AddToCourseCommand(buffer, ctx);
	}
	else if (ctx.logged == UserType::Student && isValidEnrollInput(buffer))
	{
		return new EnrollCommand(buffer, ctx);
	}
	else if (ctx.logged == UserType::Teacher && isValidAssignHomeworkInput(buffer))
	{
		return new AssignHomeworkCommand(buffer, ctx);
	}
	else if (ctx.logged == UserType::Teacher && isValidMessageStudentsInput(buffer))
	{
		return new MessageStudentsCommand(buffer, ctx);
	}
	else if (ctx.logged != UserType::None && isValidClearMailboxInput(buffer))
	{
		return new ClearMailboxCommand(buffer, ctx);
	}
	else if (ctx.logged == UserType::Student && isValidSubmitAssignmentInput(buffer))
	{
		return new SubmitAssignmentCommand(buffer, ctx);
	}
	else if (ctx.logged == UserType::Teacher && isValidViewAssignmentSubmissionsInput(buffer))
	{
		return new ViewAssignmentSubmissionsCommand(buffer, ctx);
	}
	else if (ctx.logged == UserType::Teacher && isValidGradeAssignmentInput(buffer))
	{
		return new GradeAssignmentCommand(buffer, ctx);
	}
	else if (ctx.logged == UserType::Student && isValidGradesInput(buffer))
	{
		return new GradesCommand(buffer, ctx);
	}
	else if (ctx.logged == UserType::Student && isValidMessageInput(buffer))
	{
		return new MessageCommand(buffer, ctx);
	}
	else
	{
		std::cout << "Invalid input" << std::endl;
		return nullptr;
	}
}