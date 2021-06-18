#include <Core/Logger.h>
#include "spdlog/sinks/stdout_color_sinks.h"
#include "spdlog/sinks/basic_file_sink.h"
using namespace V5Core;

std::shared_ptr<spdlog::logger> Logger::s_Logger;

void Logger::Init()
{
	s_Logger = spdlog::basic_logger_mt("V5", "V5Log.txt");

	spdlog::set_pattern("[%H:%M:%S] %v");

	V5LOG_INFO("------------------ START OF LOG ----------------------\n");

	spdlog::set_pattern("[%H:%M:%S] [%t] %^%l%$: %v");
	s_Logger->set_level(spdlog::level::trace);
	
}
