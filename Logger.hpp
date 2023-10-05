#pragma once
#include <string>

#include "SETTINGS.hpp"
#include <iostream>
#include <filesystem>
#include <ctime>


class Logger
{
public:
	Logger() = delete;

	template<typename T>
	static void Print(const T& message, int snoozeStatus = SNOOZE);

	template<typename T>
	static void Println(const T& message, int snoozeStatus = SNOOZE);

	template<typename T>
	static void PrintError(const T& errorMessage, int snoozeStatus = SNOOZE);

	template<typename T>
	static void LogIntoFile(const T& log, int snoozeStatus = SNOOZE, int logDelayMs = 1000);
	


	static size_t GetMemoryConsumptionKB();
	static void LogInnit();
	static void FreeLogger();
};

template <typename T>
void Logger::Print(const T& message, int snoozeStatus)
{
	if (!snoozeStatus)
		std::cout  << "INFO:" << message;
}

template <typename T>
void Logger::Println(const T& message, int snoozeStatus)
{
	if (!snoozeStatus)
		std::cout <<"INFO:" << message << "\n";
}

template <typename T>
void Logger::PrintError(const T& errorMessage, int snoozeStatus)
{
	if (!snoozeStatus)
		std::cout  << "ERROR:" << errorMessage << "\n";
}

template <typename T>
void Logger::LogIntoFile(const T& log, int snoozeStatus, int logDelayMs)
{
	/*time_t now = time(0);
	tm localTime;
	localtime_s(&localTime, &now);
	if (std::filesystem::create_directory(std::filesystem::current_path() / log_dir))
	{
		Println("Directory created sucessfully at path", 0);
	}
	else PrintError("Could not create directory");

	std::ofstream outputFile(log_dir + "\\" + log_name + ".txt", std::ofstream::app);

	if (!snoozeStatus)
	{
		outputFile << "[" << std::to_string(localTime.tm_hour) << ":" << std::to_string(localTime.tm_min) << ":" <<
			std::to_string(localTime.tm_sec) << "]" << log << "\n";
	}

	outputFile.close();*/
}
