#include "game.h"
#include "../Shapes/Shapes.h"
#include "../Shader/Shader.h"
#include "../Shader/ShaderStream.h"
#include <glm-0.9.9.8/glm/gtx/string_cast.hpp>
#include <vector>
#include "../Renderer/Renderer.h"
#include "../Asteroids/Asteroids.h"
#include "../Bullet/Bullet.h"
#include "../SpaceObjects/Planet.h"
#include <Irrklang/irrKlang.h>

Game::Game() {}
Game::~Game(){}

std::pair<float, float> ProjVerts(std::vector<glm::vec2>& v1, glm::vec2& axis) {
	float minA = FLT_MAX;
	float maxA = FLT_MIN;
	for (int i = 0; i < v1.size(); i++) {
		float proj = glm::dot(v1[i], axis);
		if (proj > maxA) { maxA = proj; }
		if (proj < minA) { minA = proj; }
	}
	std::pair<float, float> projvals{ minA, maxA };
	return projvals;

}

bool SeperatingAxisCollision(std::vector<glm::vec2>& pol1, std::vector<glm::vec2>& pol2, glm::vec2& p1normal1, glm::vec2& p1normal2, glm::vec2& p1normal3, glm::vec2& p1normal4) {

	glm::vec2 p2edge1 = pol2[1] - pol2[0];
	glm::vec2 p2edge2 = pol2[2] - pol2[1];
	glm::vec2 p2edge3 = pol2[3] - pol2[2];
	glm::vec2 p2edge4 = pol2[0] - pol2[3];
	glm::vec2 p2normal1 = glm::vec2(p2edge1.y, -p2edge1.x);
	glm::vec2 p2normal2 = glm::vec2(p2edge2.y, -p2edge2.x);
	glm::vec2 p2normal3 = glm::vec2(p2edge3.y, -p2edge3.x);
	glm::vec2 p2normal4 = glm::vec2(p2edge4.y, -p2edge4.x);

	std::pair<float, float>projvals1 = ProjVerts(pol1, p1normal1);
	std::pair<float, float>projvals2 = ProjVerts(pol2, p1normal1);
	if (projvals1.first >= projvals2.second || projvals2.first >= projvals1.second) {
		return false;
	}	
	std::pair<float, float>projvals3 = ProjVerts(pol1, p1normal2);
	std::pair<float, float>projvals4 = ProjVerts(pol2, p1normal2);
	if (projvals3.first >= projvals4.second || projvals4.first >= projvals3.second) {
		return false;
	}
	std::pair<float, float>projvals5 = ProjVerts(pol1, p1normal3);
	std::pair<float, float>projvals6 = ProjVerts(pol2, p1normal3);
	if (projvals5.first >= projvals6.second || projvals6.first >= projvals5.second) {
		return false;
	}
	std::pair<float, float>projvals7 = ProjVerts(pol1, p1normal4);
	std::pair<float, float>projvals8 = ProjVerts(pol2, p1normal4);
	if (projvals7.first >= projvals8.second || projvals8.first >= projvals7.second) {
		return false;
	}


	std::pair<float, float>projvals9 = ProjVerts(pol1, p2normal1);
	std::pair<float, float>projvals10 = ProjVerts(pol2, p2normal1);
	if (projvals9.first >= projvals10.second || projvals10.first >= projvals9.second) {
		return false;
	}
	std::pair<float, float>projvals11 = ProjVerts(pol1, p2normal2);
	std::pair<float, float>projvals12 = ProjVerts(pol2, p2normal2);
	if (projvals11.first >= projvals12.second || projvals12.first >= projvals11.second) {
		return false;
	}
	std::pair<float, float>projvals13 = ProjVerts(pol1, p2normal3);
	std::pair<float, float>projvals14 = ProjVerts(pol2, p2normal3);
	if (projvals13.first >= projvals14.second || projvals14.first >= projvals13.second) {
		return false;
	}
	std::pair<float, float>projvals15 = ProjVerts(pol1, p2normal4);
	std::pair<float, float>projvals16 = ProjVerts(pol2, p2normal4);
	if (projvals15.first >= projvals16.second || projvals16.first >= projvals15.second) {
		return false;
	}
	
	return true;

}



void Game::Run() {
	glfwInit();
	if (!glfwInit()) {
		std::cout << "GLFW could not be initialized" << std::endl;		
	}
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	window = glfwCreateWindow(w_width, w_length, "V", NULL, NULL);
	if (window == nullptr) {
		std::cout << "Window could not be instatiated" << std::endl;
	}	
	glfwMakeContextCurrent(window);
	gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
	glViewport(0, 0, w_width, w_length);

	std::cout << glGetString(GL_VERSION) << std::endl;

	// ScreenText Properties Initialization
	glEnable(GL_DEPTH_TEST);

	// Screen Text Shader
	/*std::string screenVS = ShaderStream::ReadShaderSource("screenTextShader.vert");
	std::string screenFS = ShaderStream::ReadShaderSource("screenTextShader.frag");
	Shader s2;
	GLuint screenTextID = s2.Load(screenVS, screenFS);*/

	// Main Shader
	std::string vs = ShaderStream::ReadShaderSource("Shader\\shader.vert");
	std::string fs = ShaderStream::ReadShaderSource("Shader\\shader.frag");
	Shader s1;
	GLuint t = s1.Load(vs, fs);



	Renderer r1;
	//GLuint t1 = r1.rec.bufferint();

	//glm::mat4 proj = glm::perspective(45.0f, (GLfloat) w_width / w_length, 0.0f, 150.0f);
	glm::mat4 proj = glm::ortho(-800.0f, 800.0f, -600.0f, 600.0f, -1.0f, 1.0f);
	s1.setUniform(t, "Projection", proj);
	s1.setUniform(t, "Transform", glm::mat4(1.0f));
	
	glm::mat4 model = glm::mat4(1.0f);
	

	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	GLfloat deltatime = 0.0f;
	GLfloat lastframe = 0.0f;

	// Player Characteristics

	glm::vec3 pos = glm::vec3(0.0f, 1.0f, 1.0f);
	glm::vec3 axis = glm::vec3(0.0f, 0.0f, 1.0f);
	GLfloat angle = 0.0f;
	GLfloat velocity = 0.0f;
	GLfloat acceleration = 200.0f;
	bool Engine = false;

	GLfloat refangle = angle;

	// Planet in Background

	Planet bgPlanet(glm::vec3(-450.0f, 250.0f, 1.0f));


	//Bullet Characteristics
	std::vector<Bullet*>barr{};
	bool bulletstat = true;



	// Asteroids

	Asteroids* Ast1 = new Asteroids;
	Asteroids* Ast2 = new Asteroids;
	Asteroids* Ast3 = new Asteroids;
	Asteroids* Ast4 = new Asteroids;
	/*ast3, ast4;*/

	std::vector<Asteroids*>arr{ Ast1, Ast2, Ast3, Ast4 };

	//Create 28 Asteroid Objects initially
	//When impact, 
	
	std::vector<Asteroids*>arr1;
	for (int i = 0; i < 28; i++) {
		arr1.push_back(new Asteroids);
	}


	//Asteroids arr[4]{ Ast1, Ast2 };

	bool AstHit = false;
	std::vector<int>AstStack;

	//GLuint t2 = testAst.a1.bufferint();
	/*glm::vec3 a1pos = glm::vec3(10.0f, 10.0f, 1.0f);
	glm::vec3 a1size = glm::vec3(10.0f, 10.0f, 1.0f);*/

	// IrrKlang
	irrklang::ISoundEngine* SoundEngine = irrklang::createIrrKlangDevice();
	SoundEngine->play2D(".\\Assets\\breakout.wav", true);

	//PlaySound(".\\Assets\\breakout.wav", NULL, SND_ASYNC | SND_FILENAME | SND_LOOP);

	
	while (!glfwWindowShouldClose(window)) {
		if (glfwGetCurrentContext() == NULL) { std::cout << "Window out of scope" << std::endl; }

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		//Delta time
		GLfloat currenttime = glfwGetTime();
		deltatime = currenttime - lastframe;
		lastframe = currenttime;

		//std::cout << "Deltatime: " << deltatime << std::endl;

		//Input 
		
		if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
			/*pos.y += (velocity * deltatime * cos(angle));
			pos.x += (velocity * deltatime * -sin(angle));*/
			if (velocity < 800.0f) {
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

	/*	std::vector<glm::vec2>player_vert_coords;
		glm::vec2 TR = glm::vec2((pos.x + (25 * cos(angle)) - (50 * sin(angle))), (pos.y + (25 * sin(angle)) + (50 * cos(angle))));
		glm::vec2 TL = glm::vec2((pos.x - (25 * cos(angle)) - (50 * sin(angle))), (pos.y - (25 * sin(angle)) + (50 * cos(angle))));
		glm::vec2 BL = glm::vec2((pos.x - (25 * cos(angle)) + (50 * sin(angle))), (pos.y - (25 * sin(angle)) - (50 * cos(angle))));
		glm::vec2 BR = glm::vec2((pos.x + (25 * cos(angle)) + (50 * sin(angle))), (pos.y + (25 * sin(angle)) - (50 * cos(angle))));
		player_vert_coords.push_back(TR);
		player_vert_coords.push_back(TL);
		player_vert_coords.push_back(BL);
		player_vert_coords.push_back(BR);*/



		/*glm::vec2 edge1 = TR - TL;
		glm::vec2 edge2 = TR - BR;
		glm::vec2 normal1 = glm::vec2(edge1.y, -edge1.x);
		glm::vec2 normal2 = glm::vec2(edge2.y, -edge2.x);*/

		

		// Have to change this up, creating texture on the go isn't it
		if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS && bulletstat == true) {
			Bullet* b1 = new Bullet(pos, angle);
			std::cout << pos.x << " " << pos.y << std::endl;
			barr.push_back(b1);
			bulletstat = false;

			// Get player coordinates every time we shoot
			// Something else also prints here, I believe bullet hit debug 
			// Declare first

			// Transferred to update constantly, doesn't make sense to update it just once

			/*std::cout << "Player Vertices: " << std::endl;

			std::cout << "Top Right: " << player_vert_coords[0][0] << " " << player_vert_coords[0][1] << std::endl;
			std::cout << "Top Left: " << player_vert_coords[1][0] << " " << player_vert_coords[1][1] << std::endl;
			std::cout << "Bottom Left: " << player_vert_coords[2][0] << " " << player_vert_coords[2][1] << std::endl;
			std::cout << "Bottom Right: " << player_vert_coords[3][0] << " " << player_vert_coords[3][1] << std::endl;*/

		}

		if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_RELEASE && bulletstat == false) {
			SoundEngine->play2D(".\\Assets\\BulletSound.wav", false);
			//PlaySound(".\\Assets\\BulletSound.wav", NULL, SND_ASYNC | SND_FILENAME);
			bulletstat = true;
		}


		if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {		 
			angle -= 2.0f * deltatime;			
			//axis.z = 1.0f;

		}
		if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {			
			angle += 2.0f * deltatime;
			//axis.z = -1.0f;

		}
		
		//Old Asteroid Spawning Test code -->IGNORE

		/*if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS) {
			ast3.astsize = arr[arr.size() - 1].astsize/2.0f;
			ast3.astpos = arr[arr.size() - 1].astpos;
			ast3.astangle = rand() % 25 + 10;
			arr.push_back(ast3);
		}*/

		//Old Asteroid Spawning Test code -->IGNORE

		
		//Collision Check	
		
		//std::cout << pos.x << std::endl;

		if (pos.x + 25.0f <= -800.0f || pos.x - 25.0f >= 800.0f) { 
			std::cout << "Collision Detected" << std::endl;
			pos.x *= -1.0f;
			

		}

		if (pos.y + 50.0f <= -600.0f || pos.y - 50.0f >= 600.0f) {
			std::cout << "Collision Detected" << std::endl;
			pos.y *= -1.0f;
			

		}


		//Bullet Check

		for (int i = 0; i < barr.size(); i++) {
			if (!barr[i]->Impact) {
				barr[i]->BulletDraw(barr[i]->b1.VAO, s1, t, deltatime);
				barr[i]->BulletCollision(arr);
			}
			if (barr[i]->Impact) {
				barr.erase(barr.begin() + i);
			}
		}	



		/* Implement SAT collision, player-based, and since we haven't done a player class, do it here
		 Vertices debug*/
		std::vector<glm::vec2>player_vert_coords;
		glm::vec2 TR = glm::vec2((pos.x + (25.0f * cos(angle)) - (50.0f * sin(angle))), (pos.y + (25.0f * sin(angle)) + (50.0f * cos(angle))));
		glm::vec2 TL = glm::vec2((pos.x - (25.0f * cos(angle)) - (50.0f * sin(angle))), (pos.y - (25.0f * sin(angle)) + (50.0f * cos(angle))));
		glm::vec2 BL = glm::vec2((pos.x - (25.0f * cos(angle)) + (50.0f * sin(angle))), (pos.y - (25.0f * sin(angle)) - (50.0f * cos(angle))));
		glm::vec2 BR = glm::vec2((pos.x + (25.0f * cos(angle)) + (50.0f * sin(angle))), (pos.y + (25.0f * sin(angle)) - (50.0f * cos(angle))));
		player_vert_coords.push_back(TR);
		player_vert_coords.push_back(TL);
		player_vert_coords.push_back(BL); 
		player_vert_coords.push_back(BR);

		glm::vec2 edge1 = TL - TR;
		glm::vec2 edge2 = BL - TL;
		glm::vec2 edge3 = BR - BL;
		glm::vec2 edge4 = TR - BR;
		glm::vec2 normal1 = glm::vec2(edge1.y, -edge1.x);
		glm::vec2 normal2 = glm::vec2(edge2.y, -edge2.x);
		glm::vec2 normal3 = glm::vec2(edge3.y, -edge3.x);
		glm::vec2 normal4 = glm::vec2(edge4.y, -edge4.x);


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
			arr[i]->AsteroidDraw(arr[i]->a1.VAO, s1, t, deltatime);
			arr[i]->AsteroidCollisionCheck();		

			/*bool firstOverlap = false, secondOverlap = false;
			float minA = FLT_MAX;
			float maxA = FLT_MIN;*/

			std::vector<glm::vec2>p_ast_collision = arr[i]->VertexPos();


			// Grab vertices of both asteroid and ship
			// Find normals of ship first, then project both ship and asteroid vertices onto both axes, find max and min proj in both
			// Find normals of asteroid, project both ship and asteroid vertices onto both axes, find max and min proj in both
			// If firstoverlap and secondOverlap are both true, then there is collision
			// if firstOverlap is false, break procedure
		

			if (SeperatingAxisCollision(player_vert_coords, p_ast_collision, normal1, normal2, normal3, normal4)) { std::cout << "Collision" << std::endl; }
			
		}
		
		// Render Text
		bgPlanet.draw(s1, t, deltatime);



		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	glfwTerminate();

}


