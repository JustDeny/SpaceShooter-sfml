#include "Enemy.h"

Enemy::Enemy(const sf::Texture* texture, sf::Texture* bullet, float x_pos, float y_pos) :
	bounds(35, 3),bullet_texture(bullet), sprite(*texture)
{
	sprite.setScale(1.f, 1.f);
	sprite.setPosition(x_pos, y_pos);
	bounds.setPosition(x_pos+18, y_pos+80);
	bounds.setScale(0.8f, -1.f);
	initValues();
	makeShot();
}

Enemy::~Enemy()
{
}

void Enemy::initValues()
{
	speed = 4;
	type = 0;
	hpMax = 10;
	damage = 10;
	points = 5;
	timer = 30;
}

void Enemy::render(sf::RenderWindow& target)
{
	target.draw(this->sprite);
	for (auto& bullet : enemy_bullets)
	{
		bullet->render(target);
	}
}

void Enemy::update(Player* player)
{
	sprite.move(0.f, 1.f*speed);
	bounds.move(0.f, 1.f*speed);
	unsigned int counter = 0;
	if (!enemy_bullets.empty())
	{
		for (auto& bullet : enemy_bullets)
		{
			bullet->update();
			bullet->update();
			if (bullet->getSprite().getGlobalBounds().top + bullet->getSprite().getGlobalBounds().height > 800.f)
			{
				delete this->enemy_bullets.at(counter);
				this->enemy_bullets.erase(enemy_bullets.begin() + counter);
				--counter;
			}
			if (bullet->getSprite().getGlobalBounds().intersects(player->getSprite().getGlobalBounds()))
			{
				player->setHp(player->getHp()-this->getDamage());
				enemy_bullets.erase(enemy_bullets.begin() + counter);
				--counter;
			}
			++counter;
		}
	}
	timer -= 0.5;
	if (!timer)
	{
		makeShot();
		timer = 30;
	}
}

const sf::CircleShape& Enemy::getBounds()
{
	return bounds;
}

const sf::Sprite& Enemy::getSprite()
{
	return sprite;
}

int Enemy::getDamage()
{
	return damage;
}

void Enemy::makeShot()
{
	enemy_bullets.push_back(new Bullet(bullet_texture, sprite.getPosition().x-5, 
		sprite.getPosition().y + 65, 0.f, 0.1f));
}
