#include "game.h"

Game::Game() 
{
	/*state = new playState;*/
}
Game::~Game(){}

void Game::Init()
{
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
	t = s1.Load(vs, fs);

	//glm::mat4 proj = glm::perspective(45.0f, (GLfloat) w_width / w_length, 0.0f, 150.0f);
	glm::mat4 proj = glm::ortho(-800.0f, 800.0f, -600.0f, 600.0f, -1.0f, 1.0f);
	s1.setUniform(t, "Projection", proj);
	s1.setUniform(t, "Transform", glm::mat4(1.0f));

	glm::mat4 model = glm::mat4(1.0f);


	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	deltatime = 0.0f;
	lastframe = 0.0f;

}


void Game::Run() {
	
	Init();

	

	//// Player
	//Renderer* r1 = new Renderer;

	//// Ship Lives Render
	//std::vector<ShipLives>shiphearts;
	//float shiphx = 800.0f, shiphy = 500.0f;
	//ShipLives heart1(glm::vec3{ shiphx-=60.0f, shiphy, 0.0f });
	//ShipLives heart2(glm::vec3{ shiphx-=60.0f, shiphy, 0.0f });
	//ShipLives heart3(glm::vec3{ shiphx-=60.0f, shiphy, 0.0f });
	//ShipLives heart4(glm::vec3{ shiphx-=60.0f, shiphy, 0.0f });

	//shiphearts.push_back(heart1);
	//shiphearts.push_back(heart2);
	//shiphearts.push_back(heart3);
	//shiphearts.push_back(heart4);

	//int livesLeft = shiphearts.size();

	//// Player Characteristics



	//// Enemy Characteristics
	//Enemy* enemy1 = new Enemy(glm::vec3{ -850.0f, 0.0f, 0.0f });
	//std::vector<Enemy*>enemyAI{ enemy1 };
	//std::vector<Bullet*>enemybarr;
	//std::clock_t enemyTime = std::clock();
	//bool enemyActive = false, oneEnemy = true;

	//// Planet in Background

	//Planet bgPlanet(glm::vec3(-450.0f, 250.0f, 1.0f));


	////Bullet Characteristics
	//std::vector<Bullet*>barr{};
	//bool bulletstat = true;
	//std::clock_t charge;


	//// Asteroids

	//Asteroids* Ast1 = new Asteroids;
	//Asteroids* Ast2 = new Asteroids;
	//Asteroids* Ast3 = new Asteroids;
	//Asteroids* Ast4 = new Asteroids;
	///*ast3, ast4;*/

	//std::vector<Asteroids*>arr{ Ast1, Ast2, Ast3, Ast4 };
	//std::vector<Asteroids*>s2_arr;
	//std::vector<Asteroids*>s3_arr;
	//for (int i = 0; i <  6; i++)
	//{
	//	Asteroids* stageTwo = new Asteroids;
	//	s2_arr.push_back(stageTwo);
	//}
	//for (int i = 0; i < 8; i++)
	//{
	//	Asteroids* stageThree = new Asteroids;
	//	s3_arr.push_back(stageThree);
	//}

	//// Stage Checks
	//bool stageTwo = true;
	//bool stageThree = false;
	////Create 28 Asteroid Objects initially
	////When impact, 
	//
	//std::vector<Asteroids*>arr1;
	//for (int i = 0; i < 28; i++) {
	//	arr1.push_back(new Asteroids);
	//}


	////Asteroids arr[4]{ Ast1, Ast2 };

	//bool AstHit = false;
	//std::vector<int>AstStack;

	////GLuint t2 = testAst.a1.bufferint();
	///*glm::vec3 a1pos = glm::vec3(10.0f, 10.0f, 1.0f);
	//glm::vec3 a1size = glm::vec3(10.0f, 10.0f, 1.0f);*/

	//// IrrKlang
	irrklang::ISoundEngine* SoundEngine = irrklang::createIrrKlangDevice();
	//irrklang::ISoundSource* bgMusic = SoundEngine->addSoundSourceFromFile(".\\Assets\\breakout.wav");
	//irrklang::ISoundSource* shipExplosionMusic = SoundEngine->addSoundSourceFromFile(".\\Assets\\ShipExplosion.mp3");
	////irrklang::ISoundSource* shipEngineMusic = SoundEngine->addSoundSourceFromFile(".\\Assets\\shipEngineSound.wav");
	//irrklang::ISoundSource* gameoverMusic = SoundEngine->addSoundSourceFromFile(".\\Assets\\GameOverMusic.wav");
	//irrklang::ISound* m_bgMusic = SoundEngine->play2D(bgMusic, true, false, true);
	////irrklang::ISound* m_shipEngineMusic = SoundEngine->play2D(shipEngineMusic, false, false, true);
	//
	playState playGame(SoundEngine);


	////PlaySound(".\\Assets\\breakout.wav", NULL, SND_ASYNC | SND_FILENAME | SND_LOOP);

	//endGame endgame;
	//bool isgameover = false;
	menuState menuGame(SoundEngine, playGame);
	state = &menuGame;

	while (!glfwWindowShouldClose(window)) {
		if (glfwGetCurrentContext() == NULL) { std::cout << "Window out of scope" << std::endl; }

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		//Delta time
		GLfloat currenttime = glfwGetTime();
		deltatime = currenttime - lastframe;
		lastframe = currenttime;

		state->stateRun(window, deltatime, SoundEngine, s1, t);

		if(state->transitionState() != nullptr)
		{
			std::cout << "Menu to Game" << std::endl;
			state = state->transitionState();
		}

		//std::cout << "Deltatime: " << deltatime << std::endl;

		//Input 
		
	//	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
	//		/*pos.y += (velocity * deltatime * cos(angle));
	//		pos.x += (velocity * deltatime * -sin(angle));*/

	//		if (r1->velocity < 800.0f) {
	//			r1->velocity += (r1->acceleration * deltatime);
	//		}					
	//		r1->pos.y += (r1->velocity * deltatime * cos(r1->angle));
	//		r1->pos.x += (r1->velocity * deltatime * -sin(r1->angle));					
	//		r1->refangle = r1->angle;
	//		
	//	}

	//	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_RELEASE) {       
	//		if (r1->velocity > 0.0f) {
	//			r1->velocity -= (0.99999*r1->velocity*deltatime);							
	//			r1->pos.y += (r1->velocity * deltatime * cos(r1->refangle));
	//			r1->pos.x += (r1->velocity * deltatime * -sin(r1->refangle));
	//		}						
	//		
	//	}

	///*	std::vector<glm::vec2>player_vert_coords;
	//	glm::vec2 TR = glm::vec2((pos.x + (25 * cos(angle)) - (50 * sin(angle))), (pos.y + (25 * sin(angle)) + (50 * cos(angle))));
	//	glm::vec2 TL = glm::vec2((pos.x - (25 * cos(angle)) - (50 * sin(angle))), (pos.y - (25 * sin(angle)) + (50 * cos(angle))));
	//	glm::vec2 BL = glm::vec2((pos.x - (25 * cos(angle)) + (50 * sin(angle))), (pos.y - (25 * sin(angle)) - (50 * cos(angle))));
	//	glm::vec2 BR = glm::vec2((pos.x + (25 * cos(angle)) + (50 * sin(angle))), (pos.y + (25 * sin(angle)) - (50 * cos(angle))));
	//	player_vert_coords.push_back(TR);
	//	player_vert_coords.push_back(TL);
	//	player_vert_coords.push_back(BL);
	//	player_vert_coords.push_back(BR);*/



	//	/*glm::vec2 edge1 = TR - TL;
	//	glm::vec2 edge2 = TR - BR;
	//	glm::vec2 normal1 = glm::vec2(edge1.y, -edge1.x);
	//	glm::vec2 normal2 = glm::vec2(edge2.y, -edge2.x);*/

	//	

	//	// Have to change this up, creating texture on the go isn't it
	//	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS && bulletstat == true) {
	//		Bullet* b1 = new Bullet(r1->pos, r1->angle);
	//		std::cout << r1->pos.x << " " << r1->pos.y << std::endl;
	//		barr.push_back(b1);
	//		SoundEngine->play2D(".\\Assets\\BulletSound.wav", false);
	//		bulletstat = false;
	//		// Get player coordinates every time we shoot
	//		// Something else also prints here, I believe bullet hit debug 
	//		// Declare first

	//		// Transferred to update constantly, doesn't make sense to update it just once

	//		/*std::cout << "Player Vertices: " << std::endl;

	//		std::cout << "Top Right: " << player_vert_coords[0][0] << " " << player_vert_coords[0][1] << std::endl;
	//		std::cout << "Top Left: " << player_vert_coords[1][0] << " " << player_vert_coords[1][1] << std::endl;
	//		std::cout << "Bottom Left: " << player_vert_coords[2][0] << " " << player_vert_coords[2][1] << std::endl;
	//		std::cout << "Bottom Right: " << player_vert_coords[3][0] << " " << player_vert_coords[3][1] << std::endl;*/

	//	}

	//	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_RELEASE && bulletstat == false) {
	//		//PlaySound(".\\Assets\\BulletSound.wav", NULL, SND_ASYNC | SND_FILENAME);
	//		bulletstat = true;
	//	}


	//	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
	//		r1->angle -= 4.0f * deltatime;			
	//		//axis.z = 1.0f;
	//	}

	//	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
	//		r1->angle += 4.0f * deltatime;
	//		//axis.z = -1.0f;
	//	}

	//	//Old Asteroid Spawning Test code -->IGNORE

	//	/*if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS) {
	//		ast3.astsize = arr[arr.size() - 1].astsize/2.0f;
	//		ast3.astpos = arr[arr.size() - 1].astpos;
	//		ast3.astangle = rand() % 25 + 10;
	//		arr.push_back(ast3);
	//	}*/

	//	//Old Asteroid Spawning Test code -->IGNORE

	//	
	//	//Collision Check	
	//	
	//	//std::cout << pos.x << std::endl;

	//	if (r1->pos.x + 25.0f <= -800.0f || r1->pos.x - 25.0f >= 800.0f) { 
	//		std::cout << "Collision Detected" << std::endl;
	//		r1->pos.x *= -1.0f;
	//		

	//	}

	//	if (r1->pos.y + 50.0f <= -600.0f || r1->pos.y - 50.0f >= 600.0f) {
	//		std::cout << "Collision Detected" << std::endl;
	//		r1->pos.y *= -1.0f;
	//		

	//	}

	//	//Bullet Check

	//	for (int i = 0; i < barr.size(); i++) {
	//		if (!barr[i]->isImpact()) {
	//			barr[i]->BulletDraw(s1, t, deltatime);
	//			barr[i]->BulletCollision(arr);
	//		}
	//		if (barr[i]->isImpact()) {
	//			SoundEngine->play2D(".\\Assets\\BulletAstImpact.wav", false);
	//			delete barr[i];
	//			barr.erase(barr.begin() + i);
	//			continue;
	//		}
	//		if (std::fabs(barr[i]->getogpos().x - barr[i]->getcurrentPos().x) >= 800.0f || std::fabs(barr[i]->getogpos().y - barr[i]->getcurrentPos().y) >= 800.0f)
	//		{
	//			delete barr[i];
	//			barr.erase(barr.begin() + i);
	//		}

	//	}	



	//	/* Implement SAT collision, player-based, and since we haven't done a player class, do it here
	//	 Vertices debug*/
	//	std::vector<glm::vec2>player_vert_coords;
	//	glm::vec2 TR = glm::vec2((r1->pos.x + (25.0f * cos(r1->angle)) - (50.0f * sin(r1->angle))), (r1->pos.y + (25.0f * sin(r1->angle)) + (50.0f * cos(r1->angle))));
	//	glm::vec2 TL = glm::vec2((r1->pos.x - (25.0f * cos(r1->angle)) - (50.0f * sin(r1->angle))), (r1->pos.y - (25.0f * sin(r1->angle)) + (50.0f * cos(r1->angle))));
	//	glm::vec2 BL = glm::vec2((r1->pos.x - (25.0f * cos(r1->angle)) + (50.0f * sin(r1->angle))), (r1->pos.y - (25.0f * sin(r1->angle)) - (50.0f * cos(r1->angle))));
	//	glm::vec2 BR = glm::vec2((r1->pos.x + (25.0f * cos(r1->angle)) + (50.0f * sin(r1->angle))), (r1->pos.y + (25.0f * sin(r1->angle)) - (50.0f * cos(r1->angle))));
	//	player_vert_coords.push_back(TR);
	//	player_vert_coords.push_back(TL);
	//	player_vert_coords.push_back(BL); 
	//	player_vert_coords.push_back(BR);

	//	glm::vec2 edge1 = TL - TR;
	//	glm::vec2 edge2 = BL - TL;
	//	glm::vec2 edge3 = BR - BL;
	//	glm::vec2 edge4 = TR - BR;
	//	glm::vec2 normal1 = glm::vec2(edge1.y, -edge1.x);
	//	glm::vec2 normal2 = glm::vec2(edge2.y, -edge2.x);
	//	glm::vec2 normal3 = glm::vec2(edge3.y, -edge3.x);
	//	glm::vec2 normal4 = glm::vec2(edge4.y, -edge4.x);


	//	/*if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
	//		model = glm::translate(model, glm::vec3(0.0f, -0.01f, 0.0f));
	//		s1.setUniform(t, "Transform", model);
	//	}*/


	//	/*for (int i = 0; i < 9; i++) {
	//		std::cout << r1->rec.quad_verts[i] << " ";
	//	}
	//	std::cout << std::endl;*/
	//	r1->Draw(s1, t);
	//	
	//	// Asteroid renderer

	//	for (int i = 0; i < arr.size(); i++) {
	//		arr[i]->AsteroidDraw(s1, t, deltatime);
	//		arr[i]->AsteroidCollisionCheck();		

	//		/*bool firstOverlap = false, secondOverlap = false;
	//		float minA = FLT_MAX;
	//		float maxA = FLT_MIN;*/

	//		std::vector<glm::vec2>p_ast_collision = arr[i]->VertexPos();


	//		// Grab vertices of both asteroid and ship
	//		// Find normals of ship first, then project both ship and asteroid vertices onto both axes, find max and min proj in both
	//		// Find normals of asteroid, project both ship and asteroid vertices onto both axes, find max and min proj in both
	//		// If firstoverlap and secondOverlap are both true, then there is collision
	//		// if firstOverlap is false, break procedure
	//	

	//		if (SeperatingAxisCollision(player_vert_coords, p_ast_collision, normal1, normal2, normal3, normal4) && !r1->respawnInvincibility) 
	//		{ 
	//			livesLeft -= 1;
	//			SoundEngine->play2D(shipExplosionMusic, false);
	//			m_bgMusic->setIsPaused();
	//			m_bgMusic->setPlayPosition(0);
	//			r1->Reset();
	//			std::cout << "Collision" << std::endl;
	//			r1->startTime = std::clock();
	//		}
	//		
	//	}

	//	// Spaceship flicker upon respawn, indicates invincibility
	//	if (r1->respawnInvincibility)
	//	{
	//		if (((std::clock() - r1->startTime) / ((double)CLOCKS_PER_SEC)) >= 0.0 && ((std::clock() - r1->startTime) / ((double)CLOCKS_PER_SEC)) < 0.5) { r1->pos.z = -2.0f; }
	//		else if (((std::clock() - r1->startTime) / ((double)CLOCKS_PER_SEC)) >= 0.5 && ((std::clock() - r1->startTime) / ((double)CLOCKS_PER_SEC)) < 1.0) { r1->pos.z = 1.0f; }
	//		else if (((std::clock() - r1->startTime) / ((double)CLOCKS_PER_SEC)) >= 1.0 && ((std::clock() - r1->startTime) / ((double)CLOCKS_PER_SEC)) < 1.5) { r1->pos.z = -2.0f; }
	//		else if (((std::clock() - r1->startTime) / ((double)CLOCKS_PER_SEC)) >= 1.5 && ((std::clock() - r1->startTime) / ((double)CLOCKS_PER_SEC)) < 2.0) { r1->pos.z = 1.0f; }
	//		else if (((std::clock() - r1->startTime) / ((double)CLOCKS_PER_SEC)) >= 2.0 && ((std::clock() - r1->startTime) / ((double)CLOCKS_PER_SEC)) < 2.4) { r1->pos.z = -2.0f; }
	//		else if (((std::clock() - r1->startTime) / ((double)CLOCKS_PER_SEC)) >= 2.5) { r1->respawnInvincibility = false; m_bgMusic->setIsPaused(false); r1->pos.z = 1.0f; }
	//	}
	//	// Enemy 
	//	
	//	if ((int)((std::clock() - enemyTime) / ((double)CLOCKS_PER_SEC)) % 10 == 0 && oneEnemy) { enemyActive = true; oneEnemy = false; }
	//	if (enemyActive)
	//	{
	//		for (int i = 0; i < enemyAI.size(); i++)
	//		{
	//			enemyAI[i]->draw(s1, t, deltatime);
	//			if (enemyAI[i]->arrival == false) { enemyAI[i]->checkArrival(); continue; }
	//			enemyAI[i]->collisionCheck();
	//			if (SeperatingAxisCollision(player_vert_coords, enemyAI[i]->vertexPos(), normal1, normal2, normal3, normal4) && !r1->respawnInvincibility)
	//			{
	//				enemyActive = false;
	//				enemyTime = std::clock();
	//				delete enemyAI[i];
	//				enemyAI.erase(enemyAI.begin() + i);
	//				oneEnemy = true;
	//				break;
	//			}
	//			for (int j = 0; j < enemybarr.size(); j++) 
	//			{
	//				enemybarr[j]->BulletDraw(s1, t, deltatime); 
	//				enemybarr[j]->BulletCollision(arr);
	//				if (enemybarr[j]->isImpact()) { enemybarr.erase(enemybarr.begin() + j); }
	//			}
	//		}

	//	}


	//	// Render Hearts
	//	for (int h = 0; h < livesLeft; h++)
	//	{
	//		shiphearts[h].draw(s1, t, deltatime);
	//	}

	//	// Level Changer

	//	if (arr.empty() && !stageThree) 
	//	{
	//		if (stageTwo) { arr = s2_arr; stageTwo = false; }
	//		else { arr = s3_arr; stageThree = true; }
	//	
	//	}

	//	if (livesLeft <= 0 && !isgameover)
	//	{
	//		// Render game over overlay
	//		isgameover = true;			
	//		SoundEngine->play2D(gameoverMusic, false);
	//		m_bgMusic->drop();
	//	}

	//	if (isgameover)
	//	{
	//		r1->pos.z = -10.0f;
	//		endgame.draw(s1, t, deltatime);
	//	}
	//	// Render Text
	//	bgPlanet.draw(s1, t, deltatime);



		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	glfwTerminate();

}


