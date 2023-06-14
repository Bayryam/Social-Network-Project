#pragma once
#include <ctime>
#include <iostream>

unsigned generateRandomNumber();
bool searchInText(const char* text, const char* pattern);
bool isPrefix(const char* pattern, const char* text);
bool isDigit(char symbol);
bool isTextNumber(const char* text);
unsigned getDigitFromSymbol(char symbol);
unsigned getNumberFromText(const char* text);




