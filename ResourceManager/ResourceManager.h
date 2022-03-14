#pragma once
#include <map>
#include <string>
#include <tuple>
#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>


class ResourceManager
{
	// Load images, point to images when needed
	// Load Music? I think irrklang already does that
	// Let's make it for textures first
public:
	static ResourceManager* getInstance();

	void loadTexture(const std::string& imgID, const char* imagePath);
	void freeTexture(unsigned char* imgSource);
	int getWidth(const std::string& imgID);
	int getHeight(const std::string& imgID);
	GLuint getTexture(const std::string& imgID);
	//unsigned char* getTexture(const std::string& imgID);

private:
	ResourceManager() {}
	static ResourceManager* m_resourceManager;
	std::map<std::string, std::tuple<unsigned char*, GLuint>>textureManager;
	std::map<std::string, std::pair<int, int>>textureDetails;

};