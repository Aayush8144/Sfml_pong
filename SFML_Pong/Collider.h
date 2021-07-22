#include "SFML/Graphics.hpp"

#pragma once
class Collider
{
public:
	// constructor
	Collider(sf::RectangleShape& body);

	// deconstructor
	~Collider();

	// size getter funcitons
	const sf::Vector2f GetSize() { return body.getSize(); }

	// positon getter funcitons
	const sf::Vector2f GetPosition() { return body.getPosition(); }

	// position setter funciton 
	void SetPositon(float xPosition, float yPosition) { body.setPosition(xPosition, yPosition); }

	// checking body collison

	/* IsOutOfBoundsTopOrBottom checks if the ball is colliding with the top 
	 * or bottom of the screen or not applies for both ball and bars
	 * @param const window : reference of the window to get its size
	 * @return  bool values true if colliding, else false
	*/
	const bool IsOutOfBoundsTopOrBottom(const sf::RenderWindow& window);

	/* IsOutOfBoundsLeftOrRight checks if the ball is colliding with the top 
	 * or bottom of the screen or not applies for only the ball 
	 * @param const window : reference of the window to get its size
	 * @return  bool values true if colliding, else false
	*/
	const bool IsOutOfBoundsLeftOrRight(const sf::RenderWindow& window);

	/* IsCollidingWithBar checks if the ball is colliding with bar
	* @param const sf::RectangleShape& barBodyy : reference of the body of the bar to get its position
	* @return  bool values true if colliding, else false
	*/
	const bool IsCollidingWithBar(const sf::RectangleShape& barBody);



private:
	sf::RectangleShape& body;

};

