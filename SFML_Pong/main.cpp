#include "SFML/Graphics.hpp" // for sfml graphics
#include <iostream>	// for cout,cin
#include <sstream>	// for concoting text 

#include "Bar.h"
#include "Ball.h"
#include "Collider.h"


// global variables
const unsigned int WINDOW_WIDTH = 800;
const unsigned int WINDOW_HEIGHT = 600;
const unsigned int FRAME_RATE = 60;


// make a base class for bar and ball to poly morphorize

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

	//// variables
	bool play = true; // for game loop 
	float xVelocity = 0, yVelocity = 0; // ball velocity 
	int leftBarScore = 0, rightBarScore = 0; // score counter
	bool gameOver = true;	// start the game

	// fonts 
	sf::Font font;
	
	// loading font form file
	if (!font.loadFromFile("F:/Projects/c_plus_plus/SFML_Pong/data/BRUSHSCI.ttf"))
	{
		std::cout << "Error while loading font." << std::endl;
		return -1;
	}

	/////// scoreboard
	sf::Text score;
	// setting the font of the score
	score.setFont(font);
	// setting the size of the score board to 30.f
	score.setCharacterSize(30.f);
	// setting origin to the center of the object
	score.setOrigin(score.getCharacterSize() / 2, score.getCharacterSize() / 2);
	// setting position of the score board to the middle of the screen in x-axis and top of the screen inm y-axis
	score.setPosition(WINDOW_WIDTH / 2, score.getCharacterSize() / 2);
	// setting the color to white
	score.setFillColor(sf::Color::White);
	// setting the score
	score.setString("0 : 0");

	// textures
	sf::Texture ballTexture;
	sf::Texture pongBarTexture;

	//// loading texture from file
	// loading ball texture
	if (!ballTexture.loadFromFile("F:/Projects/c_plus_plus/SFML_Pong/data/images_textures/ball.png"))
	{
		std::cout << "Error while loading Ball Texture." << std::endl;
		return -1;
	}
	
	// loading pong bar texture
	if (!pongBarTexture.loadFromFile("F:/Projects/c_plus_plus/SFML_Pong/data/images_textures/pongBar.png"))
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
					// checking if space bar is pressed 
					// if yes then starting the game
					if (events.key.code == sf::Keyboard::Space) gameOver = false;
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
		if (ball.GetCollider().IsOutOfBoundsLeftOrRight(window))
		{
			gameOver = true;
			
			// increasing the score
			if (ball.GetPosition().x > WINDOW_WIDTH/2)
			{
				rightBarScore++;
			}
			else
			{
				leftBarScore++;
			}

			// pauseing for a bit
			// look into the udemy video
			for (int i = 0; i <= 100000; ++i);

			//// resetting everything
			// resetting the ball
			ball.SetPositon(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2);
			
			// resetting the bars
			pongBarLeft.SetPositon(pongBarLeft.GetPosition().x, WINDOW_HEIGHT / 2);
			pongBarRight.SetPositon(pongBarRight.GetPosition().x, WINDOW_HEIGHT / 2);

		}

		if (!gameOver)
		{

			// movement for the bar
			pongBarRight.Update(upKeyPressed, downKeyPressed);
			pongBarLeft.Update(wKeyPressed, sKeyPressed);
		
			// movement for ball
			ball.Move();

			//@todo: make a update collider classfor bars and balls

			////// colider
			//// checking if the pong bar is out of bounds
			// left bar
			pongBarLeft.CheckCollisionWithScreen(window);

			// right bar
			pongBarRight.CheckCollisionWithScreen(window);

			///// ball collider
			// checking collider with the screen
			ball.CheckCollisionWithScreen(window);

			////  checking collider  for ball with bar
			// pongBarLeft
			ball.CheckCollisionWithBar(window, pongBarLeft.GetBody());

			// pongBarRight
			ball.CheckCollisionWithBar(window, pongBarRight.GetBody());

		}

		//////// rendering
		window.clear(); // clearing the screen

		window.draw(score);

		// ball
		ball.Draw(window);
		//bars
		pongBarLeft.Draw(window);
		pongBarRight.Draw(window);

		// scores
		std::stringstream text;
		text << leftBarScore << " : " << rightBarScore;
		score.setString(text.str());
		
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