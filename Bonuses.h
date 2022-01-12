#pragma once
#include "Utility.h"
class AidKit
{
private:
	const int bonusHp = 15;
	sf::Sprite sprite;
public:
	AidKit(sf::Texture* texture, float x_pos, float y_pos);
	void update();
	void render(sf::RenderWindow& target);
	int getHp();
	sf::Sprite& getSprite();
};

class Armor
{
private:
	sf::Sprite sprite;
public:
	Armor(sf::Texture* texture, float x_pos, float y_pos);
	void update();
	void render(sf::RenderWindow& target);
	sf::Sprite& getSprite();
};

