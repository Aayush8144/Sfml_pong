#include "Ball.h"
#include <utility>

Ball::Ball(const sf::Texture* texture, const sf::RenderWindow &window, float xVelocity, float yVelocity)
{
	// setting ball size
	body.setSize(sf::Vector2f(20, 20)); 
	
	// setting ball texture
	body.setTexture(texture); 
	
	// setting the relative ball origin to its center 
	body.setOrigin(body.getSize().x / 2, body.getSize().y / 2);
	
	// setting ball at the middle of the screen
	body.setPosition(window.getSize().x / 2, window.getSize().y / 2); 

	// setting speed
	this->xVelocity = xVelocity;
	this->yVelocity = yVelocity;
}

Ball::~Ball()
{
}

bool Ball::IsOutOfBoundsTopOrBottom(const sf::RenderWindow& window)
{
	if (body.getPosition().y < body.getSize().y / 2 ||
		body.getPosition().y >(window.getSize().y - (body.getSize().y / 2)))
		return true;

	return false;
}

bool Ball::IsOutOfBoundsLeftOrRight(const sf::RenderWindow& window)
{
	if (body.getPosition().x < body.getSize().x / 2 ||
		body.getPosition().x >(window.getSize().x - body.getSize().x / 2))
		return true;

	return false;
}

bool Ball::IsCollidingWithBar(const sf::RectangleShape& barBody)
{
	if (body.getGlobalBounds().intersects(barBody.getGlobalBounds()))
		return true;
	
	return false;
}

void Ball::Draw(sf::RenderWindow& window)
{
	window.draw(body);

}
