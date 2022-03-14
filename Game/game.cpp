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

	// Main Shader
	std::string vs = ShaderStream::ReadShaderSource("Shader\\shader.vert");
	std::string fs = ShaderStream::ReadShaderSource("Shader\\shader.frag");
	t = s1.Load(vs, fs);

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
	irrklang::ISoundEngine* SoundEngine = irrklang::createIrrKlangDevice();
	ecsPlayState playGame(SoundEngine);

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



		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	glfwTerminate();

}


