#include "Menu.h"

Menu::Menu(sf::RenderWindow* window)
{
	this->window = window;
	initVariables();
}

void Menu::Run()
{
	sf::Vector2i mouse_pos;
	while (m_play)
	{
		sf::Event event;
		mouse_pos = sf::Mouse::getPosition(*window);
		while (window->pollEvent(event))
		{
			if (m_button == BUTTON_PLAY)
			{
				button_play.setOutlineColor(sf::Color::White);
				button_exit.setOutlineColor(sf::Color::White);
				m_play = false;
			}
			if (m_button == BUTTON_EXIT) { m_play = false; window->close(); }
			m_button = BUTTON_UNDEF;
			if (button_play.getGlobalBounds().contains(mouse_pos.x, mouse_pos.y))
			{
				text[0].setFillColor(sf::Color::Blue);
				if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
				{
					m_button = BUTTON_PLAY;
					button_play.setOutlineColor(sf::Color::Blue);
				}
			}
			else
			{
				text[0].setFillColor(sf::Color::White);
			}
			if (button_exit.getGlobalBounds().contains(mouse_pos.x, mouse_pos.y))
			{
				text[1].setFillColor(sf::Color::Blue);
				if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
				{
					m_button = BUTTON_EXIT;
					button_exit.setOutlineColor(sf::Color::Blue);
				}
			}
			else
			{
				text[1].setFillColor(sf::Color::White);
			}
		}
		window->clear();
		window->draw(m_background_sprite);
		window->draw(button_play);
		window->draw(button_exit);
		window->draw(text[0]);
		window->draw(text[1]);
		window->display();
	}
}

void Menu::initVariables()
{
	m_play = true;
	m_button = BUTTON_UNDEF;
	font.loadFromFile("font\\font.ttf");
	text[0].setString("PLAY");
	text[1].setString("EXIT");
	text[0].setFont(font);
	text[1].setFont(font);
	text[0].setPosition(555, 325);
	text[1].setPosition(555, 475);
	button_play.setSize(sf::Vector2f(150, 80));
	button_exit.setSize(sf::Vector2f(150, 80));
	button_play.setPosition(sf::Vector2f(525, 300));
	button_exit.setPosition(sf::Vector2f(525, 450));
	button_play.setOutlineColor(sf::Color::White);
	button_play.setOutlineThickness(10);
	button_exit.setOutlineColor(sf::Color::White);
	button_exit.setOutlineThickness(10);
	button_play.setFillColor(sf::Color::Black);
	button_exit.setFillColor(sf::Color::Black);
	m_background_texture.loadFromFile("textures\\background.jpg");
	m_background_sprite.setTexture(m_background_texture);
}

void Menu::Reset()
{
	m_play = true;
	m_button = BUTTON_UNDEF;
}
