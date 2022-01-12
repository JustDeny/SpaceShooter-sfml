#include "Explosion.h"

Explosion::Explosion(sf::Texture* texture, const float x_pos, const float y_pos) :
	sprite(*texture), currentFrame(0), row(0), finished(false)
{
	sprite.setPosition(x_pos, y_pos);
	sprite.setScale(0.7f, 0.7f);
	sprite.setTextureRect(sf::IntRect((int)currentFrame * 194, row * 192, 190, 190));
}

void Explosion::render(sf::RenderWindow& target)
{
	target.draw(sprite);
}

void Explosion::update()
{
	if (animClock.getElapsedTime().asSeconds() > ANIM_DELAY)
	{
		++currentFrame;
		animClock.restart();
		if (currentFrame > 5)
		{
			currentFrame -= 5;
			row += 1;
		}
		if (row > 4)
		{
			row -= 4;
			finished = true;
		}
	}
	sprite.setTextureRect(sf::IntRect((int)currentFrame * 194, row * 192, 190, 190));
}

bool Explosion::isFinished()
{
	return finished;
}
