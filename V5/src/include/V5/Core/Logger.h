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
		inline static std::shared_ptr<spdlog::logger>& GetLogger() { return s_Logger; }

	private:
		static std::shared_ptr<spdlog::logger> s_Logger;
	};

#define V5LOG_TRACE(...)         ::V5Core::Logger::GetLogger()->trace(__VA_ARGS__)
#define V5LOG_INFO(...)          ::V5Core::Logger::GetLogger()->info(__VA_ARGS__)
#define V5LOG_WARN(...)          ::V5Core::Logger::GetLogger()->warn(__VA_ARGS__)
#define V5LOG_ERROR(...)         ::V5Core::Logger::GetLogger()->error(__VA_ARGS__)
#define V5LOG_CRITICAL(...)      ::V5Core::Logger::GetLogger()->critical(__VA_ARGS__)
}