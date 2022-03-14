#pragma once
#include "../Shader/Shader.h"
#include "../Renderer/Renderer.h"
#include "../Asteroids/Asteroids.h"
#include "../Bullet/Bullet.h"
#include "../SpaceObjects/Planet.h"
#include "../ShipLives/ShipLives.h"
#include "../Enemy/Enemy.h"
#include "../StateScreens/endGame.h"
#include "../StateScreens/menuGame.h"
#include "../Shapes/Shapes.h"
#include "../Shader/ShaderStream.h"
#include "../Physics/Physics.h"
#include "../ResourceManager/ResourceManager.h"
#include "../Components/Components.h"
#include "../Systems/MoveSystem.h"
#include "../Systems/AABBCollision.h"
#include "../Systems/SATCollision.h"
#include "../Systems/GameOver.h"
#include "../Systems/respawnSystem.h"
#include <ctime>
#include <vector>
#include <Irrklang/irrKlang.h>
#include <iostream>
#include <entt/entt.hpp>
class GameState
{
public:
	virtual ~GameState() = default;
	virtual GameState* transitionState() = 0;
	virtual void stateRun(GLFWwindow* window, float deltatime, irrklang::ISoundEngine* SoundEngine, Shader s1, GLuint t) = 0;
	virtual void setup(irrklang::ISoundEngine* SoundEngine) = 0;
	
};

class overState;

class playState: public GameState
{
public:
	playState(irrklang::ISoundEngine* SoundEngine);
	~playState();
	
	GameState* transitionState() override;
	void stateRun(GLFWwindow* window, float deltatime, irrklang::ISoundEngine* SoundEngine, Shader s1, GLuint t) override;
	void setup(irrklang::ISoundEngine* SoundEngine) override;

	void resetGame();

private:
	Renderer* r1 = nullptr;
	//ResourceManager* m_resourcemanager = nullptr;
	std::vector<ShipLives>shiphearts;
	int livesLeft{};	

	std::vector<Bullet*>barr{};
	bool bulletstat = true;

	std::vector<Asteroids*>arr;
	std::vector<Asteroids*>s2_arr;
	std::vector<Asteroids*>s3_arr;
	bool AstHit = false;
	bool stageTwo = true;
	bool stageThree = false;

	endGame* endgame = nullptr;
	bool isgameover = false;

	std::vector<Enemy*>enemyAI;
	std::vector<Bullet*>enemybarr;
	std::clock_t enemyTime{};
	bool enemyActive = false, oneEnemy = true, enemyinRange = false;

	Planet* bgPlanet = nullptr;

	irrklang::ISoundEngine* playSoundEngine = nullptr;
	irrklang::ISoundSource* bgMusic = nullptr;
	irrklang::ISoundSource* shipExplosionMusic = nullptr;
	//irrklang::ISoundSource* shipEngineMusic = SoundEngine->addSoundSourceFromFile(".\\Assets\\shipEngineSound.wav");
	irrklang::ISoundSource* gameoverMusic = nullptr;
	irrklang::ISound* m_bgMusic = nullptr;

	GameState* changeState = nullptr;
	static int deathCounter;

};

class ecsPlayState: public GameState
{
public:
	ecsPlayState(irrklang::ISoundEngine* SoundEngine);
	~ecsPlayState() = default;

	GameState* transitionState() override;
	void stateRun(GLFWwindow* window, float deltatime, irrklang::ISoundEngine* SoundEngine, Shader s1, GLuint t) override;
	void inputPolling(GLFWwindow* window, entt::registry& m_registry, float dt);
	void setup(irrklang::ISoundEngine* SoundEngine) override;
	//void resetGame();

private:
	entt::registry m_registry;
	entt::dispatcher m_dispatcher;
	MoveSystem m_moveSystem;
	AABBCollision m_AABBCollision;
	SATCollision m_SATCollision;
	GameOver m_gameover;
	respawnSystem m_respawnSystem;
	//ResourceManager* m_resourcemanager = nullptr;
	std::vector<entt::entity>shiphearts;
	int livesLeft{};
	std::clock_t respawnTimer{};
	bool gameactive = false;


	std::vector<Bullet*>barr{};
	bool bulletstat = true;
	bool respawnInvincibility = false;
	std::vector<Asteroids*>arr;
	std::vector<Asteroids*>s2_arr;
	std::vector<Asteroids*>s3_arr;
	bool AstHit = false;
	bool stageTwo = true;
	bool stageThree = false;

	endGame* endgame = nullptr;
	bool isgameover = false;

	std::vector<Enemy*>enemyAI;
	std::vector<Bullet*>enemybarr;
	std::clock_t enemyTime{};
	bool enemyActive = false, oneEnemy = true, enemyinRange = false;

	Planet* bgPlanet = nullptr;

	irrklang::ISoundEngine* playSoundEngine = nullptr;
	irrklang::ISoundSource* bgMusic = nullptr;
	irrklang::ISoundSource* shipExplosionMusic = nullptr;
	//irrklang::ISoundSource* shipEngineMusic = SoundEngine->addSoundSourceFromFile(".\\Assets\\shipEngineSound.wav");
	irrklang::ISoundSource* gameoverMusic = nullptr;
	irrklang::ISound* m_bgMusic = nullptr;

	GameState* changeState = nullptr;
	static int deathCounter;


};

class menuState : public GameState
{
public:
	menuState(irrklang::ISoundEngine* SoundEngine, ecsPlayState &ps);
	~menuState() = default;

	GameState* transitionState() override;
	void stateRun(GLFWwindow* window, float deltatime, irrklang::ISoundEngine* SoundEngine, Shader s1, GLuint t) override;
	void setup(irrklang::ISoundEngine* SoundEngine) override;

private:
	irrklang::ISoundSource* menuMusic = nullptr;
	ecsPlayState &m_playState;
	GameState* changeState = nullptr;

	menuGame* introScreen = nullptr;
	
};

class overState : public GameState
{
public:
	overState(irrklang::ISoundEngine* SoundEngine, playState& ps);
	~overState() = default;

	GameState* transitionState() override;
	void stateRun(GLFWwindow* window, float deltatime, irrklang::ISoundEngine* SoundEngine, Shader s1, GLuint t) override;
	void setup(irrklang::ISoundEngine* SoundEngine) override;

private:
	irrklang::ISoundSource* menuMusic = nullptr;
	playState& m_playState;
	GameState* changeState = nullptr;

	endGame* m_endgame = nullptr;

};