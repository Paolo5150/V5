#pragma once
#include <V5/Core/Logger.h>

#define LOG_ENABLE

#ifdef LOG_ENABLE

	#define V5CORE_LOG_TRACE(...)         ::V5Core::Logger::GetV5Logger()->trace(__VA_ARGS__)
	#define V5CORE_LOG_INFO(...)          ::V5Core::Logger::GetV5Logger()->info(__VA_ARGS__)
	#define V5CORE_LOG_WARN(...)          ::V5Core::Logger::GetV5Logger()->warn(__VA_ARGS__)
	#define V5CORE_LOG_ERROR(...)         ::V5Core::Logger::GetV5Logger()->error(__VA_ARGS__)
	#define V5CORE_LOG_CRITICAL(...)      ::V5Core::Logger::GetV5Logger()->critical(__VA_ARGS__)
#else
	#define V5CORE_LOG_TRACE(...)    
	#define V5CORE_LOG_INFO(...)     
	#define V5CORE_LOG_WARN(...)     
	#define V5CORE_LOG_ERROR(...)    
	#define V5CORE_LOG_CRITICAL(...) 
#endif // LOB_ENABLE