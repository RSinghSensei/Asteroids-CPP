#include <iostream>
#include <string>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Game/game.h"


int main(void)
{
	Game engine;
	//Shader s1;	
	engine.Run();
	//t = s1.Load("shader.vert", "shader.frag");	
	
	return 0;
}