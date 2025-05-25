#include "Utils.h"

namespace Utils
{
	const char* DEFAULT_ADMINISTRATOR_NAME = "adminName";
	const char* DEFAULT_ADMINISTRATOR_SURNAME = "adminSurname";
	const int DEFAULT_ADMINISTRATOR_ID = 0;
	const char* DEFAULT_ADMINISTRATOR_PASSWORD = "0000";
	const char* USERS_FILE_NAME = "usersData.bin";
	const char* COURSES_FILE_NAME = "coursesData.bin";

	unsigned stringLength(const char* text)
	{
		if (!text)
		{
			return 0;
		}
		unsigned length = 0;
		while (*text)
		{
			length++;
			text++;
		}
		return length;
	}
	char* stringCopy(char* dest, const char* src)
	{
		char* original = dest;
		while (*src)
		{
			*dest++ = *src++;
		}
		*dest = '\0';
		return original;
	}
	bool isPrefix(const char* prefix, const char* text)
	{
		while (*prefix)
		{
			if (*prefix != *text)
			{
				return false;
			}
			++prefix;
			++text;
		}
		return true;
	}
	bool areStringsEqual(const char* text1, const char* text2)
	{
		if (text1 == nullptr || text2 == nullptr)
		{
			return false;
		}
		if (!text1 || !text2)
		{
			return false;
		}
		while (*text1 && *text2)
		{
			if (*text1 != *text2)
				return false;

			++text1;
			++text2;
		}
		return *text1 == *text2;
	}

	bool isCharDigit(char c)
	{
		return c >= '0' && c <= '9';
	}
	bool isCharLetter(char c)
	{
		return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
	}
	int convertCharToInt(char c)
	{
		return c - '0';
	}
	bool isPasswordCharValid(char c)
	{
		return isCharDigit(c)|| isCharLetter(c);
	}
	int stringToInt(const char* str)
	{
		int result = 0;
		while (*str)
		{
			if (*str < '0' || *str > '9') break;
			result = result * 10 + convertCharToInt(*str);
			str++;
		}
		return result;
	}
	double stringToDouble(const char* str)
	{
		double result = 0.0;
		bool decimalPointReached = false;
		double fractionalDivisor = 10.0;

		while (*str)
		{
			if (*str == '.')
			{
				decimalPointReached = true;
				str++;
				continue;
			}

			if (*str < '0' || *str > '9') break;

			int digit = convertCharToInt(*str);
			if (!decimalPointReached)
			{
				result = result * 10 + digit;
			}
			else
			{
				result += digit / fractionalDivisor;
				fractionalDivisor *= 10.0;
			}

			str++;
		}

		return result;
	}
}

