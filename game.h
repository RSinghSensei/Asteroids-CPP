#pragma once
#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm-0.9.9.8/glm/glm.hpp>

class Game {
public:
	Game();
	~Game();
	void Run();
private:
	GLFWwindow* window;
	const int w_width = 800, w_length = 600;	
	

};
