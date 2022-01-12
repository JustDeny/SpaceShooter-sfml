#pragma once
#include "Utility.h"
#include "Bullet.h"
#include <vector>
class Player
{
private:
	int hp;
	int hpMax;
	float armorBonusTimer;
	sf::Texture texture;
	sf::Sprite sprite;
	sf::CircleShape bounds;
	float movementSpeed;
	void initTexture();
	void initSprite();
	float attackCooldown;
	float attackCooldownMax;
	bool hasArmor;
public:
	Player(); 
	~Player();
	void render(sf::RenderWindow& target);
	void update();
	void updateAtack();
	void move(const float x_dir, const float y_dir);
	bool canAttack();
	void setPosition(float x_pos, float y_pos);
	const sf::Vector2f& getPosition() const;
	const sf::Sprite& getSprite() const;
	const sf::CircleShape& getBounds() const;
	int getHp();
	int getHpMax();
	void setHp(size_t hp);
	void setArmorTimer(float time);
	float getArmorTimer();
};