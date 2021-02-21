#pragma once
#include <SFML/Graphics.hpp>
#include "gameObject.h"
#include "macros.h"


class staticObj : public gameObject {
public:
	staticObj(const sf::Sprite& sprite);
	virtual void draw(sf::RenderWindow& window) override;
	bool getExistens() const;
	void setExistens(bool booliany);
	virtual void handleCollision(gameObject& obj, bool WhileFalling = false) override;
	virtual void handleCollision(enemy& enemy, bool WhileFalling = false) override;
	virtual void handleCollision(wall& wall, bool WhileFalling = false) override;
	virtual void handleCollision(ladder& ladder, bool WhileFalling = false) override;
	virtual void handleCollision(pole& pole, bool WhileFalling = false) override;
	virtual void handleCollision(Present& Present, bool WhileFalling = false) override;
	virtual void handleCollision(coin& coin, bool WhileFalling = false) override;

private:
	bool m_exists;//true = display, false = do not display
};