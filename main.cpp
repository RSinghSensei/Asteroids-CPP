#include <iostream>
#include <string>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "game.h"
#include "ShaderStream.h"
#include "Shader.h"



int main(void)
{
	Game engine;
	//Shader s1;	
	engine.Run();
	//t = s1.Load("shader.vert", "shader.frag");	
	
	return 0;
}