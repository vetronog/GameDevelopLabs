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
	RIGHT,
};

struct Player
{
	CircleShape s_player;
	CircleShape s_righthand;
	CircleShape s_lefthand;
	Direction direction;
};

struct SnowBall
{
	CircleShape s_snowball;
};

void InitializeSnowBall(SnowBall &ball, Player &player)
{
	ball.s_snowball.setRadius(5);
	ball.s_snowball.setFillColor(Color::Green);
	Vector2f position = player.s_player.getPosition();
	position.y -= 15;
	ball.s_snowball.setPosition(position);
}

void UpdateSnowBall(SnowBall &ball, Player &player)
{
	Vector2f position = ball.s_snowball.getPosition();
	position.y -= 15;
	if (position.y <= 0)
	{
		position = player.s_player.getPosition();
	}
	ball.s_snowball.setPosition(position);
}

void initializeMan(Player &player, int &numberPlayer)
{
	Color color;
	Vector2f positionBody;
	Vector2f positionLeftHand;
	Vector2f positionRightHand;
	if (numberPlayer == 1)
	{
		color = Color::Green;
		positionBody = Vector2f(400.f, 450.f);
		positionLeftHand = Vector2f(440.f, 450.f);
		positionRightHand = Vector2f(380.f, 450.f);
	}
	else
	{
		color = Color::Red;
		positionBody = Vector2f(400.f, 200.f);
		positionLeftHand = Vector2f(435.f, 230.f);
		positionRightHand = Vector2f(385.f, 230.f);
	}
	player.s_player.setRadius(20);
	player.s_player.setFillColor(color);
	player.s_player.setPosition(positionBody);
	player.s_righthand.setRadius(10);
	player.s_righthand.setFillColor(color);
	player.s_righthand.setPosition(positionRightHand);
	player.s_lefthand.setRadius(10);
	player.s_lefthand.setFillColor(color);
	player.s_lefthand.setPosition(positionLeftHand);
}

void UpdatePlayer(Player &player, int &numberPlayer)
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
	if (numberPlayer == 1)
	{
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
	}
	else
	{
		if (position.x <= 20)
			position.x = 20;
		else if (position.x >= 740)
			position.x = 740;
		if (position.y <= 0)
			position.y = 0;
		else if (position.y >= 250)
			position.y = 250;

		if (positionRight.x <= 60)
			positionRight.x = 60;
		else if (positionRight.x >= 780)
			positionRight.x = 780;
		if (positionRight.y <= 25)
			positionRight.y = 25;
		else if (positionRight.y >= 280)
			positionRight.y = 280;

		if (positionLeft.x <= 0)
			positionLeft.x = 0;
		else if (positionLeft.x >= 720)
			positionLeft.x = 720;
		if (positionLeft.y <= 25)
			positionLeft.y = 25;
		else if (positionLeft.y >= 280)
			positionLeft.y = 280;
	}

	player.s_player.setPosition(position);
	player.s_righthand.setPosition(positionRight);
	player.s_lefthand.setPosition(positionLeft);
}

void UpdateDirectionFirstPlayer(Player &player, int &numberPlayer)
{
	if (Keyboard::isKeyPressed(Keyboard::Up))
		{
			player.direction = Direction::UP;
			UpdatePlayer(player, numberPlayer);
		}
	else if (Keyboard::isKeyPressed(Keyboard::Down))
	{
		player.direction = Direction::DOWN;
		UpdatePlayer(player, numberPlayer);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		player.direction = Direction::LEFT;
		UpdatePlayer(player, numberPlayer);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		{
			player.direction = Direction::RIGHT;
			UpdatePlayer(player, numberPlayer);
		}
}

void UpdateDirectionSecondPlayer(Player &enemy, int &numberPlayer)
{
	if (Keyboard::isKeyPressed(Keyboard::W))
	{
		enemy.direction = Direction::UP;
		UpdatePlayer(enemy, numberPlayer);
	}
	else if (Keyboard::isKeyPressed(Keyboard::S))
	{
		enemy.direction = Direction::DOWN;
		UpdatePlayer(enemy, numberPlayer);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		enemy.direction = Direction::LEFT;
		UpdatePlayer(enemy, numberPlayer);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		enemy.direction = Direction::RIGHT;
		UpdatePlayer(enemy, numberPlayer);
	}
}

void handleEvents(sf::RenderWindow & window, Player &player, Player &enemy, SnowBall &ball)
{
	sf::Event event;
	while (window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
		{
			window.close();
		}
		int numberPlayer = 1;
		UpdateDirectionFirstPlayer(player, numberPlayer);
		numberPlayer = 2;
		UpdateDirectionSecondPlayer(enemy, numberPlayer);
		UpdateSnowBall(ball, player);
	}
}

void render(sf::RenderWindow & window, Player & player, Player & enemy, SnowBall &ball)
{
	window.clear(sf::Color::White);
	window.draw(player.s_player);
	window.draw(player.s_righthand);
	window.draw(player.s_lefthand);
	
	window.draw(enemy.s_player);
	window.draw(enemy.s_righthand);
	window.draw(enemy.s_lefthand);
	
	window.draw(ball.s_snowball);
	window.display();
}



int main(int, char *[])
{
	sf::RenderWindow window(sf::VideoMode(800, 600), "Window Title");
	window.sf::Window::setMouseCursorVisible(false);
	Player player;
	Player enemy;
	SnowBall snowball;
	int numberPlayer = 1;
	initializeMan(player, numberPlayer);
	numberPlayer = 2;
	initializeMan(enemy, numberPlayer);
	InitializeSnowBall(snowball, player);
	while (window.isOpen())
	{
		handleEvents(window, player, enemy, snowball);
		render(window, player, enemy, snowball);
	}
	return 0;
}