#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "macros.h"

//singleton class
class textures  {
public:
	~textures();
	static textures& instance();
	const sf::Texture& getTexture(simbolIndex symbol) const;
	const sf::Font& getFont() const;

private:
	textures();
	textures(const textures&) = default;
	textures& operator=(const textures&) = default;
	std::vector <sf::Texture> m_textures;
	sf::Font m_font;
};