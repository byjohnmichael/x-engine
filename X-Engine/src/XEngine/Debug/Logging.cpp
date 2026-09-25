// Sets up logging system with Init function
#include "Xpch.h"
#include "XEngine/Debug/Logging.h"
#include <spdlog/sinks/basic_file_sink.h>
#include <spdlog/sinks/stdout_color_sinks.h>
namespace XEngine
{
	Ref<spdlog::logger> Logging::m_CoreLogger;
	Ref<spdlog::logger> Logging::m_ClientLogger;
	void Logging::Init()
	{
		// Hide Console Window on Distribution Builds
		//#if XDEBUG
			::ShowWindow(::GetConsoleWindow(), SW_SHOW);
		//#else
			//::ShowWindow(::GetConsoleWindow(), SW_HIDE);
		//#endif
		std::vector<spdlog::sink_ptr> logSinks;
		logSinks.emplace_back(std::make_shared<spdlog::sinks::stdout_color_sink_mt>());
		logSinks.emplace_back(std::make_shared<spdlog::sinks::basic_file_sink_mt>("XEngine.log", true));
		logSinks[0]->set_pattern("%^[%T] %n: %v%$");
		logSinks[1]->set_pattern("[%T] [%l] %n: %v");
		m_CoreLogger = std::make_shared<spdlog::logger>("X-ENGINE", begin(logSinks), end(logSinks));
		spdlog::register_logger(m_CoreLogger);
		m_CoreLogger->set_level(spdlog::level::trace);
		m_CoreLogger->flush_on(spdlog::level::trace);
		m_ClientLogger = std::make_shared<spdlog::logger>("APP", begin(logSinks), end(logSinks));
		spdlog::register_logger(m_ClientLogger);
		m_ClientLogger->set_level(spdlog::level::trace);
		m_ClientLogger->flush_on(spdlog::level::trace);
	}
}

// byjohnmichael
