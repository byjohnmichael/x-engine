// Header file for log system, also macro setup for logging
#pragma once
#include <spdlog/spdlog.h>
#include <spdlog/fmt/ostr.h>
#include "XEngine/Core/XCore.h"
namespace XEngine
{
	class Logging
	{
	public:
		static void Init();
		static Ref<spdlog::logger>& GetCoreLogger()
			{ return m_CoreLogger; }
		static Ref<spdlog::logger>& GetClientLogger()
			{ return m_ClientLogger; }
	private:
		static Ref<spdlog::logger> m_CoreLogger;
		static Ref<spdlog::logger> m_ClientLogger;
	};
}
// Logging Macros
#if !XDIST
	#define XCORE_TRACE(...)::XEngine::Logging::GetCoreLogger()->trace(__VA_ARGS__)
	#define XCORE_INFO(...)::XEngine::Logging::GetCoreLogger()->info(__VA_ARGS__)
	#define XCORE_WARN(...)::XEngine::Logging::GetCoreLogger()->warn(__VA_ARGS__)
	#define XCORE_ERROR(...)::XEngine::Logging::GetCoreLogger()->error(__VA_ARGS__)
	#define XCORE_CRITICAL(...)::XEngine::Logging::GetCoreLogger()->critical(__VA_ARGS__)
	#define XCLIENT_TRACE(...)::XEngine::Logging::GetClientLogger()->trace(__VA_ARGS__)
	#define XCLIENT_INFO(...)::XEngine::Logging::GetClientLogger()->info(__VA_ARGS__)
	#define XCLIENT_WARN(...)::XEngine::Logging::GetClientLogger()->warn(__VA_ARGS__)
	#define XCLIENT_ERROR(...)::XEngine::Logging::GetClientLogger()->error(__VA_ARGS__)
	#define XCLIENT_CRITICAL(...)::XEngine::Logging::GetClientLogger()->critical(__VA_ARGS__)
#else
	#define XCORE_TRACE(...)
	#define XCORE_INFO(...)
	#define XCORE_WARN(...)
	#define XCORE_ERROR(...)
	#define XCORE_CRITICAL(...)
	#define XCLIENT_TRACE(...)
	#define XCLIENT_INFO(...)
	#define XCLIENT_WARN(...)
	#define XCLIENT_ERROR(...)
	#define XCLIENT_CRITICAL(...)
#endif

// byjohnmichael
