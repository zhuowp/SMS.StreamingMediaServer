#pragma once
#include <sstream>
#include <debugapi.h>
#include <iostream>

void inline OutPutDebug(std::string log)
{
	std::stringstream sdk_log;
	sdk_log << "[HIK_PLAY_LOG] " << log << std::endl;
	OutputDebugStringA(sdk_log.str().c_str());
	std::cout << sdk_log.str() << std::endl;
}