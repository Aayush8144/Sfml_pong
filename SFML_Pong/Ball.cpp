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

void Ball::Draw(sf::RenderWindow& window)
{
	window.draw(body);

}
