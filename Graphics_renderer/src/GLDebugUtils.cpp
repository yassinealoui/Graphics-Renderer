#include "GLDebugUtils.h"
#include "GLEW/glew.h"


#define Log(x) std::cout << x << std::endl;

void print(Message type, const std::string& msg)
{
	std::string content = "";
	switch (type)
	{
	case Message::INFO: content += "[INFO]";
		break;
	case Message::WARNING: content += "[WARNING]";
		break;
	case Message::ERROR: content += "[ERROR]";
		break;
	default:content += "[]";
		break;
	}

	Log(content << " " << msg);
}


void clearGLErrors()
{
	while (glGetError() != GL_NO_ERROR);
}


const std::string glGetErrorName(const unsigned int errorCode)
{
	switch (errorCode)
	{
	case 1280: return "GL_INVALID_ENUM";
	case 1281: return "GL_INVALID_VALUE";
	case 1282: return "GL_INVALID_OPERATION";
	case 1283: return "GL_STACK_OVERFLOW";
	case 1284: return "GL_STACK_UNDERFLOW";
	case 1285: return "GL_OUT_OF_MEMORY";
	case 1286: return "GL_INVALID_FRAMEBUFFER_OPERATION";
	default: return "[no name]error : " + std::to_string(errorCode);
	}
}

const std::string createglErrorMessage(const unsigned int errorCode,
	const std::string& file,
	const int line,
	const std::string functionName)
{
	std::string err = glGetErrorName(errorCode);
	return err + " : " + file + " #" + std::to_string(line) + " :" + functionName;
}




void glCheckErrors(const std::string functionName, const char* file, const int line)
{
	unsigned int errorCode = glGetError();
	while (errorCode != GL_NO_ERROR) {
		std::string err_msg = createglErrorMessage(errorCode, file, line, functionName);
		print(Message::ERROR, err_msg);
		ASSERT(false);
		errorCode = glGetError();
	}

}