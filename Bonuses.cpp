#include "Bonuses.h"

AidKit::AidKit(sf::Texture *texture, float x_pos, float y_pos)
{
	sprite.setTexture(*texture);
	sprite.setPosition(x_pos, y_pos);
	sprite.setScale(0.1f, 0.1f);
}

void AidKit::update()
{
	sprite.move(0.f, 5.f);
}

void AidKit::render(sf::RenderWindow& target)
{
	target.draw(sprite);
}

int AidKit::getHp()
{
	return bonusHp;
}

sf::Sprite& AidKit::getSprite()
{
	return sprite;
}


//Armor
Armor::Armor(sf::Texture* texture, float x_pos, float y_pos)
{
	sprite.setTexture(*texture);
	sprite.setPosition(x_pos, y_pos);
	sprite.setScale(0.1f, 0.1f);
}

void Armor::update()
{
	sprite.move(0.f, 4.f);
}

void Armor::render(sf::RenderWindow& target)
{
	target.draw(sprite);
}

sf::Sprite& Armor::getSprite()
{
	return sprite;
}
