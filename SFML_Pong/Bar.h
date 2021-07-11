#include <iostream>
#include "SFML/Graphics.hpp"

#pragma once
class Bar
{
public:
	/* 
	* constructor sets the initial state of the bar object, sets the texture, rotation, 
		size, origin, and positon for the bar object
	* @param const *texture: memory lotion of the loaded texture
	* @param const window: reference of the window to get its size
	* @param bool leftSide: decides which side to positoin the bar
	*/
	Bar(const sf::Texture* texture, const sf::RenderWindow& window, bool leftSide);
	
	// deconstructor
	~Bar();

	// position setter funciton 
	void SetPositon(float xPosition, float yPosition) { body.setPosition(xPosition, yPosition); }

	// size getter funcitons
	const sf::Vector2f GetSize() { return body.getSize(); }
	
	// positon getter funcitons
	const sf::Vector2f GetPosition() { return body.getPosition(); }
	
	/*
		Update function moves the body according to the key state
		if both the parameter are true or false then does not move the body
		@param upKeyState: if true moves the body up by 5 pixel, if false then by 0
		@param downKeyState: if true moves the body down by 5 pixel, if false then by 0
	*/
	void Update(bool upKeyState, bool downKeyState);

	/* 
		GetBody getter function
		@return: returns the reference to the body
	*/
	const sf::RectangleShape GetBody() { return body; }

	// IsOutOfBounds checks if the bar is in the screen or not
	// @param const window : reference of the window to get its size
	bool IsOutOfBounds(const sf::RenderWindow& window);

	// Draw function draws the body to screen
	void Draw(sf::RenderWindow &window);

private:
	sf::RectangleShape body;
	float yVelocity;
};

