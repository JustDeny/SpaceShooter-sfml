#pragma once
#include "Utility.h"
#include "Bullet.h"
#include "Player.h"
class Enemy
{
private:
	int type;
	int points;
	int hp;
	int hpMax;
	int damage;
	float speed;
	float timer;
	sf::Sprite sprite;
	sf::Texture *bullet_texture;
	sf::CircleShape bounds;
	std::vector<Bullet*> enemy_bullets;

public:
	Enemy(const sf::Texture* texture, sf::Texture* bullet, float x_pos, float y_pos);
	~Enemy();
	void initValues();
	void render(sf::RenderWindow& target);
	void update(Player* player);
	const sf::CircleShape& getBounds();
	const sf::Sprite& getSprite();
	int getDamage();
	void makeShot();
};

