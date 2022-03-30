#include "GameState.h"

ecsPlayState::ecsPlayState(irrklang::ISoundEngine* SoundEngine)
{
	playSoundEngine = SoundEngine;
	// Load all resources
	const auto playerShip = m_registry.create();
	const auto ast1 = m_registry.create();
	const auto ast2 = m_registry.create();
	const auto ast3 = m_registry.create();
	const auto ast4 = m_registry.create();
	const auto bgImage = m_registry.create();
	const auto shipl1 = m_registry.create();
	const auto shipl2 = m_registry.create();
	const auto shipl3 = m_registry.create();
	const auto shipl4 = m_registry.create();
	shiphearts.push_back(shipl1);
	shiphearts.push_back(shipl2);
	shiphearts.push_back(shipl3);
	shiphearts.push_back(shipl4);
	livesLeft = shiphearts.size();
	ResourceManager::getInstance()->loadTexture("ship", ".\\Assets\\pixelSpaceShip.png");
	ResourceManager::getInstance()->loadTexture("menu", ".\\Assets\\MenuScreen.png");
	ResourceManager::getInstance()->loadTexture("asteroids", ".\\Assets\\Asteroid.png");
	ResourceManager::getInstance()->loadTexture("bullet", ".\\Assets\\fireballbullet1.png");
	ResourceManager::getInstance()->loadTexture("planet", ".\\Assets\\planet.png");
	ResourceManager::getInstance()->loadTexture("gameover", ".\\Assets\\gameoversprite.png");
	//ResourceManager::getInstance()->loadTexture("tiles", ".\\Assets\\tileset2.png");
	ResourceManager::getInstance()->loadTexture("greentile", ".\\Assets\\greentile.png");
	ResourceManager::getInstance()->loadTexture("marbletile", ".\\Assets\\marbletile.png");
	

	// Tilemap Render Component Test
	std::vector<int> tilemap{ 2,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,2,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,2,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,2 };
	
	for (int width = 0; width < 20; width++)
	{
		for (int height = 0; height < 10; height++)
		{
			int xpos = 50 * width;
			int ypos = 50 * height;
			auto tile = m_registry.create();
			if (tilemap[width * 10 + height] == 1) { m_registry.emplace<TransformComponent>(tile, glm::vec3(xpos, ypos, 1.0f), glm::vec3(50.0f, 50.0f, 1.0f), 0.0f, "marbletile"); }
			else
			{
				m_registry.emplace<TransformComponent>(tile, glm::vec3(xpos, ypos, 1.0f), glm::vec3(50.0f, 50.0f, 1.0f), 0.0f, "greentile");
			}
		}
	}



	m_registry.emplace<TransformComponent>(playerShip, glm::vec3(0.0f, 1.0f, 1.0f), glm::vec3(50.0f, 100.0f, 1.0f), 0.0f, "ship");
	m_registry.emplace<RigidBodyComponent>(playerShip, glm::vec3(0.0f, 0.0f, 0.0f));
	m_registry.emplace<PlayerComponent>(playerShip);


	float xvel = rand() % 10 + 200;
	float yvel = rand() % 10 + 200;
	m_registry.emplace<TransformComponent>(ast1, glm::vec3(-450.0f, 250.0f, 1.0f), glm::vec3(200.0f, 200.0f, 1.0f), 35.0f, "asteroids");
	m_registry.emplace<RigidBodyComponent>(ast1, glm::vec3(xvel, yvel, 0.0f));
	m_registry.emplace<AsteroidComponent>(ast1);
	m_registry.emplace<TransformComponent>(ast2, glm::vec3(450.0f, 250.0f, 1.0f), glm::vec3(200.0f, 200.0f, 1.0f), 43.0f, "asteroids");
	m_registry.emplace<RigidBodyComponent>(ast2, glm::vec3(xvel, yvel, 0.0f));
	m_registry.emplace<AsteroidComponent>(ast2);
	m_registry.emplace<TransformComponent>(ast3, glm::vec3(450.0f, -250.0f, 1.0f), glm::vec3(200.0f, 200.0f, 1.0f), 42.0f, "asteroids");
	m_registry.emplace<RigidBodyComponent>(ast3, glm::vec3(xvel, yvel, 0.0f));
	m_registry.emplace<AsteroidComponent>(ast3);
	m_registry.emplace<TransformComponent>(ast4, glm::vec3(-450.0f, -250.0f, 1.0f), glm::vec3(200.0f, 200.0f, 1.0f), 15.0f, "asteroids");
	m_registry.emplace<RigidBodyComponent>(ast4, glm::vec3(xvel, yvel, 0.0f));
	m_registry.emplace<AsteroidComponent>(ast4);

	m_registry.emplace<TransformComponent>(bgImage, glm::vec3(-450.0f, 250.0f, 0.0f), glm::vec3(300.0f, 300.0f, 1.0f), 0.0f, "planet");	

	m_registry.emplace<TransformComponent>(shipl1, glm::vec3(740.0f, 500.0f, 0.0f), glm::vec3(50.0f, 100.0f, 1.0f), 0.0f, "ship");
	m_registry.emplace<TransformComponent>(shipl2, glm::vec3(680.0f, 500.0f, 0.0f), glm::vec3(50.0f, 100.0f, 1.0f), 0.0f, "ship");
	m_registry.emplace<TransformComponent>(shipl3, glm::vec3(620.0f, 500.0f, 0.0f), glm::vec3(50.0f, 100.0f, 1.0f), 0.0f, "ship");
	m_registry.emplace<TransformComponent>(shipl4, glm::vec3(560.0f, 500.0f, 0.0f), glm::vec3(50.0f, 100.0f, 1.0f), 0.0f, "ship");


	//m_dispatcher.sink<>


	bgMusic = SoundEngine->addSoundSourceFromFile(".\\Assets\\breakout.wav");
	m_bgMusic = SoundEngine->play2D(bgMusic, true, false, true);

	//m_dispatcher.sink<>()
	
}

void ecsPlayState::inputPolling(GLFWwindow* window, entt::registry &m_registry, float dt)
{
	auto view = m_registry.view<TransformComponent, RigidBodyComponent, PlayerComponent>();
	view.each([&](auto& spr, auto& rb, auto& playerComp)
		{
			if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) 
			{
				if (playerComp.m_velocity < 800.0f /*&& rb.m_velocity.y < 800.0f*/)
				{
					playerComp.m_velocity+= (playerComp.m_acceleration * dt);
					//rb.m_velocity.y += (playerComp.m_acceleration * dt);
				}
				spr.m_pos.y += (playerComp.m_velocity * dt * cos(spr.m_angle));
				spr.m_pos.x += (playerComp.m_velocity * dt * -sin(spr.m_angle));
				playerComp.refangle = spr.m_angle;
			}

			if (glfwGetKey(window, GLFW_KEY_W) == GLFW_RELEASE) 
			{				
				if (playerComp.m_velocity > 0.0f/* && rb.m_velocity.y > 0.0f*/)
				{
					playerComp.m_velocity -= (0.99f * playerComp.m_velocity * dt);
					//rb.m_velocity.y -= (0.99999 * rb.m_velocity * dt);
					spr.m_pos.y += (playerComp.m_velocity * dt * cos(playerComp.refangle));
					spr.m_pos.x += (playerComp.m_velocity * dt * -sin(playerComp.refangle));
				}
			}
			if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS && bulletstat == true) 
			{
				const auto bullet = m_registry.create();
				m_registry.emplace<TransformComponent>(bullet, spr.m_pos, glm::vec3(20.0f, 20.0f, 1.0f), spr.m_angle, "bullet");
				m_registry.emplace<RigidBodyComponent>(bullet, glm::vec3(1500.0f, 1500.0f, 0.0f)/*1500.0f*/);
				glm::vec3 originalbpos = spr.m_pos;
				m_registry.emplace<BulletComponent>(bullet, originalbpos);
				bulletstat = false;
			}

			if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_RELEASE && bulletstat == false) 
			{
				bulletstat = true;
			}


			if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) 
			{
				spr.m_angle -= 4.0f * dt;
			}

			if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) 
			{
				spr.m_angle += 4.0f * dt;
			}


			if (glfwGetKey(window, GLFW_KEY_F) == GLFW_PRESS && isgameover) 
			{
				/*deathCounter += 1;
				std::cout << deathCounter << std::endl;
				resetGame();*/
			}
		});

}

GameState* ecsPlayState::transitionState() 
{
	if (changeState != nullptr)
	{
		return changeState;
	}
	return nullptr;
}
void ecsPlayState::stateRun(GLFWwindow* window, float deltatime, irrklang::ISoundEngine* SoundEngine, Shader s1, GLuint t) 
{
	inputPolling(window, m_registry, deltatime);
	//m_AABBCollision.update(m_registry, deltatime);
	//m_SATCollision.update(m_registry, deltatime, respawnInvincibility, isgameover, gameactive, shiphearts, respawnTimer, livesLeft);
	//m_respawnSystem.update(m_registry, deltatime, respawnTimer, respawnInvincibility);
	//m_gameover.update(m_registry, deltatime, isgameover, gameactive);
	m_moveSystem.update(m_registry, deltatime);	
	auto view = m_registry.view<TransformComponent>();
	view.each([&](const auto& spr)
		{
			glBindTexture(GL_TEXTURE_2D, spr.m_texID);
			glBindVertexArray(spr.VAO);			
			glm::mat4 model(1.0f);

			model = glm::translate(model, spr.m_pos);
			model = glm::rotate(model, spr.m_angle, glm::vec3(0.0f, 0.0f, 1.0f));
			model = glm::scale(model, spr.m_size);

			// Vertices of player

			s1.setUniform(t, "Transform", model);

			glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
			glBindVertexArray(0);

		});

}
void ecsPlayState::setup(irrklang::ISoundEngine* SoundEngine) {}