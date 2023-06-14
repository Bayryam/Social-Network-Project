#include "HelperFunctions.h"
unsigned generateRandomNumber()
{
	std::srand(std::time(nullptr));
	unsigned randomId = std::rand();
	return randomId;
}
bool searchInText(const char* text, const char* pattern)
{
	size_t textLen = strlen(text);
	size_t patternLen = strlen(pattern);
	while (patternLen <= textLen)
	{
		if (isPrefix(pattern, text))
			return true;
		text++;
		textLen--;
	}
	return false;
}
bool isPrefix(const char* pattern, const char* text)
{
	while (*text != '\0' && *pattern != '\0')
	{
		if (*text != *pattern)
			return false;
		text++;
		pattern++;
	}
	return *pattern == '\0';
}
bool isDigit(char symbol) 
{
	return symbol >= '0' && symbol <= '9';
}
bool isTextNumber(const char* text)
{
	while (*text)
	{
		if (!isDigit(*text))
		{
			return false;
		}
		text++;
	}
	return true;
}
unsigned getDigitFromSymbol(char symbol)
{
	return symbol - '0';
}
unsigned getNumberFromText(const char* text)
{
	unsigned result = 0;
	while (*text)
	{
		result *= 10;
		result += getDigitFromSymbol(*text);
		text++;
	}
	return result;
}
