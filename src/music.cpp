#include "music.h"

music::music()
{
	m_soundbuffer.loadFromFile("backgroundSound.ogg");
}//end constructor

music::~music()
{
}//end destructor

music& music::instance()
{//get the single music object
	static music muz;
	return muz;
}//end instance

const sf::SoundBuffer& music::getSoundbuffer() const
{
	return m_soundbuffer;
}//end getSoundbuffer

