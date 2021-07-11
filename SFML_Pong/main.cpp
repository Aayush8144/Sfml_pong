#include "SFML/Graphics.hpp"
#include <iostream>

#include "Bar.h"
#include "Ball.h"


// global variables
const unsigned int WINDOW_WIDTH = 800;
const unsigned int WINDOW_HEIGHT = 600;
const unsigned int FRAME_RATE = 60;

int main()
{
	// creating a render window
	sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "SFML_Pong");
	
	// setting framerate to 60 FPS
	window.setFramerateLimit(FRAME_RATE);

	// disabling continous key key press
	window.setKeyRepeatEnabled(false);

	// objects to handel events
	sf::Event events;

	//// states
	// pongBarLeft key states
	bool wKeyPressed = false;
	bool sKeyPressed = false;

	// pongBarRight key states
	bool upKeyPressed = false;
	bool downKeyPressed = false;

	// variables
	bool play = true;
	float xVelocity = 0, yVelocity = 0;

	// textures
	sf::Texture ballTexture;
	sf::Texture pongBarTexture;

	//// loading texture from file
	// loading ball texture
	if (!ballTexture.loadFromFile("F:/Projects/c_plus_plus/SFML_Pong/data/ball.png"))
	{
		std::cout << "Error while loading Ball Texture." << std::endl;
		return -1;
	}
	
	// loading pong bar texture
	if (!pongBarTexture.loadFromFile("F:/Projects/c_plus_plus/SFML_Pong/data/pongBar.png"))
	{
		std::cout << "Error while loading Pong Bar Texture" << std::endl;
		return -1;
	}

	//// shapes
	// ball
	Ball ball(&ballTexture, window, -2, 5);

	// pong bars 
	Bar pongBarLeft(&pongBarTexture, window, true);
	Bar pongBarRight(&pongBarTexture, window, false);

	// game loop
	while (play)
	{
		// events
		while (window.pollEvent(events))
		{
			//if (events.type == sf::Event::Closed) play = false;
			// checking which events are present
			switch(events.type)
			{
				// when eventype is closed
				case (sf::Event::Closed):
				{
					play = false;
					break;
				}

				// when event type is a key press
				case(sf::Event::KeyPressed):
				{
					//checking if W,S key is pressed
					if (events.key.code == sf::Keyboard::S) sKeyPressed = true;
					if (events.key.code == sf::Keyboard::W) wKeyPressed = true;
					// checking if up and down is  pressed
					if (events.key.code == sf::Keyboard::Up) upKeyPressed = true;
					if (events.key.code == sf::Keyboard::Down) downKeyPressed = true;
					break;
				}

				// when event type is a key released
				case(sf::Event::KeyReleased):
				{
					//checking if W,S key is released
					if (events.key.code == sf::Keyboard::S) sKeyPressed = false;
					if (events.key.code == sf::Keyboard::W) wKeyPressed = false;
					// checking if up and down is released
					if (events.key.code == sf::Keyboard::Up) upKeyPressed = false;
					if (events.key.code == sf::Keyboard::Down) downKeyPressed = false;
					break;
				} 
			} // event switch ends
		} // events ends
		
		//// logic

		// movement for the bar
		pongBarRight.Update(upKeyPressed, downKeyPressed);
		pongBarLeft.Update(wKeyPressed, sKeyPressed);
		
		// movement for ball
		ball.Move();

		////// colider
		//// todo: move to a collider class
		//// checking if the pong bar is out of bounds
		// left bat
		if (pongBarLeft.IsOutOfBounds(window)) 
		{ 
			// checking if it is out of bounds in the top or below and adjusting respectively
			if(pongBarLeft.GetPosition().y < WINDOW_WIDTH / 2)
				pongBarLeft.SetPositon(12.5 / 100 * WINDOW_WIDTH, pongBarLeft.GetSize().x/2);
			else
				pongBarLeft.SetPositon(12.5 / 100 * WINDOW_WIDTH, WINDOW_HEIGHT - pongBarLeft.GetSize().x / 2);
		}
		// right bar
		if (pongBarRight.IsOutOfBounds(window))
		{
			// checking if it is out of bounds in the top or below and adjusting respectively
			if (pongBarRight.GetPosition().y < WINDOW_WIDTH / 2)
				pongBarRight.SetPositon(87.5 / 100 * WINDOW_WIDTH, pongBarRight.GetSize().x / 2);
			else
				pongBarRight.SetPositon(87.5 / 100 * WINDOW_WIDTH, WINDOW_HEIGHT - pongBarRight.GetSize().x / 2);
		}

		// ball collider
		// checking top or bottom
		if (ball.IsOutOfBoundsTopOrBottom(window))
		{
			ball.FlipYVelocity();
		}
		// checking for left or right
		// @todo: reset the game, gameOver
		if (ball.IsOutOfBoundsLeftOrRight(window))
		{
			ball.FlipXVelocity();
		}
		
		////  checking collider  for ball with bar
		// pongBarLeft
		if (ball.IsCollidingWithBar(pongBarLeft.GetBody()))
		{
			ball.FlipXVelocity();
		}
		// pongBarRight
		if (ball.IsCollidingWithBar(pongBarRight.GetBody()))
		{
			ball.FlipXVelocity();
		}

		// rendering
		window.clear(); // clearing the screen

		ball.Draw(window);
		//bars
		pongBarLeft.Draw(window);
		pongBarRight.Draw(window);
		
		window.display(); // displaying the screen
	} // play loop ends
	
	// cleaning 
	window.close();

	return 0;
}

/*
// four movement
		// horizontal movements
		//if (aKeyPressed)
		//{
		//	xVelocity = -5;
		//}
		//if (dKeyPressed)
		//{
		//	xVelocity = 5;
		//}
		//// if both a and d is pressed at the sametime xVelocity = 0;
		//if (aKeyPressed && dKeyPressed)
		//{
		//	xVelocity = 0;
		//}
		//// if both a and d is not pressed xVelocity = 0;
		//if (!aKeyPressed && !dKeyPressed)
		//{
		//	xVelocity = 0;
		//}

		//// vertical movements
		//if (wKeyPressed)
		//{
		//	yVelocity = -5;
		//}
		//if (sKeyPressed)
		//{
		//	yVelocity = 5;
		//}
		//// if both a and d is pressed at the sametime xVelocity = 0;
		//if (aKeyPressed && dKeyPressed)
		//{
		//	yVelocity = 0;
		//}
		//// if both a and d is not pressed xVelocity = 0;
		//if (!aKeyPressed && !dKeyPressed)
		//{
		//	yVelocity = 0;
		//}

		//// moving the ball;
		//// moving in x-axis
		//ball.move(xVelocity, 0);
*/