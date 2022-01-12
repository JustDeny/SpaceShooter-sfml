#pragma once
#include "Utility.h"
#include "Player.h"
#include "Bullet.h"
#include "Enemy.h"
#include "Explosion.h"
#include "Bonuses.h"



class GameLoop
{
private:
	//window
	sf::RenderWindow* window;
	float time;
	//resources
	std::map<std::string, sf::Texture*> textures;
	//enemies
	float spawnTimer;
	float spawnTimerMax;
	std::vector<Enemy*> enemies;
	//player
	Player* player;
	std::vector<Bullet*> bullets;
	void initWindow();
	void initPlayer();
	void initEnemies();
	void initTextures();
	void initBackground();
	void initSystem();
	void initGUI();
	//background
	sf::Sprite background1;
	sf::Sprite background2;
	//GUI
	sf::Font font;
	sf::Text points;
	//System
	size_t countPoints;
	sf::RectangleShape playerHpBar;
	sf::RectangleShape playerMaxHpBar;
	std::vector<Explosion*> explosions;
	//bonuses
	float bonusTimer = 0;
	AidKit *hpBonus = nullptr;
	Armor* armorBonus = nullptr;
public:
	GameLoop(sf::RenderWindow* window);
	~GameLoop();
	void Run();
	void updatePollEvents();
	void updateInput();
	void updateBackground();
	void updateBullets();
	void updateEnemies();
	void updatePlayerCollision();
	void updateGUI();
	void updateExplosion();
	void updateBonuses();
	void Update();
	void Render();
	void Reset();
};