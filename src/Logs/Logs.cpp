#include "Logs.hpp"
#include <sstream>
#include <iostream>
#include <chrono>
#include <fstream>
#include <iomanip>

namespace Match
{
	Logger LoggerInstance;
	const std::string LogLevelToTerminalColor(const LogLevel level)
	{
		/*
		* Info - Green
		* Debug - Blue
		* Warning - Yellow
		* Error - Red
		* Fatal - Purple
		*/
		switch (level)
		{
            case LogLevel::LOG_INFO:
			return "\033[1;32m";
		case LogLevel::LOG_DEBUG:
			return "\033[1;34m";
		case LogLevel::LOG_WARNING:
			return "\033[1;33m";
		case LogLevel::LOG_ERROR:
			return "\033[1;31m";
		case LogLevel::LOG_FATAL:
			return "\033[1;35m";
		default:
			return "\033[1;39m";
		}
	}
	std::string& operator<<(std::string& str, const LogLevel level)
	{
		switch (level)
		{
		case LogLevel::LOG_INFO:
			str.insert(0, LogLevelToTerminalColor(level) + "[INFO] ");
			return str;
		case LogLevel::LOG_DEBUG:
			str.insert(0, LogLevelToTerminalColor(level) + "[DEBUG] ");
			return str;
		case LogLevel::LOG_WARNING:
			str.insert(0, LogLevelToTerminalColor(level) + "[WARNING] ");
			return str;
		case LogLevel::LOG_ERROR:
			str.insert(0, LogLevelToTerminalColor(level) + "[ERROR] ");
			return str;
		case LogLevel::LOG_FATAL:
			str.insert(0, LogLevelToTerminalColor(level) + "[FATAL] ");
			return str;

		default:
			// Never should happen
			// Unknown should be color brown
			str.insert(0, "\033[1;39m[UNKNOWN] ");
			return str;
		}
	}
	std::stringstream& operator<<(std::stringstream& str, const LogLevel level)
	{
		switch (level)
		{
		case LogLevel::LOG_INFO:
			str << LogLevelToTerminalColor(level) << "[INFO] ";
			return str;
		case LogLevel::LOG_DEBUG:
			str << LogLevelToTerminalColor(level) << "[DEBUG] ";
			return str;
		case LogLevel::LOG_WARNING:
			str << LogLevelToTerminalColor(level) << "[WARNING] ";
			return str;
		case LogLevel::LOG_ERROR:
			str << LogLevelToTerminalColor(level) << "[ERROR] ";
			return str;
		case LogLevel::LOG_FATAL:
			str << LogLevelToTerminalColor(level) << "[FATAL] ";
			return str;

		default:
			// Never should happen
			// Unknown should be color brown
			str << "\033[1;39m[UNKNOWN] ";
			return str;
		}
	}
	void Logger::RawLog(const std::string& message)
	{
		std::printf("%s\n", message.c_str());
		this->m_currentBuffer->Push(message);
		if (++m_logCount % LOG_FLUSH_CONSTANT == 0)
			Flush();
	}
	void Logger::Log(const std::string& message, LogLevel level)
	{
		std::stringstream ss;
		// Calculate current time to add to the start of the log
		auto now = std::chrono::system_clock::now();
		auto now_c = std::chrono::system_clock::to_time_t(now);
		std::tm now_tm = *std::localtime(&now_c);
		ss << std::put_time(&now_tm, "[%Y-%m-%d %X] ");
		ss << level << message << "\033[0m";
		RawLog(ss.str());
		if (level == LogLevel::LOG_FATAL) [[unlikely]]
			std::exit(EXIT_FAILURE);
	}
	void Logger::Flush(bool invokeNewThread)
	{
		if (invokeNewThread)
			std::jthread flusher(&Logger::Flush, this, false);
		this->m_buffPointerMutex.lock();
		auto* flushTarget = m_currentBuffer;
		this->m_buffPointerMutex.unlock();
		FlipBuffers();
		// open a file in write mode.
		std::ofstream file;
		file.open("logs.txt", std::ios_base::app);
		flushTarget->ForEach([&](const std::string& message, std::ofstream& file) { file << message << std::endl; }, file);
		file.close();
	}


}