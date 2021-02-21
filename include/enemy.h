#pragma once
#include <SFML/Graphics.hpp>
#include "moveable.h"

//abstract class
class enemy : public moveable {
public:
	enemy(const sf::Sprite& sprite);
	virtual void setEDirection() = 0;

private:
};