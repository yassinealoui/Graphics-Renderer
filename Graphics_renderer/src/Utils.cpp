#include "../headers/Utils.h"

void stringUtils::tolower(std::string& str)
{
	for (char& c : str)
	{
		c = std::tolower(c);
	}
}

void stringUtils::toupper(std::string& str)
{
	for (char& c : str)
	{
		c = std::toupper(c);
	}
}

std::string stringUtils::getTolower(std::string str)
{
	for (char& c : str)
	{
		c = std::tolower(c);
	}

	return str;
}

std::string stringUtils::getToupper(std::string str)
{
	for (char& c : str)
	{
		c = std::toupper(c);
	}

	return str;
}
