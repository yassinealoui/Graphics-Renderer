#pragma once
#include <string>


namespace stringUtils{
	void tolower(std::string& str);
	void toupper(std::string& str);

	std::string getTolower(std::string str);
	std::string getToupper(std::string str);
}

namespace mathUtils {
	float getRandomFloat(float min_value, float max_value);

}

