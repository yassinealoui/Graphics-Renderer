#include "../headers/Utils.h"
#include "../vendor/glm/glm.hpp"

#include <random>

/*#########################################   mathUtils   #######################################################*/

namespace mathUtils {
	float getRandomFloat(float min_value, float max_value)
	{
		std::random_device rd;
		std::mt19937 eng(rd());
		std::uniform_real_distribution<float> distr(min_value, max_value);
		return distr(eng);
	}

	
}




/*#########################################   stringUtils   #######################################################*/
namespace stringUtils
{


	void tolower(std::string& str)
	{
		for (char& c : str)
		{
			c = std::tolower(c);
		}
	}

	void toupper(std::string& str)
	{
		for (char& c : str)
		{
			c = std::toupper(c);
		}
	}

	std::string getTolower(std::string str)
	{
		for (char& c : str)
		{
			c = std::tolower(c);
		}

		return str;
	}

	std::string getToupper(std::string str)
	{
		for (char& c : str)
		{
			c = std::toupper(c);
		}

		return str;
	}
}


