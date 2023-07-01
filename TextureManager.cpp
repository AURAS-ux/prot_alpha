#include "TextureManager.hpp"
#include "Logger.hpp"

void TextureManager::GetSprite(std::string texturePath, std::unique_ptr<sf::Texture>& textureOut)
{
	if(textureOut == nullptr)
	{
		try
		{
			textureOut = std::make_unique<sf::Texture>();
			textureOut->loadFromFile(texturePath);
		}catch (...)
		{
			Logger::PrintError("Error in loading texture for path",0);
		}
	}else
	{
		textureOut.reset();
		try
		{
			textureOut = std::make_unique<sf::Texture>();
			textureOut->loadFromFile(texturePath);
		}
		catch (...)
		{
			Logger::PrintError("Error in loading texture for path", 0);
		}
	}
}

void TextureManager::GetSpritesVector(std::vector<std::string> texturePath, std::vector<std::unique_ptr<sf::Texture>>& texturesVectorOut)
{
	if(texturePath.size() != texturesVectorOut.size())
	{
		Logger::PrintError("Error: different size for input and output", 0);
	}else
	{
		for(int i=0;i<texturePath.size();i++)
		{
			if(texturesVectorOut.at(i) == nullptr)
			{
				try
				{
					texturesVectorOut.at(i) = std::make_unique<sf::Texture>();
					texturesVectorOut.at(i).get()->loadFromFile(texturePath.at(i));
				}catch (...)
				{
					Logger::PrintError("Error in loading texture for path", 0);
				}
			}
		}
	}
}
