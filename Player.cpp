#include "Player.h"
#include <iostream>

void Player::initTexture()
{
	if (!this->texture.loadFromFile("textures\\ship.png"))
	{
		std::cerr << "ERROR. initTexture() could not load texture file\n";
	}
	texture.setSmooth(true);
}

void Player::initSprite()
{
	this->sprite.setTexture(this->texture);
	this->sprite.scale(0.2f, 0.2f);
	movementSpeed = 80.f;
}

Player::Player():
	bounds(45, 3)
{
	this->initTexture();
	this->initSprite();
	attackCooldownMax = 10.f;
	attackCooldown = attackCooldownMax;
	hpMax = 100;
	hp = 100;
	bounds.setScale(1.2f, 1.2f);
	armorBonusTimer = 0.0;
}

Player::~Player()
{
}

void Player::render(sf::RenderWindow& target)
{
	target.draw(this->sprite);
}

void Player::update()
{
	this->updateAtack();
	if (armorBonusTimer)
		armorBonusTimer -= 0.1;
	if (armorBonusTimer <= 0)
	{
		hasArmor = false;
		sprite.setColor(sf::Color::White);
	}
}

void Player::updateAtack()
{
	if (attackCooldown < attackCooldownMax)
		attackCooldown += 0.5f;
}

void Player::move(const float x_dir, const float y_dir)
{
	sprite.move(this->movementSpeed * x_dir, this->movementSpeed * y_dir);
	this->bounds.move(this->movementSpeed * x_dir, this->movementSpeed * y_dir);
}

bool Player::canAttack()
{
	if (this->attackCooldown >= this->attackCooldownMax)
	{
		this->attackCooldown = 0.f;
		return true;
	}
	return false;
}

void Player::setPosition(float x_pos, float y_pos)
{
	sprite.setPosition(x_pos, y_pos);
	this->bounds.setPosition(x_pos-2, y_pos+10);
}

const sf::Vector2f& Player::getPosition() const
{
	return this->sprite.getPosition();
}

const sf::Sprite& Player::getSprite() const
{
	return sprite;
}

const sf::CircleShape& Player::getBounds() const
{
	return bounds;
}

int Player::getHp()
{
	return hp;
}

int Player::getHpMax()
{
	return hpMax;
}

void Player::setHp(size_t hp)
{
	if(!hasArmor)
		this->hp = hp;
}

float Player::getArmorTimer()
{
	return armorBonusTimer;
}

void Player::setArmorTimer(float time)
{
	armorBonusTimer = time;
	hasArmor = true;
	this->sprite.setColor(sf::Color(102, 204, 102));
}
