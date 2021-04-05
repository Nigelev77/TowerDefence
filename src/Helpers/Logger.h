#pragma once
#include "spdlog/spdlog.h"
#include <memory>

class Logger
{
public:
	Logger();
	~Logger();

	std::shared_ptr<spdlog::logger> m_Trace;


};
