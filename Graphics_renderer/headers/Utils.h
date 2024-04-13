#pragma once
#include <string>
#include <iostream>

#define Log(x) std::cout << x << std::endl;

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
		//use it on non empty matrix
		template<typename T>
		void print_mat(const T & mat, const std::string& msg)
		{
			if (mat.length() == 0 || mat[0].length() == 0)
			{
				Log("Matrix is Empty !");
				return;
			}
			Log(msg);
			for (int i = 0; i < mat.length(); ++i) {
				for (int j = 0; j < mat[0].length(); ++j) {
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
			Log( msg << ": " );
			for (int i = 0; i < vec.length(); ++i) {
					std::cout << vec[i] << " ";				
			}
			std::cout << std::endl;

		}
	};
	

}

