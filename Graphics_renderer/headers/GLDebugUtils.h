#pragma once
#include <string>
#include <iostream>


#define ASSERT(x) if(!(x)) __debugbreak()

#define glCall(x) \
	clearGLErrors(); \
	x ;\
	glCheckErrors(#x,__FILE__,__LINE__);


enum Message {
	INFO,
	WARNING,
	ERROR
};

void print(Message type, const std::string& msg);

void clearGLErrors();

const std::string glGetErrorName(const unsigned int errorCode);

const std::string createglErrorMessage(const unsigned int errorCode,
	const std::string& file,
	const int line,
	const std::string functionName);



void glCheckErrors(const std::string functionName, const char* file, const int line);