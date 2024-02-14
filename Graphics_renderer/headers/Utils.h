#pragma once
#include <string>

namespace stringUtils{
	static void tolower(std::string& str);
	static void toupper(std::string& str);

	std::string getTolower(std::string str);
	std::string getToupper(std::string str);

}