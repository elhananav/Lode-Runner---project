#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

const unsigned int BOARDSIZE_X = 1200;
const unsigned int BOARDSIZE_Y = 750;
const sf::Vector2f BOARDSIZE(1200, 750);
const int ENEMY_SPEED = 200;
const int PLAYER_SPEED = 350;

enum simbolIndex { PLAYER, ENEMY, COIN, WALL, POLE, LADDER, PRESENT,MENU_BACKGROUND, GAME_BACKGROUND, GAMEOVER_BACKGROUND, PLAY_BUTTON, EXIT_BUTTON  };
enum excavateSide { left, right };