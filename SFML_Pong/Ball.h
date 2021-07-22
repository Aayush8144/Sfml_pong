#include "SFML/Graphics.hpp"
#include <iostream>

#include "Bar.h"
#include "Collider.h"

#pragma once
class Ball
{
public: 
	/*
	* constructor sets the initial state of the ball object, sets the texture, rotation,
		size, origin, positon , and speed for the ball object
	* @param const *texture: memory lotion of the loaded texture
	* @param const window: reference of the window to get its size
	* @param xVelocity: speed of the ball object in x axis
	* @param yVelocity: speed of the ball object in x axis
	*/
	Ball(const sf::Texture* texture, const sf::RenderWindow& window, float xVelocity, float yVelocity);

	~Ball();

	// position setter funciton 
	void SetPositon(float xPosition, float yPosition) { body.setPosition(xPosition, yPosition); }
	
	// flip xVelocity setter funciton 
	void FlipXVelocity() { this->xVelocity *= -1; }
	
	// flip yVelocity setter funciton 
	void FlipYVelocity() { this->yVelocity *= -1; }

	// size getter funcitons
	const sf::Vector2f GetSize() { return body.getSize(); }

	// positon getter funcitons
	const sf::Vector2f GetPosition() { return body.getPosition(); }

	// getter funciton returns collider object of the body
	Collider GetCollider() { return Collider(body); }

	// Move function moves the ball
	void Move() { body.move(xVelocity, yVelocity); }

	// Draw function draws the body to screen
	void Draw(sf::RenderWindow& window);

	/* CheckCollisionWithScreen checks if the ball is colliding with screen: 
			top, left, bottom, and right
	* @param const window : reference of the window to get its size
	* @todo: reset the game, gameOver when ball hits the left or right screen
	*/
	void CheckCollisionWithScreen(const sf::RenderWindow& window);

	/* CheckCollisionWithScreen checks if the ball is colliding with screen:
			top, left, bottom, and right
	* @param const window : reference of the window to get its size
	* @todo: reset the game, gameOver when ball hits the left or right screen
	*/
	void CheckCollisionWithBar(const sf::RenderWindow& window, const sf::RectangleShape& barBody);


private:
	sf::RectangleShape body;
	float xVelocity;
	float yVelocity;
};

