#include "stdafx.h"
#include <SFML/Graphics.hpp>

const float step = 15.0f;

using namespace sf;

enum struct Direction
{
	NONE,
	UP,
	DOWN,
	LEFT,
	RIGHT
};

struct Player
{
	CircleShape s_player;
	CircleShape s_righthand;
	CircleShape s_lefthand;
	Direction direction;
};

void initializeMan(Player &player)
{
	player.s_player.setRadius(20);
	player.s_player.setFillColor(sf::Color::Green);
	player.s_player.setPosition(400, 450);
	player.s_righthand.setRadius(10);
	player.s_righthand.setFillColor(sf::Color::Green);
	player.s_righthand.setPosition(440, 450);
	player.s_lefthand.setRadius(10);
	player.s_lefthand.setFillColor(sf::Color::Green);
	player.s_lefthand.setPosition(380, 450);
}
void UpdatePlayer(Player &player)
{
Vector2f position = player.s_player.getPosition();
Vector2f positionRight = player.s_righthand.getPosition();
Vector2f positionLeft = player.s_lefthand.getPosition();
	switch (player.direction)
	{
	case Direction::UP:
		position.y -= step;
		positionRight.y -= step;
		positionLeft.y -= step;
		break;
	case Direction::DOWN:
		position.y += step;
		positionRight.y += step;
		positionLeft.y += step;
		break;
	case Direction::LEFT:
		position.x -= step;
		positionRight.x -= step;
		positionLeft.x -= step;
		break;
	case Direction::RIGHT:
		position.x += step;
		positionRight.x += step;
		positionLeft.x += step;
		break;
	}
	if (position.x <= 20)
		position.x = 20;
	else if (position.x >= 740)
		position.x = 740;
	if (position.y <= 340)
		position.y = 340;
	else if (position.y >= 560)
		position.y = 560;

	if (positionRight.x <= 60)
		positionRight.x = 60;
	else if (positionRight.x >= 780)
		positionRight.x = 780;
	if (positionRight.y <= 340)
		positionRight.y = 340;
	else if (positionRight.y >= 560)
		positionRight.y = 560;

	if (positionLeft.x <= 0)
		positionLeft.x = 0;
	else if (positionLeft.x >= 720)
		positionLeft.x = 720;
	if (positionLeft.y <= 340)
		positionLeft.y = 340;
	else if (positionLeft.y >= 560)
		positionLeft.y = 560;

	player.s_player.setPosition(position);
	player.s_righthand.setPosition(positionRight);
	player.s_lefthand.setPosition(positionLeft);
}

bool handleKeyPress(const Event::KeyEvent &event, Player &player)
{
	bool handled = true;
	switch (event.code)
	{
	case sf::Keyboard::Up:
		player.direction = Direction::UP;
		UpdatePlayer(player);
		break;
	case sf::Keyboard::Down:
		player.direction = Direction::DOWN;
		UpdatePlayer(player);
		break;
	case sf::Keyboard::Left:
		player.direction = Direction::LEFT;
		UpdatePlayer(player);
		break;
	case sf::Keyboard::Right:
		player.direction = Direction::RIGHT;
		UpdatePlayer(player);
		break;
	default:
		handled = false;
		break;
	}
	return handled;
}

bool handleKeyRelease(const sf::Event::KeyEvent &event, Player &player)
{
	bool handled = true;
	switch (event.code)
	{
	case sf::Keyboard::Up:
		if (player.direction == Direction::UP)
		{
			player.direction = Direction::NONE;
		}
		break;
	case sf::Keyboard::Down:
		if (player.direction == Direction::DOWN)
		{
			player.direction = Direction::NONE;
		}
		break;
	case sf::Keyboard::Left:
		if (player.direction == Direction::LEFT)
		{
			player.direction = Direction::NONE;
		}
		break;
	case sf::Keyboard::Right:
		if (player.direction == Direction::RIGHT)
		{
			player.direction = Direction::NONE;
		}
		break;
	default:
		handled = false;
		break;
	}

	return handled;
}

void handleEvents(sf::RenderWindow & window, Player &player)
{
	sf::Event event;
	while (window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
		{
			window.close();
		}
		else if (event.type == Event::KeyPressed)
		{
			handleKeyPress(event.key, player);		
		}
		else if (event.type == sf::Event::KeyReleased)
		{
			handleKeyRelease(event.key, player);
		}

	}
}

void render(sf::RenderWindow & window, Player & player)
{
	window.clear(sf::Color::White);
	window.draw(player.s_player);
	window.draw(player.s_righthand);
	window.draw(player.s_lefthand);
	window.display();
}



int main(int, char *[])
{
	sf::RenderWindow window(sf::VideoMode(800, 600), "Window Title");
	//window.sf::Window::setMouseCursorVisible(false);
	Player player;
	initializeMan(player);

	while (window.isOpen())
	{
		handleEvents(window, player);
		render(window, player);
	}

	return 0;
}