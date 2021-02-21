#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>

//singleton class
class music  {
public:
	~music();
	static music& instance();
	const sf::SoundBuffer& getSoundbuffer() const;

private:
	music();
	music(const music&) = default;
	music& operator=(const music&) = default;
	sf::SoundBuffer m_soundbuffer;
};