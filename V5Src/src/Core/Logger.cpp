#include <V5/Core/Logger.h>
#include "spdlog/sinks/stdout_color_sinks.h"
#include "spdlog/sinks/basic_file_sink.h"
#include "spdlog/sinks/basic_file_sink-inl.h"
#include "spdlog/sinks/sink.h"
#include <iostream>
#include <chrono>
#include <ctime>  
#include <sstream>
using namespace V5Core;

std::shared_ptr<spdlog::logger> Logger::s_Logger;
std::shared_ptr<spdlog::logger> Logger::s_V5Logger;
std::shared_ptr<spdlog::logger> Logger::s_ConsoleLogger;

void Logger::Init()
{

	time_t t = time(0);   // get time now
	struct tm * now = localtime(&t);

	char buffer[80];
	strftime(buffer, 80, "%d-%m-%Y_%H-%M-%S", now);
	std::string fileName(buffer);

	std::stringstream ss;
	ss << "Logs\\V5Log_" << fileName << ".txt";

	auto file_sink = std::make_shared<spdlog::sinks::basic_file_sink_mt>(ss.str());

	s_Logger = std::make_shared<spdlog::logger>(spdlog::logger("Generic",file_sink));
	s_V5Logger = std::make_shared<spdlog::logger>(spdlog::logger("V5Engine",file_sink));
	s_ConsoleLogger = spdlog::stdout_color_mt("Console");

	spdlog::set_pattern("[%H:%M:%S] %v");

	s_Logger->info("------------------ START OF LOG ----------------------\n");

	s_Logger->set_level(spdlog::level::trace);
	spdlog::set_pattern("[%H:%M:%S] [%t] %^%l%$: %v");

	
}
