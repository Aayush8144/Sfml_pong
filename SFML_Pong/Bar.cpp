#include "Bar.h"

Bar::Bar(const sf::Texture* texture, const sf::RenderWindow &window, bool leftSide)
{
	// setting bar size
	body.setSize(sf::Vector2f(150, 15)); 
	
	// setting origin at the center
	body.setOrigin(body.getSize().x/2, body.getSize().y/2);
	
	// setting bar initial position according to side
	if (leftSide)
		body.setPosition((12.5/100*window.getSize().x), window.getSize().y/2);
	else
		body.setPosition((87.5 / 100 * window.getSize().x), window.getSize().y / 2);
	
	// setting bar texture
	body.setTexture(texture); 

	// rotating the bar so that it is vertical
	body.setRotation(90.f); 

	// setting yVelocity
	yVelocity = 0;
}

Bar::~Bar()
{
}

void Bar::Update(bool upKeyState, bool downKeyState)
{
	// vertical movements
	// up key is pressed
	if (upKeyState)
	{
		this->yVelocity = -5;
	}

	// down key is pressed
	if (downKeyState)
	{
		this->yVelocity = 5;
	}

	// if both up and down key is pressed at the sametime xVelocity = 0;
	if (upKeyState && downKeyState)
	{
		this->yVelocity = 0;
	}

	// if both up and down key is not pressed xVelocity = 0;
	if (!upKeyState && !downKeyState)
	{
		this->yVelocity = 0;
	}

	// moving the body in y-axis
	body.move(0,this->yVelocity);
}

bool Bar::IsOutOfBounds(const sf::RenderWindow& window)
{
	// checking if the bar is in palyable zone
	// x value of get size is used because the body is rotated 90 degree
	// body is rotated because a certain someone made a horizontal texture
	// todo: see if the texture can be rotated and then generated the body of size 15,150
	if (body.getPosition().y > body.getSize().x/2 &&
		body.getPosition().y < (window.getSize().y - body.getSize().x / 2))
		return false;
	return true;
}

void Bar::Draw(sf::RenderWindow& window)
{
	window.draw(body);
}