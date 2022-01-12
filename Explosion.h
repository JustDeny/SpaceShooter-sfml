#pragma once
#include "Utility.h"
class Explosion
{
private:
	sf::Sprite sprite;
	float currentFrame;
	int row;
	const float ANIM_DELAY = 0.01;
	sf::Clock animClock;
	bool finished;
public:
	Explosion(sf::Texture* texture, const float x_pos, const float y_pos);
	void render(sf::RenderWindow& target);
	void update();
	bool isFinished();
};

