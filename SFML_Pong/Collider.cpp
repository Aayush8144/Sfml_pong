#include "Collider.h"

Collider::Collider(sf::RectangleShape& body):
	body(body)
{
}

Collider::~Collider()
{
}

const bool Collider::IsOutOfBoundsTopOrBottom(const sf::RenderWindow& window)
{
	// chekcing if the body is in the out of bounds area
	if (GetPosition().y < GetSize().y / 2 ||
		GetPosition().y >(window.getSize().y - (GetSize().y / 2)))
		return true;

	return false;
}

const bool Collider::IsOutOfBoundsLeftOrRight(const sf::RenderWindow& window)
{
	if (body.getPosition().x < body.getSize().x / 2 ||
		body.getPosition().x >(window.getSize().x - body.getSize().x / 2))
		return true;

	return false;
}

const bool Collider::IsCollidingWithBar(const sf::RectangleShape& barBody)
{
	if (this->body.getGlobalBounds().intersects(barBody.getGlobalBounds()))
		return true;

	return false;
}

