#pragma once
#include <filesystem>
#include "Logger.hpp"
class FileManager
{
public:
	FileManager() = delete;
	static std::string GetFilePath(std::string);
};

