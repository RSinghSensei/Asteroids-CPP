#include "ResourceManager.h"
#include "stb/stb_image.h"

ResourceManager* ResourceManager::m_resourceManager = nullptr;

ResourceManager* ResourceManager::getInstance()
{
	if (m_resourceManager == nullptr)
	{
		m_resourceManager = new ResourceManager();
		std::cout << "Resource Manager Created" << std::endl;
	}

	return m_resourceManager;

}

void ResourceManager::loadTexture(const std::string& imgID, const char* imgPath)
{
	GLuint texture;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	stbi_set_flip_vertically_on_load(true);
	int width, height, nrChannels;
	unsigned char* data = stbi_load(imgPath, &width, &height, &nrChannels, 0);
	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Failed to load texture" << std::endl;
	}
	std::tuple<unsigned char*, GLuint> tempTuple{ data, texture };
	textureManager.insert(std::pair<std::string, std::tuple<unsigned char*, GLuint>>(imgID, tempTuple));
	textureDetails.insert(std::pair<std::string, std::pair<int, int>>(imgID, { width, height }));
	glBindTexture(GL_TEXTURE_2D, 0);
	stbi_image_free(data);
}

void ResourceManager::freeTexture(unsigned char* imgSource)
{
	//stbi_image_free(imgSource);
}

int ResourceManager::getWidth(const std::string& imgID)
{
	return textureDetails[imgID].first;

}
int ResourceManager::getHeight(const std::string& imgID)
{
	return textureDetails[imgID].second;

}

GLuint ResourceManager::getTexture(const std::string& imgID)
{
	auto tempT = textureManager.at(imgID);
	return std::get<GLuint>(tempT);

}
//unsigned char* ResourceManager::getTexture(const std::string& imgID)
//{
//	/*auto tempT = textureManager.at(imgID);
//	std::get<unsigned char*>(tempT)*/
//	return textureManager[imgID];
//}