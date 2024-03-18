#pragma once
#include <string>
#include <iostream>

namespace stringUtils{
	void tolower(std::string& str);
	void toupper(std::string& str);

	std::string getTolower(std::string str);
	std::string getToupper(std::string str);
}

namespace mathUtils {
	float getRandomFloat(float min_value, float max_value);


	class Matrix
	{
	public:
		template<typename T>
		static void print(const T& mat, std::string msg)
		{
			std::cout << msg << ": " << std::endl;
			for (int i = 0; i < mat.length(); ++i) {
				for (int j = 0; j < mat.length(); ++j) {
					std::cout << mat[i][j] << " ";
				}
				std::cout << std::endl;
			}
		}
	};


	class Vector
	{
	public:
		template<typename T>
		static void print(const T& vec, std::string msg)
		{
			std::cout << msg << ": " << std::endl;
			for (int i = 0; i < vec.length(); ++i) {
					std::cout << vec[i] << " ";				
			}
			std::cout << std::endl;

		}
	};
	

}

