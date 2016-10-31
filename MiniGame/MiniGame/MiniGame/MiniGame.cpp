#include "stdafx.h"
#include <SFML/Graphics.hpp>
#include <iostream>

const float speed = 15.0f;
using namespace sf;
using namespace std;


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
	position.x += 15;
	position.y += 30;
	ball.s_snowball.setPosition(position);
}

void InitializeSecondSnowBall(SnowBall &ball, Player &player)
{
	ball.s_snowball.setRadius(5);
	ball.s_snowball.setFillColor(Color::Red);
	Vector2f position = player.s_player.getPosition();
	position.x += 15;
	ball.s_snowball.setPosition(position);
}

void UpdateSnowBall(SnowBall &ball, Player &player)
{
	Vector2f position = ball.s_snowball.getPosition();
	position.y -= 0.1f;
	if (position.y <= 0)
	{
		position = player.s_player.getPosition();
		position.x += 15;
		position.y -= 15;
	}
	ball.s_snowball.setPosition(position);
}

void UpdateSecondSnowBall(SnowBall &ball, Player &player)
{
	Vector2f position = ball.s_snowball.getPosition();
	position.y += 0.1f;
	if (position.y >= 600)
	{
		position = player.s_player.getPosition();
		position.x += 15;
		position.y += 15;
	}
	ball.s_snowball.setPosition(position);
}

bool FirstPlayerWin(SnowBall ball, Player &enemy)
{
	Vector2f snowballPosition = ball.s_snowball.getPosition();
	Vector2f enemyPosition = enemy.s_player.getPosition();
	return (snowballPosition.x >= enemyPosition.x &&
		snowballPosition.x <= enemyPosition.x + 40 &&
		snowballPosition.y >= enemyPosition.y &&
		snowballPosition.y <= enemyPosition.y + 40);
}

bool SecondPlayerWin(SnowBall ball, Player &player)
{
	Vector2f snowballPosition = ball.s_snowball.getPosition();
	Vector2f enemyPosition = player.s_player.getPosition();
	return (snowballPosition.x >= enemyPosition.x &&
		snowballPosition.x <= enemyPosition.x + 40 &&
		snowballPosition.y <= enemyPosition.y &&
		snowballPosition.y + 5 >= enemyPosition.y);
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

void UpdatePlayer(Player &player, int &numberPlayer, Clock &clock)
{
	Vector2f position = player.s_player.getPosition();
	Vector2f positionRight = player.s_righthand.getPosition();
	Vector2f positionLeft = player.s_lefthand.getPosition();
	/*int time = clock.getElapsedTime().asMilliseconds();
	clock.restart();
	time = time / 100;
	int step = speed * time;*/
	int step = 15.f;
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

void UpdateDirectionFirstPlayer(Player &player, int &numberPlayer, Clock &clock)
{
	if (Keyboard::isKeyPressed(Keyboard::Up))
		{
			player.direction = Direction::UP;
			UpdatePlayer(player, numberPlayer, clock);
		}
	else if (Keyboard::isKeyPressed(Keyboard::Down))
	{
		player.direction = Direction::DOWN;
		UpdatePlayer(player, numberPlayer, clock);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		player.direction = Direction::LEFT;
		UpdatePlayer(player, numberPlayer, clock);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		player.direction = Direction::RIGHT;
		UpdatePlayer(player, numberPlayer, clock);
	}
}

void UpdateDirectionSecondPlayer(Player &enemy, int &numberPlayer, Clock &clock)
{
	if (Keyboard::isKeyPressed(Keyboard::W))
	{
		enemy.direction = Direction::UP;
		UpdatePlayer(enemy, numberPlayer, clock);
	}
	else if (Keyboard::isKeyPressed(Keyboard::S))
	{
		enemy.direction = Direction::DOWN;
		UpdatePlayer(enemy, numberPlayer, clock);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		enemy.direction = Direction::LEFT;
		UpdatePlayer(enemy, numberPlayer, clock);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		enemy.direction = Direction::RIGHT;
		UpdatePlayer(enemy, numberPlayer, clock);
	}
}

void handleEvents(sf::RenderWindow & window, Player &player, Player &enemy, SnowBall &ball, Clock &clock)
{
	sf::Event event;
	while (window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
		{
			window.close();
		}
		int numberPlayer = 1;
		UpdateDirectionFirstPlayer(player, numberPlayer, clock);
		numberPlayer = 2;
		UpdateDirectionSecondPlayer(enemy, numberPlayer, clock);
	}
}

void render(sf::RenderWindow & window, Player & player, Player & enemy, SnowBall &ball, SnowBall &secondball)
{
	window.clear(sf::Color::White);
	window.draw(player.s_player);
	window.draw(player.s_righthand);
	window.draw(player.s_lefthand);
	
	window.draw(enemy.s_player);
	window.draw(enemy.s_righthand);
	window.draw(enemy.s_lefthand);
	
	window.draw(ball.s_snowball);
	window.draw(secondball.s_snowball);
	window.display();
}



int main(int, char *[])
{
	sf::RenderWindow window(sf::VideoMode(800, 600), "Window Title");
	window.sf::Window::setMouseCursorVisible(false);
	Clock clock;
	bool gameEnd = false;
	Player player;
	Player enemy;
	SnowBall snowball;
	SnowBall secondsnowball;
	int numberPlayer = 1;
	initializeMan(player, numberPlayer);
	numberPlayer = 2;
	initializeMan(enemy, numberPlayer);
	InitializeSnowBall(snowball, player);
	InitializeSecondSnowBall(secondsnowball, enemy);
	while (window.isOpen() && (!gameEnd))
	{
		handleEvents(window, player, enemy, snowball, clock);
		UpdateSnowBall(snowball, player);
		UpdateSecondSnowBall(secondsnowball, enemy);
		if (FirstPlayerWin(snowball, enemy))
		{
			gameEnd = true;
			cout << "First player win" << "\n";	
		}
		if (SecondPlayerWin(secondsnowball, player))
		{
			gameEnd = true;
			cout << "Second player win" << "\n";
		}
		render(window, player, enemy, snowball, secondsnowball);
	}
	return 0;
}