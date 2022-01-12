#pragma once
#include "Utility.h"

class Bullet
{
private:
	sf::Sprite sprite;
	//sf::Texture texture;
	//sf::CircleShape ball;
	float speed;
	sf::Vector2f direction;
public:
	Bullet(sf::Texture* ,const float x_pos, const float y_pos, float x_dir,float y_dir);
	void render(sf::RenderWindow& target);
	void update();
	sf::Vector2f getPosition();
	const sf::FloatRect& getBounds() const;
	const sf::Sprite& getSprite();

};

