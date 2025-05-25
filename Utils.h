#pragma once

namespace Utils
{
	enum class UserType
	{
		Administrator,
		Teacher,
		Student,
		None
	};

	constexpr unsigned MAX_BUFFER_SIZE = 1024;
	constexpr unsigned MAX_PASSWORD_SIZE = 50;
	constexpr int MIN_CONTAINER_CAPACITY = 16;
	constexpr int MIN_MAIL_CAPACITY = 16;
	constexpr int MIN_ASSIGNMENT_CAPACITY = 16;
	constexpr int MIN_STUDENTS_CAPACITY = 16;
	constexpr int MIN_SUBMISSION_CAPACITY = 16;
	constexpr int MIN_COURSE_CAPACITY = 16;
	constexpr unsigned RESIZE_COEFF = 2;

	extern const char* DEFAULT_ADMINISTRATOR_NAME;
	extern const char* DEFAULT_ADMINISTRATOR_SURNAME;
	extern const int DEFAULT_ADMINISTRATOR_ID;
	extern const char* DEFAULT_ADMINISTRATOR_PASSWORD;
	extern const char* USERS_FILE_NAME;
	extern const char* COURSES_FILE_NAME;

	unsigned stringLength(const char* text);
	char* stringCopy(char* dest, const char* src);
	bool isPrefix(const char* prefix, const char* text);
	bool areStringsEqual(const char* text1, const char* text2);
	bool isCharDigit(char c);
	bool isCharLetter(char c);
	int convertCharToInt(char c);
	bool isPasswordCharValid(char c);
	int stringToInt(const char* str);
	double stringToDouble(const char* str);
}


