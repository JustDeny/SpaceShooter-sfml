#include "GameLoop.h"

const static std::string namesOfTextures[] = { "Enemy1", "Enemy2"};

void GameLoop::initWindow()
{
	this->window->setFramerateLimit(60);
	this->window->setVerticalSyncEnabled(false);
}

void GameLoop::initPlayer()
{
	player = new Player;
	player->setPosition(window->getSize().x / 2, window->getSize().y / 2);
}

void GameLoop::initEnemies()
{
	spawnTimerMax = 65.f;
	spawnTimer = spawnTimerMax;
}

void GameLoop::initTextures()
{
	sf::Image* bullet_img = new sf::Image;
	bullet_img->loadFromFile("textures\\Bullet.png");
	bullet_img->createMaskFromColor(sf::Color(255, 255, 255));

	//player's bullets
	this->textures["Bullet"] = new sf::Texture;
	this->textures["Bullet"]->loadFromImage(*bullet_img);

	//enemy
	this->textures["Enemy1"] = new sf::Texture;
	this->textures["Enemy1"]->loadFromFile("textures\\enemy_1.png");
	this->textures["Enemy1"]->setSmooth(true);
	this->textures["enemyBullet"] = new sf::Texture;
	this->textures["enemyBullet"]->loadFromFile("textures\\enemyBullet.png");
	this->textures["enemyBullet"]->setSmooth(true);

	//background
	this->textures["Background"] = new sf::Texture;
	this->textures["Background"]->loadFromFile("textures\\background.jpg");

	//explosion
	textures["Explosion"] = new sf::Texture;
	textures["Explosion"]->loadFromFile("textures\\explosion.png");
	textures["Explosion"]->setSmooth(true);

	//bonuses
	textures["hpBonus"] = new sf::Texture;
	textures["hpBonus"]->loadFromFile("textures\\hpBonus.png");
	textures["hpBonus"]->setSmooth(true);
	textures["armorBonus"] = new sf::Texture;
	textures["armorBonus"]->loadFromFile("textures\\armorBonus.png");
	textures["armorBonus"]->setSmooth(true);

}
void GameLoop::initBackground()
{
	background1.setTexture(*textures["Background"]);
	background2.setTexture(*textures["Background"]);
	//background1.setPosition(0.f, 0.f);
	background2.setPosition(0.f, -800.f);
}
void GameLoop::initSystem()
{
	countPoints = 0;
}

void GameLoop::initGUI()
{
	font.loadFromFile("font\\font.ttf");
	std::stringstream ss;
	ss << "Points: " << countPoints;
	points.setString(ss.str());
	points.setFont(font);
	points.setScale(0.6f, 0.6f);
	points.setPosition(10.f, 10.f);
	points.setFillColor(sf::Color::White);
	playerHpBar.setSize(sf::Vector2f(player->getHpMax(), 20.f));
	playerMaxHpBar.setSize(sf::Vector2f(player->getHpMax(), 20.f));
	playerHpBar.setPosition(10.f, 50.f);
	playerMaxHpBar.setPosition(10.f, 50.f);
	playerHpBar.setFillColor(sf::Color(255, 0, 0));
	playerMaxHpBar.setFillColor(sf::Color(148, 0, 0));
}

GameLoop::GameLoop(sf::RenderWindow* window)
{
	this->window = window;
	this->initWindow();
	this->initTextures();
	this->initBackground();
	this->initPlayer();
	this->initGUI();
	this->initEnemies();
	this->initSystem();
	//this->initExplosion();
}

GameLoop::~GameLoop()
{
	//textures
	for (auto& m : textures)
	{
		delete m.second;
	}
	//bullets
	for (auto* b : bullets)
	{
		delete b;
	}
	//enemies
	for (auto* e : enemies)
	{
		delete e;
	}
}

void GameLoop::Run()
{
	while (window->isOpen())
	{
		Update();
		Render();
		if (player->getHp() <= 0)
			break;
	}
}

void GameLoop::updatePollEvents()
{
	sf::Event e;
	while (this->window->pollEvent(e))
	{
		if (e.type == sf::Event::Closed)
			this->window->close();
		if (e.type == sf::Event::KeyPressed && e.key.code == sf::Keyboard::Escape)
			this->window->close();
	}
}

void GameLoop::updateInput()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		player->move(0.f, -0.1);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		player->move(-0.1, 0.f);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		player->move(0.f, 0.1);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		player->move(0.1, 0.f);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && this->player->canAttack())
		bullets.push_back(new Bullet(textures["Bullet"], player->getPosition().x+13, player->getPosition().y,
			0.f, -0.1f));
}

void GameLoop::updateBackground()
{
	background1.move(0.f, 2.f);
	background2.move(0.f, 2.f);
	if (background1.getPosition().y >= 800)
		background1.setPosition(0.f, -800);
	if (background2.getPosition().y >= 800)
		background2.setPosition(0.f, -800);
}

void GameLoop::updateBullets()
{
	unsigned int counter = 0;
		if (!this->bullets.empty())
		{
			for (auto* bullet : bullets)
			{
				bullet->update();
				if (bullet->getBounds().top + bullet->getBounds().height < 0.f)
				{
					delete this->bullets.at(counter);
					this->bullets.erase(bullets.begin() + counter);
					--counter;
				}
				counter++;
			}
		}
}

void GameLoop::updateEnemies()
{
	spawnTimer += 0.5f;
	if (spawnTimer >= spawnTimerMax)
	{
		enemies.push_back(new Enemy(textures["Enemy1"],textures["enemyBullet"],(rand() % (1160 - 20 + 1) + 20), -40.f));
		spawnTimer = 0.f;
	}
	for (int e = 0; e < enemies.size(); e++)
	{
		bool enemy_removed = false;
		enemies[e]->update(player);
		for (int b = 0; b < bullets.size()&&!enemy_removed; b++)
		{
			if (this->bullets[b]->getSprite().getGlobalBounds().intersects(enemies[e]->getBounds().getGlobalBounds()))
			{
				explosions.push_back(new Explosion(textures["Explosion"], enemies[e]->getSprite().getPosition().x,
					enemies[e]->getSprite().getPosition().y));
				this->bullets.erase(bullets.begin()+b);
				enemies.erase(enemies.begin()+e);
				enemy_removed = true;
				++countPoints;
			}
		}
		if (!enemy_removed)
		{
			if (enemies[e]->getSprite().getGlobalBounds().top > window->getSize().y)
			{
				enemies.erase(enemies.begin()+e);
				enemy_removed = true;
				if (countPoints)
					--countPoints;
			}
			else if (enemies[e]->getSprite().getGlobalBounds().intersects(player->getBounds().getGlobalBounds()))
			{
				player->setHp(player->getHp() - enemies[e]->getDamage());
				explosions.push_back(new Explosion(textures["Explosion"], enemies[e]->getSprite().getPosition().x,
					enemies[e]->getSprite().getPosition().y));
				enemies.erase(enemies.begin() + e);
				enemy_removed = true;
				++countPoints;
			}
		}
	}
}

void GameLoop::updatePlayerCollision()
{	
	if (player->getPosition().x < 0.f)
		player->setPosition(0.f, player->getPosition().y);
	if (player->getPosition().y < 0.f)
		player->setPosition(player->getPosition().x, 0.f);
	if (player->getPosition().x > window->getSize().x - 92.f)
		player->setPosition(window->getSize().x - 92.f, player->getPosition().y);
	if (player->getPosition().y > window->getSize().y-92.f)
		player->setPosition(player->getPosition().x, window->getSize().y-92.f);
}

void GameLoop::updateGUI()
{
	std::stringstream ss;
	ss << "Points: " << countPoints;
	points.setString(ss.str());
	playerHpBar.setSize(sf::Vector2f(player->getHp(), 20.f));
}

void GameLoop::updateExplosion()
{
	if (!explosions.empty())
	{
		for (auto& exp : explosions)
		{
			exp->update();
			if (exp->isFinished())
			{
				auto found = std::find(explosions.begin(), explosions.end(), exp);
				explosions.erase(found);
			}
		}
	}
}

void GameLoop::updateBonuses()
{
	if (hpBonus)
	{
		hpBonus->update();
	}
	if (armorBonus)
	{
		armorBonus->update();
	}
	bonusTimer += 0.2;
	if (bonusTimer >= 170.f && bonusTimer < 171 && hpBonus == nullptr)
	{
		hpBonus = new AidKit(textures["hpBonus"], rand() % (1170 - 30 + 1) + 30, -10.f);
	}
	if (hpBonus && hpBonus->getSprite().getGlobalBounds().intersects(
		player->getSprite().getGlobalBounds()))
	{
		player->setHp(player->getHp()+hpBonus->getHp());
		delete hpBonus;
		hpBonus = nullptr;
	}
	if (hpBonus && hpBonus->getSprite().getGlobalBounds().top > 810.f)
	{
		delete hpBonus;
		hpBonus = nullptr;
	}
	if (bonusTimer >= 270 && armorBonus == nullptr)
	{
		armorBonus = new Armor(textures["armorBonus"], rand() % (1170 - 30 + 1) + 30, -10.f);
		bonusTimer = 0.0;
	}
	
	if (armorBonus && armorBonus->getSprite().getGlobalBounds().intersects(
		player->getSprite().getGlobalBounds()))
	{
		player->setArmorTimer(40);
		delete armorBonus;
		armorBonus = nullptr;
	}
	if (armorBonus && armorBonus->getSprite().getGlobalBounds().top > 810.f)
	{
		delete armorBonus;
		armorBonus = nullptr;
	}

}

void GameLoop::Update()
{
	this->updatePollEvents();
	this->updateInput();
	this->updateBackground();
	this->player->update();
	this->updatePlayerCollision();
	this->updateExplosion();
	this->updateBullets();
	this->updateEnemies();
	this->updateGUI();
	this->updateBonuses();

}

void GameLoop::Render()
{

	window->clear();
	window->draw(background1);
	window->draw(background2);
	player->render(*window);
	for (auto* bullet : bullets)
	{
		bullet->render(*window);
	}
	for (auto& enemy : enemies)
	{
		enemy->render(*window);
	}
	for (auto& exps : explosions)
	{
		exps->render(*window);
	}
	if(hpBonus)
		hpBonus->render(*window);
	if (armorBonus)
		armorBonus->render(*window);
	window->draw(points);
	window->draw(playerMaxHpBar);
	window->draw(playerHpBar);
	window->display();
}
void GameLoop::Reset()
{
	//player
	player->setHp(player->getHpMax());
	player->setPosition(600, 400);
	//bonuses
	bonusTimer = 0;
	//points
	countPoints = 0;
	//bullets
	if(!bullets.empty())
	for (auto* b : bullets)
	{
		delete b;
	}
	bullets.clear();
	//enemies
	if(!enemies.empty())
	for (auto* e : enemies)
	{
		delete e;
	}
	enemies.clear();
	//explosions
	explosions.clear();
}
