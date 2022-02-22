#include "Shader.h"

GLuint Shader::Load(std::string &vs, std::string &fs) {
	GLuint VertexShader, FragmentShader, ShaderProgram;
	GLint vs_success, fs_success;
	const char* vshader = vs.c_str();
	const char* fshader = fs.c_str();
	ShaderProgram = glCreateProgram();

	VertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(VertexShader, 1, &vshader, NULL);
	glCompileShader(VertexShader);
	glGetShaderiv(VertexShader, GL_COMPILE_STATUS, &vs_success);
	if (!vs_success) {
		char message[256];
		int message_length;
		std::cout << "Vertex Shader Failed to Compile!" << std::endl;
		glGetShaderInfoLog(VertexShader, 256, &message_length, message);
		std::cout << message << std::endl;
		return 0;
	}
	else {
		std::cout << "Successful Compilation!" << std::endl;
	}


	FragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(FragmentShader, 1, &fshader, NULL);
	glCompileShader(FragmentShader);
	glGetShaderiv(FragmentShader, GL_COMPILE_STATUS, &fs_success);
	if (!fs_success) {
		char message[256];
		int message_length;
		std::cout << "Fragment Shader Failed to Compile!" << std::endl;
		glGetShaderInfoLog(FragmentShader, 256, &message_length, message);
		std::cout << message << std::endl;	
		return 0;
	}
	else {
		std::cout << "Successful Compilation!" << std::endl;
	}

	glAttachShader(ShaderProgram, VertexShader);
	glAttachShader(ShaderProgram, FragmentShader);
	glLinkProgram(ShaderProgram);
	glDeleteShader(VertexShader);
	glDeleteShader(FragmentShader);


	ShaderProgramUse(ShaderProgram);

	return ShaderProgram;

}

void Shader::setUniform(GLuint &sp, const char* name, glm::mat4 matrix){
	GLuint v1 = glGetUniformLocation(sp, name);
	/*if (v1 == -1) { std::cout << "Uniform variable " << name << " not found!" << std::endl;}
	else { std::cout << "Uniform found!" << std::endl; }*/
	glUniformMatrix4fv(v1, 1, GL_FALSE, glm::value_ptr(matrix));
}

void Shader::ShaderProgramUse(GLuint& ShaderProgram){
	glUseProgram(ShaderProgram);
}
