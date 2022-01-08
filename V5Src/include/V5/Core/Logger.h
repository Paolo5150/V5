#pragma once
#pragma warning(disable: 4251)

#include <string>
#include <fstream>
#include <spdlog/spdlog.h>
#include <V5/Core/PlatformDetection.h>

#define ENABLE_FILE_LOGS 1
#define ENABLE_CONSOLE_LOGS 1

namespace V5Core
{
	class Logger
	{
	public:
		static void Init();
		static void Shutdown();
		inline static std::shared_ptr<spdlog::logger>& GetLogger() {  return s_Logger; }
		inline static std::shared_ptr<spdlog::logger>& GetConsoleLogger() { return s_ConsoleLogger; }



	private:
		static std::shared_ptr<spdlog::logger> s_Logger;
		static std::shared_ptr<spdlog::logger> s_ConsoleLogger;
	};

#if ENABLE_FILE_LOGS
#define V5LOG_TRACE(...)         ::V5Core::Logger::GetLogger()->trace(__VA_ARGS__)
#define V5LOG_INFO(...)          ::V5Core::Logger::GetLogger()->info(__VA_ARGS__)
#define V5LOG_WARN(...)          ::V5Core::Logger::GetLogger()->warn(__VA_ARGS__)
#define V5LOG_ERROR(...)         ::V5Core::Logger::GetLogger()->error(__VA_ARGS__)
#define V5LOG_CRITICAL(...)      ::V5Core::Logger::GetLogger()->critical(__VA_ARGS__)

#else
	#define V5LOG_TRACE(...)       
	#define V5LOG_INFO(...)        
	#define V5LOG_WARN(...)        
	#define V5LOG_ERROR(...)       
	#define V5LOG_CRITICAL(...)
#endif


#if ENABLE_CONSOLE_LOGS
	#ifdef V5_PLATFORM_WINDOWS
		#define V5CLOG_TRACE(...)         ::V5Core::Logger::GetConsoleLogger()->trace(__VA_ARGS__)
		#define V5CLOG_INFO(...)          ::V5Core::Logger::GetConsoleLogger()->info(__VA_ARGS__)
		#define V5CLOG_WARN(...)          ::V5Core::Logger::GetConsoleLogger()->warn(__VA_ARGS__)
		#define V5CLOG_ERROR(...)         ::V5Core::Logger::GetConsoleLogger()->error(__VA_ARGS__)
		#define V5CLOG_CRITICAL(...)      ::V5Core::Logger::GetConsoleLogger()->critical(__VA_ARGS__)
	#elif defined V5_PLATFORM_ANDROID
		#define V5CLOG_TRACE(...)         ::V5Core::Logger::GetLogger()->trace(__VA_ARGS__)
		#define V5CLOG_INFO(...)          ::V5Core::Logger::GetLogger()->info(__VA_ARGS__)
		#define V5CLOG_WARN(...)          ::V5Core::Logger::GetLogger()->warn(__VA_ARGS__)
		#define V5CLOG_ERROR(...)         ::V5Core::Logger::GetLogger()->error(__VA_ARGS__)
		#define V5CLOG_CRITICAL(...)      ::V5Core::Logger::GetLogger()->critical(__VA_ARGS__)
		#else
			#define V5CLOG_TRACE(...)      
			#define V5CLOG_INFO(...)       
			#define V5CLOG_WARN(...)       
			#define V5CLOG_ERROR(...)      
			#define V5CLOG_CRITICAL(...) 
		#endif
#else 

#define V5CLOG_TRACE(...)      
#define V5CLOG_INFO(...)       
#define V5CLOG_WARN(...)       
#define V5CLOG_ERROR(...)      
#define V5CLOG_CRITICAL(...)   
#endif
}