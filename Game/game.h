#pragma once
#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm-0.9.9.8/glm/glm.hpp>
#include <Irrklang/irrKlang.h>
#include <glm-0.9.9.8/glm/gtx/string_cast.hpp>
#include <vector>

#include "../Shader/Shader.h"
#include "GameState.h"



class Game {
public:
	Game();
	~Game();
	void Init();
	void Run();
	//void updateWorld();

private:
	GLuint t;
	GLfloat deltatime{};
	GLfloat lastframe{};
	Shader s1;

	GLFWwindow* window = nullptr;
	const int w_width = 800, w_length = 600;	
	//bool menuState = true;
	irrklang::ISoundEngine* SoundEngine = nullptr;
	GameState* state = nullptr;

};
