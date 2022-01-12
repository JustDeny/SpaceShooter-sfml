#pragma once
#include "Utility.h"
enum BUTTON
{
	BUTTON_UNDEF, BUTTON_PLAY, BUTTON_EXIT
};
class Menu
{
private:
	sf::RenderWindow* window;
	sf::Font font;
	sf::Text text[2];
	bool m_play;
	int m_button;
	sf::RectangleShape button_play;
	sf::RectangleShape button_exit;
	sf::Texture m_background_texture;
	sf::Sprite m_background_sprite;
public:
	Menu(sf::RenderWindow* window);
	void Run();
	void initVariables();
	void Reset();
};

