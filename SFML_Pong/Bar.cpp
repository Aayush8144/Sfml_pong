#include "Bar.h"

Bar::Bar(const sf::Texture* texture, const sf::RenderWindow &window, bool leftSide)
{
	// setting bar size
	body.setSize(sf::Vector2f(15, 150)); 
	
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
	// body.setRotation(90.f); 

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

void Bar::Draw(sf::RenderWindow& window)
{
	window.draw(body);
}

void Bar::CheckCollisionWithScreen(const sf::RenderWindow& window)
{
	if (GetCollider().IsOutOfBoundsTopOrBottom(window))
	{
		// checking if it is out of bounds in the top or below and adjusting respectively
		if (GetPosition().y < window.getSize().y / 2)
			SetPositon(GetPosition().x, GetSize().y / 2);
		else
			SetPositon(GetPosition().x, window.getSize().y - GetSize().y / 2);
	}
}