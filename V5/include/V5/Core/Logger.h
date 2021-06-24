#pragma once

#include "../Dll.h"
#include <string>
#include <fstream>
#include "spdlog/spdlog.h"

namespace V5Core
{
	class V5_API Logger
	{
	public:
		static void Init();
		inline static std::shared_ptr<spdlog::logger>& GetLogger() {  return s_Logger; }
		inline static std::shared_ptr<spdlog::logger>& GetV5Logger() { return s_V5Logger; }
		inline static std::shared_ptr<spdlog::logger>& GetConsoleLogger() { return s_ConsoleLogger; }



	private:
		static std::shared_ptr<spdlog::logger> s_Logger;
		static std::shared_ptr<spdlog::logger> s_V5Logger;
		static std::shared_ptr<spdlog::logger> s_ConsoleLogger;
	};

#define V5LOG_TRACE(...)         ::V5Core::Logger::GetLogger()->trace(__VA_ARGS__)
#define V5LOG_INFO(...)          ::V5Core::Logger::GetLogger()->info(__VA_ARGS__)
#define V5LOG_WARN(...)          ::V5Core::Logger::GetLogger()->warn(__VA_ARGS__)
#define V5LOG_ERROR(...)         ::V5Core::Logger::GetLogger()->error(__VA_ARGS__)
#define V5LOG_CRITICAL(...)      ::V5Core::Logger::GetLogger()->critical(__VA_ARGS__)

#define V5CLOG_TRACE(...)         ::V5Core::Logger::GetConsoleLogger()->trace(__VA_ARGS__)
#define V5CLOG_INFO(...)          ::V5Core::Logger::GetConsoleLogger()->info(__VA_ARGS__)
#define V5CLOG_WARN(...)          ::V5Core::Logger::GetConsoleLogger()->warn(__VA_ARGS__)
#define V5CLOG_ERROR(...)         ::V5Core::Logger::GetConsoleLogger()->error(__VA_ARGS__)
#define V5CLOG_CRITICAL(...)      ::V5Core::Logger::GetConsoleLogger()->critical(__VA_ARGS__)
}