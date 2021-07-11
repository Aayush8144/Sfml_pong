#include "SFML/Graphics.hpp"
#include <iostream>

#include "Bar.h"

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

	// Move function moves the ball
	void Move() { body.move(xVelocity, yVelocity); }

	/* IsOutOfBoundsTopOrBottom checks if the ball is colliding with the top or bottom of the screen or not
	 * @param const window : reference of the window to get its size
	 * @return  bool values true if colliding, else false
	*/ 
	bool IsOutOfBoundsTopOrBottom(const sf::RenderWindow& window);

	/* IsOutOfBoundsLeftOrRight checks if the ball is colliding with the top or bottom of the screen or not
	 * @param const window : reference of the window to get its size
	 * @return  bool values true if colliding, else false
	*/
	bool IsOutOfBoundsLeftOrRight(const sf::RenderWindow& window);

	/* IsCollidingWithBar checks if the ball is colliding with bar
	 * @param const sf::RectangleShape& barBodyy : reference of the body of the bar to get its position
	 * @return  bool values true if colliding, else false
	 */
	bool IsCollidingWithBar(const sf::RectangleShape &barBody);

	// Draw function draws the body to screen
	void Draw(sf::RenderWindow& window);
private:
	sf::RectangleShape body;
	float xVelocity;
	float yVelocity;
};

