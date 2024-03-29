#include "Logger.hpp"
#include <iostream>
#include <Windows.h>
#include <psapi.h>
#include <filesystem>
#include <ctime>
#include<fstream>
#include <synchapi.h>

std::string log_dir;
std::string log_name;

size_t Logger::GetMemoryConsumptionKB()
{
	PROCESS_MEMORY_COUNTERS_EX pmc;
	if (!GetProcessMemoryInfo(GetCurrentProcess(), reinterpret_cast<PROCESS_MEMORY_COUNTERS*>(&pmc), sizeof(pmc)))
	{
		std::cerr << "Failed to retrieve process memory information\n";
		return 0;
	}

	SIZE_T memoryConsumptionKB = pmc.WorkingSetSize / 1024;

	return memoryConsumptionKB;
}

void Logger::LogInnit()
{
	time_t now = time(0);
	tm localTime;
	localtime_s(&localTime, &now);
	std::string dir_name;
	dir_name.append("logs");
	dir_name.append(std::to_string(localTime.tm_year + 1900) + std::to_string(localTime.tm_mon) + std::to_string(localTime.tm_mday));

	log_dir = dir_name;

	std::string file_name;
	file_name.append("log");
	file_name.append(std::to_string(localTime.tm_hour) + std::to_string(localTime.tm_min) + std::to_string(localTime.tm_sec));

	log_name = file_name;
	Println("Logger initialized");
}

void Logger::FreeLogger()
{
	Println("Logger destroyed", 0);
}
