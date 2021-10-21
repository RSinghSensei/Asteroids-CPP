#pragma once
#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm-0.9.9.8/glm/glm.hpp>
#include <glm-0.9.9.8/glm/gtc/type_ptr.hpp>
#include <cstring>

class Shader {
public:
	GLuint Load(std::string& vs, std::string& fs);
	void setUniform(GLuint &sp, const char* name, glm::mat4 matrix);	
	void ShaderProgramUse(GLuint& ShaderProgram);
};