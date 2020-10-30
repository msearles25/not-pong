#include <cstdlib>
#include <sstream>
#include <SFML/Graphics.hpp>
#include "Ball/Ball.h"
#include "Bat/Bat.h"

int main()
{
	// create a video mode object
	sf::VideoMode vm(1920, 1080);
	
	//create and open a window for the game
	sf::RenderWindow window(vm, "Pong");

	int score{ 0 };
	int lives{ 3 };

	// Create a bat at the bottom center of the screen
	Bat bat(1920 / 2, 1080 - 20);

	// Create a ball
	Ball ball(1920 / 2, 0);

	// Create a text object 
	sf::Text hud;

	sf::Font font;
	font.loadFromFile("fonts/DS-DIGIT.ttf");

	// set the font to the text
	hud.setFont(font);

	hud.setCharacterSize(75);
	hud.setFillColor(sf::Color::White);
	hud.setPosition(20, 20);

	// here is the clock for our timing on everything
	sf::Clock clock;

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				// Quit the game when the window gets closed
				window.close();
			}
		}

		// handle the player quitting
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
		{
			window.close();
		}

		// handle the moving of the arrow keys for the bat
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		{
			bat.moveLeft();
		}
		else
		{
			bat.stopLeft();
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		{
			bat.moveRight();
		}
		else
		{
			bat.stopRight();
		}

		// Update the bat, ball and hud

		// update the delta time
		sf::Time dt = clock.restart();

		bat.update(dt);
		ball.update(dt);

		// update the hud text
		std::stringstream ss;
		ss << "Score: " << score << "   Lives: " << lives;
		hud.setString(ss.str());

		// Handle the ball hitting the bottom
		if (ball.getPosition().top > window.getSize().y)
		{
			// Reverse the balls direction
			ball.reboundBottom();

			// Remove a life
			lives--;

			// Check for zero lives
			if (lives < 1)
			{
				// reset the score
				score = 0;
				lives = 3;
			}
		}

		// Handle the ball hitting the top
		if (ball.getPosition().top < 0)
		{
			ball.reboundBatOrTop();
			// add a point
			score++;
		}

		// handle the ball hitting the sides
		if (ball.getPosition().left < 0 ||
			ball.getPosition().left + ball.getPosition().width > window.getSize().x)
		{
			ball.reboundSides();
		}

		// has the ball hit the bat?
		if (ball.getPosition().intersects(bat.getPosition()))
		{
			// hit was detected
			ball.reboundBatOrTop();
		}

		// Draw everything
		window.clear();
		window.draw(hud);
		window.draw(bat.getShape());
		window.draw(ball.getShape());
		window.display();
	}

	return 0;
}