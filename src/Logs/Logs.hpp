#pragma once
#include <iostream>
#include <memory>
#include <mutex>
#include <sstream>
#include <array>
#include <functional>
#include <format>

#ifndef LOG_FLUSH_CONSTANT
#define LOG_FLUSH_CONSTANT 1024
#endif // !LOG_FLUSH_CONSTANT


namespace Match
{
	enum class LogLevel : unsigned char
	{
		LOG_INFO,
		LOG_DEBUG,
		LOG_WARNING,
		LOG_ERROR,
		LOG_FATAL
	};
	template<typename T>
	void FormatArg(std::ostringstream& oss, const T& arg) {
		oss << arg;
	}

	template<typename T, typename... Args>
	void FormatArg(std::ostringstream& oss, const T& arg, Args... args) {
		oss << arg;
		FormatArg(oss, args...);
	}
	template<typename... Args>
	std::string FormatString(const std::string& format, Args... args) {
		std::ostringstream oss;
		size_t argIndex = 0;
		size_t formatIndex = 0;
		while (formatIndex < format.size()) {
			if (format[formatIndex] == '{') {
				// Find the closing '}'
				size_t endBraceIndex = format.find('}', formatIndex);
				if (endBraceIndex == std::string::npos) {
					throw std::runtime_error("Invalid format string: Missing closing brace");
				}
				// Output the corresponding argument
				if (argIndex >= sizeof...(args)) {
					throw std::runtime_error("Invalid argument index");
				}
				FormatArg(oss, args...);
				++argIndex;
				formatIndex = endBraceIndex + 1;
			}
			else {
				oss << format[formatIndex++];
			}
		}
		return oss.str();
	}

	const std::string LogLevelToTerminalColor(const LogLevel level);

	std::string& operator<<(std::string& str, const LogLevel level);
	std::stringstream& operator<<(std::stringstream& str, const LogLevel level);

	template<size_t BuffMaxSize>
	class StaticBuffer
	{
	public:
		StaticBuffer() = default;
		~StaticBuffer() = default;
		StaticBuffer(const StaticBuffer& other)
		{
			std::lock_guard<std::mutex> lock(m_mutex);
			m_currentIndex = 0;
			std::copy(other.m_buffer.begin(), other.m_buffer.end(), m_buffer.begin());
		}
		StaticBuffer& operator=(const StaticBuffer& other)
		{
			std::lock_guard<std::mutex> lock(m_mutex);
			m_currentIndex = 0;
			std::copy(other.m_buffer.begin(), other.m_buffer.end(), m_buffer.begin());
			return *this;
		}

		StaticBuffer(StaticBuffer&& other)
		{
			std::lock_guard<std::mutex> lock(m_mutex);
			m_currentIndex = 0;
			std::move(other.m_buffer.begin(), other.m_buffer.end(), m_buffer.begin());
		}

		void Push(const std::string& message)
		{
			std::lock_guard<std::mutex> lock(m_mutex);
			m_buffer[m_currentIndex] = message;
			m_currentIndex++;
		}

		template<typename Func, typename... Args>
		void ForEach(Func func, Args&&... args)
		{
			std::lock_guard<std::mutex> lock(m_mutex);
			for (size_t i = 0; i < m_currentIndex; i++)
				func(m_buffer[i], std::forward<Args>(args)...);
		}



	public:
		std::array<std::string, BuffMaxSize> m_buffer;
		size_t m_currentIndex = 0;
		std::mutex m_mutex;
	};

	class Logger
	{
	public:
		Logger() = default;
		~Logger() {
			Flush(false); Flush(false);
		}
		Logger(const Logger&) = default;

		void RawLog(const std::string& message);
		void Log(const std::string& message, LogLevel level);
		template<typename... Args>
		void Log(const std::string& message, LogLevel level, Args&&... arg)
		{
			Log(FormatString<Args...>(message, std::forward<Args>(arg)...), level);
		}
		void Flush(bool invokeNewThread=true);
		StaticBuffer<LOG_FLUSH_CONSTANT>* GetBuffer() { return m_currentBuffer; }
		void FlipBuffers() { std::lock_guard<std::mutex> lock(m_buffPointerMutex); m_currentBuffer = (m_currentBuffer == &m_buffOne) ? &m_buffTwo : &m_buffOne; }
	private:
	private:
		uint64_t m_logCount = 0;
		std::mutex m_buffPointerMutex;
		StaticBuffer<LOG_FLUSH_CONSTANT> m_buffOne;
		StaticBuffer<LOG_FLUSH_CONSTANT> m_buffTwo;
		StaticBuffer<LOG_FLUSH_CONSTANT>* m_currentBuffer = &m_buffOne;
	};

	extern Logger LoggerInstance;
}