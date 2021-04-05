#include "Logger.h"
#include "spdlog/sinks/stdout_color_sinks.h"

Logger::Logger()
{
	m_Trace = spdlog::stdout_color_mt("Trace");
	m_Trace->set_level(spdlog::level::trace);
	m_Trace->info("Initialised tracer");
}

Logger::~Logger()
{
	m_Trace->info("Deleting tracer");
}
