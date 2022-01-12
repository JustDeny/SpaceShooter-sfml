#include "Bullet.h"



Bullet::Bullet(sf::Texture* texture, float x_pos, float y_pos, float x_dir, float y_dir)
{
	sprite.setTexture(*texture);
	sprite.setPosition(x_pos+34, y_pos);
	sprite.setScale(0.2f, 0.2f);
	direction.x = x_dir;
	direction.y = y_dir;
	speed = 40.f;
	//94, 150,68,106
}

void Bullet::render(sf::RenderWindow& target)
{
	target.draw(sprite);
}

void Bullet::update()
{
	sprite.move(direction.x, direction.y * speed);
}

sf::Vector2f Bullet::getPosition()
{
	return sprite.getPosition();
}

const sf::FloatRect& Bullet::getBounds()const
{
	return this->sprite.getGlobalBounds();
}

const sf::Sprite& Bullet::getSprite()
{
	return sprite;
}
