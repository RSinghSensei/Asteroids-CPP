#include "game.h"
#include "Shapes.h"
#include "Shader.h"
#include "Shapes.h"
#include "ShaderStream.h"
#include <glm-0.9.9.8/glm/gtx/string_cast.hpp>
#include <vector>
#include "Renderer.h"
#include "Asteroids.h"


Game::Game() {}
Game::~Game(){}




void Game::Run() {
	glfwInit();
	if (!glfwInit()) {
		std::cout << "GLFW could not be initialized" << std::endl;		
	}
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	window = glfwCreateWindow(w_width, w_length, "V", NULL, NULL);
	if (window == NULL) {
		std::cout << "Window could not be instatiated" << std::endl;
	}	
	glfwMakeContextCurrent(window);
	gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
	glViewport(0, 0, w_width, w_length);

	std::cout << glGetString(GL_VERSION) << std::endl;

	std::string vs = ShaderStream::ReadShaderSource("shader.vert");
	std::string fs = ShaderStream::ReadShaderSource("shader.frag");
	Shader s1;
	GLuint t = s1.Load(vs, fs);


	Renderer r1;
	//GLuint t1 = r1.rec.bufferint();

	//glm::mat4 proj = glm::perspective(45.0f, (GLfloat) w_width / w_length, 0.0f, 150.0f);
	glm::mat4 proj = glm::ortho(-20.0f, 20.0f, -20.0f, 20.0f, -1.0f, 1.0f);
	s1.setUniform(t, "Projection", proj);
	s1.setUniform(t, "Transform", glm::mat4(1.0f));
	
	glm::mat4 model = glm::mat4(1.0f);
	

	glClearColor(0.5f, 0.0f, 0.5f, 1.0f);

	GLfloat deltatime = 0.0f;
	GLfloat lastframe = 0.0f;

	// Player Characteristics

	glm::vec3 pos = glm::vec3(1.0f, 0.0f, 1.0f);
	glm::vec3 axis = glm::vec3(0.0f, 0.0f, 1.0f);
	GLfloat angle = 0.0f;
	GLfloat velocity = 0.0f;
	GLfloat acceleration = 10.0f;
	bool Engine = false;

	GLfloat refangle = angle;

	// Asteroids

	Asteroids testAst, Ast1, Ast2, ast3, ast4;
	std::vector<Asteroids>arr{ Ast1, Ast2 };
	//Asteroids arr[4]{ Ast1, Ast2 };

	bool AstHit = false;
	std::vector<int>AstStack;

	//GLuint t2 = testAst.a1.bufferint();
	/*glm::vec3 a1pos = glm::vec3(10.0f, 10.0f, 1.0f);
	glm::vec3 a1size = glm::vec3(10.0f, 10.0f, 1.0f);*/

	



	
	while (!glfwWindowShouldClose(window)) {
		if (glfwGetCurrentContext() == NULL) { std::cout << "Window out of scope" << std::endl; }

		glClear(GL_COLOR_BUFFER_BIT);

		//Delta time
		GLfloat currenttime = glfwGetTime();
		deltatime = currenttime - lastframe;
		lastframe = currenttime;

		//std::cout << "Deltatime: " << deltatime << std::endl;

		//Input 
		
		if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
			/*pos.y += (velocity * deltatime * cos(angle));
			pos.x += (velocity * deltatime * -sin(angle));*/
			if (velocity < 50.0f) {
				velocity += (acceleration * deltatime);
			}
			pos.y += (velocity * deltatime * cos(angle));
			pos.x += (velocity * deltatime * -sin(angle));		
			refangle = angle;
		}

		if (glfwGetKey(window, GLFW_KEY_W) == GLFW_RELEASE) {
			if (velocity > 0.0f) {
				velocity -= (0.9f*velocity*deltatime);			
				pos.y += (velocity * deltatime * cos(refangle));
				pos.x += (velocity * deltatime * -sin(refangle));
			}

			
			
		}

		/*pos.y += (velocity * deltatime * cos(angle));
		pos.x += (velocity * deltatime * -sin(angle));*/

		//Accel Check
		

		std::cout << "Velocity: " << velocity << std::endl;

		if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
			pos.y -= (10.0f * deltatime);
		}

		if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {		 
			angle -= 2.0f * deltatime;			
			//axis.z = 1.0f;

		}
		if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {			
			angle += 2.0f * deltatime;
			//axis.z = -1.0f;

		}

		if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS) {
			ast3.astsize = arr[arr.size() - 1].astsize/2.0f;
			ast3.astpos = arr[arr.size() - 1].astpos;
			ast3.astangle = rand() % 25 + 10;
			arr.push_back(ast3);
		}

		
		//Collision Check	
		
		std::cout << pos.x << std::endl;

		if (pos.x + 0.5f <= -20.0f || pos.x - 0.5f >= 20.0f) {
			std::cout << "Collision Detected" << std::endl;
			pos.x *= -1.0f;

		}

		if (pos.y + 1.5f <= -20.0f || pos.y - 1.5f >= 20.0f) {
			std::cout << "Collision Detected" << std::endl;
			pos.y *= -1.0f;

		}


		/*if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
			model = glm::translate(model, glm::vec3(0.0f, -0.01f, 0.0f));
			s1.setUniform(t, "Transform", model);
		}*/


		/*for (int i = 0; i < 9; i++) {
			std::cout << r1.rec.quad_verts[i] << " ";
		}
		std::cout << std::endl;*/
		r1.Draw(r1.rec.VAO, s1, t, pos, angle, axis);
		
		// Asteroid renderer

		for (int i = 0; i < arr.size(); i++) {
			arr[i].AsteroidDraw(arr[i].a1.VAO, s1, t, deltatime);
			arr[i].AsteroidCollisionCheck();				
		}
		
		
		


		/*if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS) {
			glm::mat4 model = glm::mat4(1.0f);
			model = glm::translate(model, glm::vec3(0.1f * x, 0.0f, 0.0f));
			s1.setUniform(t, "MVP", model);
		}*/
		
			
		


		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	glfwTerminate();

}
