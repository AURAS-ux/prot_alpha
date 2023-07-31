#include "FileManager.hpp"


/**
 * \brief File browser for a file(.jpg,.png,.jpeg,.tff etc)
 * \param fileName the file name, the extentsion must be inculded
 * \return A string which represents the path to the file or Nullpath in case the file could not be found
 */
std::string FileManager::GetFilePath(std::string fileName)
{
	std::filesystem::path assetsPath = std::filesystem::current_path().parent_path();
	uint16_t fileSearchCounter = 0;
	bool retriesLeft = true;
	while(std::filesystem::exists(assetsPath/"assets") == false)
	{
		assetsPath = assetsPath.parent_path();
		for(const auto& entry : std::filesystem::recursive_directory_iterator(assetsPath))
		{
			if(entry.exists() && entry.path().filename().string() == "assets")
			{
 				assetsPath = entry.path().parent_path();
			}
		} 
	}
	assetsPath /= "assets";

	while (std::filesystem::exists(assetsPath/ fileName) == false && retriesLeft)
	{
 		for (const auto& entry : std::filesystem::recursive_directory_iterator(assetsPath)) 
		{
 			fileSearchCounter++;
			if (fileSearchCounter <= 1000 && entry.exists() && entry.path().filename().string() == fileName)
			{
				return entry.path().string();
			}
			else if (fileSearchCounter == 1000)
			{
				Logger::Print("Exceeded number of searches after 1000 tries", 0);
				retriesLeft = false;
				return "Nullpath returned";
			}
		}
	}
}