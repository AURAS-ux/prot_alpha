#pragma once
#include "SETTINGS.hpp"

class Logger
{
	
public:
	Logger() = delete;
	static void Print(const char* message,int snoozeStatus = SNOOZE);
	static void Println(const char* message,int snoozeStatus = SNOOZE);
	static void PrintError(const char* errorMessage,int snoozeStatus=SNOOZE);
	static void LogIntoFile(const char* log, int snoozeStatus = SNOOZE,int logDelayMs=1000);
	static size_t GetMemoryConsumptionKB();
	static void LogInnit();
	static void FreeLogger();
};

