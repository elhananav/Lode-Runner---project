#include "textures.h"

textures::~textures()
{
}

textures::textures()
{//constructor - load all textures into the vector
	m_font.loadFromFile("font.ttf");

	auto tex = sf::Texture();

	tex.loadFromFile("player.png");
	m_textures.push_back(tex);

	tex.loadFromFile("enemy.png");
	m_textures.push_back(tex);

	tex.loadFromFile("coin.png");
	m_textures.push_back(tex);

	tex.loadFromFile("wall.png");
	m_textures.push_back(tex);

	tex.loadFromFile("pole.png");
	m_textures.push_back(tex);

	tex.loadFromFile("ladder.png");
	m_textures.push_back(tex);

	tex.loadFromFile("present.png");
	m_textures.push_back(tex);

	tex.loadFromFile("menu-back.png");
	m_textures.push_back(tex);

	tex.loadFromFile("background.png");
	m_textures.push_back(tex);

	tex.loadFromFile("gameoverBack.png");
	m_textures.push_back(tex);

	tex.loadFromFile("playButton.png");
	m_textures.push_back(tex);

	tex.loadFromFile("exitButton.png");
	m_textures.push_back(tex);

}//end constructor 

textures& textures::instance()
{//get the single textures object
	static textures tex;
	return tex;
}//end instance

const sf::Texture& textures::getTexture(simbolIndex symbol) const
{//return the texture according to sent simbolIndex
	return m_textures[symbol];
}//end getTexture

const sf::Font& textures::getFont() const
{
	return m_font;
}//end getFont


