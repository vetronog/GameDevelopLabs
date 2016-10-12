#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <string>
#include <sstream>
#include <math.h>
#include <iostream>

using namespace std;


static const int SCREEN_WIDTH = 800;
static const int SCREEN_HEIGHT = 600;
static const float PI = 3.1415927;
static const int CLOCK_CIRCLE_SIZE = 250;
static const int CLOCK_CIRCLE_THICKNESS = 2;
static const int DOTS = 60;

using namespace sf;

struct Clocks
{
    CircleShape dot[DOTS];
    Music clockTick;
    Text digit[12];
    Font font;
};

void ClocksCenterCircle(RenderWindow &window, CircleShape &centerCircle, Vector2f &windowCenter)
{
    centerCircle.setPointCount(100);
    centerCircle.setFillColor(Color::Red);
    centerCircle.setOrigin(centerCircle.getGlobalBounds().width / 2, centerCircle.getGlobalBounds().height / 2);
    centerCircle.setPosition(windowCenter);
}

void ClocksOutline(RenderWindow &window, CircleShape &clockCircle)
{
    clockCircle.setPointCount(100);
    clockCircle.setOutlineThickness(CLOCK_CIRCLE_THICKNESS);
    clockCircle.setOutlineColor(sf::Color::Black);
    clockCircle.setOrigin(clockCircle.getGlobalBounds().width / 2, clockCircle.getGlobalBounds().height / 2);
    clockCircle.setPosition(window.getSize().x / 2 + CLOCK_CIRCLE_THICKNESS, window.getSize().y / 2 + CLOCK_CIRCLE_THICKNESS);
}

void ClocksHands(RenderWindow &window, RectangleShape &hourHand, RectangleShape &minuteHand, RectangleShape &secondsHand,Vector2f &windowCenter)
{
    hourHand.setFillColor(Color::Black);
    minuteHand.setFillColor(Color::Black);
    secondsHand.setFillColor(Color::Red);

    hourHand.setOrigin(hourHand.getGlobalBounds().width / 2, hourHand.getGlobalBounds().height - 25);
    minuteHand.setOrigin(minuteHand.getGlobalBounds().width / 2, minuteHand.getGlobalBounds().height - 25);
    secondsHand.setOrigin(secondsHand.getGlobalBounds().width / 2, secondsHand.getGlobalBounds().height - 25);

    hourHand.setPosition(windowCenter);
    minuteHand.setPosition(windowCenter);
    secondsHand.setPosition(windowCenter);
}

bool DotsAndPlace(RenderWindow &window, Clocks &clocks)
{
    if (!clocks.font.loadFromFile("resources/OpenSans-Bold.ttf"))
    {
        return false;
    }
    float angle = (1.5 * PI) + (PI/6);

    for (int i=0; i<DOTS; i++)
    {
        int digit = i/5;
        float x = (CLOCK_CIRCLE_SIZE - 10) * cos(angle);
        float y = (CLOCK_CIRCLE_SIZE - 10) * sin(angle);
        if (i%5 == 0)
        {
            clocks.dot[i] = sf::CircleShape(3);
            clocks.digit[i/5].setFont(clocks.font);
            clocks.digit[i/5].setFillColor(Color::Red);
            clocks.digit[i/5].setString(std::to_string(digit+1));
            clocks.digit[i/5].setCharacterSize(30);
            clocks.digit[i/5].setPosition(x + window.getSize().x / 2, y +  window.getSize().y / 2);
            clocks.digit[i/5].setOrigin(clocks.digit[i/5].getGlobalBounds().width / 2.0f, clocks.digit[i/5].getGlobalBounds().height / 2.0f);
         }
        else
            clocks.dot[i] = sf::CircleShape(1);
        clocks.dot[i].setFillColor(sf::Color::Black);
        clocks.dot[i].setOrigin(clocks.dot[i].getGlobalBounds().width / 2, clocks.dot[i].getGlobalBounds().height / 2);
        clocks.dot[i].setPosition(x + window.getSize().x / 2, y +  window.getSize().y / 2);

        angle = angle + ((2 * PI)/60);
    }
    return true;
}

bool ClocksMusic(RenderWindow &window, Clocks &clocks)
{
    if (!clocks.clockTick.openFromFile("resources/clock-1.wav"))
        return false;
    clocks.clockTick.setLoop(true);
    clocks.clockTick.play();
    return true;
}

bool ClocksBackGround(RenderWindow &window, Texture &clockImage, CircleShape &clockCircle)
{
    if (!clockImage.loadFromFile("resources/background.png"))
    {
        return false;
    }

    clockCircle.setTexture(&clockImage);
    clockCircle.setTextureRect(IntRect(40, 0, 500, 500));
    return true;
}

int main()
{

    // Define some variables and constants
    Clocks clocks;

    // Set multisampling level
    ContextSettings settings;
    settings.antialiasingLevel = 8;

    // Create the window of the application
    RenderWindow window(VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "SFML Analog Clock", Style::Close, settings);

    // Define windowCenter which gets the center of the window here, right after creating window
    Vector2f windowCenter = Vector2f(window.getSize().x / 2.0f, window.getSize().y / 2.0f);

    // Create a list for clock's dot
    // Create dots and place them to very right positions
    if (!DotsAndPlace(window, clocks))
        return 1;

    // Create outline of the clock
    CircleShape clockCircle(CLOCK_CIRCLE_SIZE);
    ClocksOutline(window, clockCircle);

    // Create another circle for center
    CircleShape centerCircle(10);

    ClocksCenterCircle(window, centerCircle, windowCenter);

    RectangleShape hourHand(Vector2f(5, 180));
    RectangleShape minuteHand(Vector2f(3, 240));
    RectangleShape secondsHand(Vector2f(2, 250));
    ClocksHands(window, hourHand, minuteHand, secondsHand, windowCenter);

    // Create hour, minute, and seconds hands


    // Create sound effect

    if (!(ClocksMusic(window, clocks)))
    {
        return 1;
    }

    // Create clock background
    Texture clockImage;
    if(!ClocksBackGround(window, clockImage, clockCircle))
    {
        return 1;
    }

    while (window.isOpen())
    {
        // Handle events
        Event event;
        while (window.pollEvent(event))
        {
            // Window closed: exit
            if (event.type == Event::Closed)
                window.close();
        }

        // Get system time
        std::time_t currentTime = std::time(NULL);

        struct tm * ptm = localtime(&currentTime);

        hourHand.setRotation(ptm->tm_hour*30 + (ptm->tm_min/2) );
        minuteHand.setRotation(ptm->tm_min*6 + (ptm->tm_sec/12) );
        secondsHand.setRotation(ptm->tm_sec*6);

        // Clear the window
        window.clear(Color::White);

        // Draw all parts of clock
        window.draw(clockCircle);
        for (int i=0; i<DOTS; i++)
        {
            window.draw(clocks.dot[i]);
            if (i % 5)
            window.draw(clocks.digit[i / 5]);
        }

        window.draw(hourHand);
        window.draw(minuteHand);
        window.draw(secondsHand);
        window.draw(centerCircle);

        // Display things on screen
        window.display();
    }

    return 0;
}