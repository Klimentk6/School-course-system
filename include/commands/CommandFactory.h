#pragma once
#include <iostream>
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

bool isValidLoginInput(const char* buffer);
bool isValidLogoutInput(const char* buffer);
bool isValidExitInput(const char* buffer);
bool isValidAddTeacherInput(const char* buffer);
bool isValidAddStudentInput(const char* buffer);
bool isValidRemoveUserInput(const char* buffer);
bool isValidChangePasswordInput(const char* buffer);
bool isValidMessageAllInput(const char* buffer);
bool isValidMailboxInput(const char* buffer);
bool isValidCreateCourseInput(const char* buffer);
bool isValidAddToCourseInput(const char* buffer);
bool isValidEnrollInput(const char* buffer);
bool isValidAssignHomeworkInput(const char* buffer);
bool isValidMessageStudentsInput(const char* buffer);
bool isValidClearMailboxInput(const char* buffer);
bool isValidSubmitAssignmentInput(const char* buffer);
bool isValidViewAssignmentSubmissionsInput(const char* buffer);
bool isValidGradeAssignmentInput(const char* buffer);
bool isValidGradesInput(const char* buffer);
bool isValidMessageInput(const char* buffer);

Command* createCommand(const char* buffer, Context& ctx);
