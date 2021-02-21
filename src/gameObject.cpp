#include "gameObject.h"

gameObject::gameObject(const sf::Sprite& sprite) :m_sprite(sprite)
{
}//end constructor

const sf::Vector2f& gameObject::getPosition() const
{
	return m_sprite.getPosition();
}//end getPosition

sf::Vector2f gameObject::getSize() const
{
	return sf::Vector2f(m_sprite.getGlobalBounds().width, m_sprite.getGlobalBounds().height);
}//end getSize

void gameObject::setPosition(const sf::Vector2f& location)
{
	m_sprite.setPosition(location);
}//end setPosition

void gameObject::setSize(const sf::Vector2f& size)
{
	m_sprite.setScale(size.x / m_sprite.getLocalBounds().width,
					  size.y / m_sprite.getLocalBounds().height);
}//end setSize

bool gameObject::collidesWith(const gameObject& obj) const
{
	return m_sprite.getGlobalBounds().intersects(obj.m_sprite.getGlobalBounds());
}//end collidesWith

const sf::Sprite& gameObject::getSprite() const
{
	return m_sprite;
}//end getSprite
