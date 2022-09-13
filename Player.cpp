#include <SFML/Graphics/RectangleShape.hpp>
#include "constants.h"

struct Player {
	 sf::RectangleShape body;
	 float width = 50;
	 float height = 50;
	 float x = PLAYER_START_POSITION_X;
	 float y = PLAYER_START_POSITION_Y;
	 float horizontal_speed = 10;
	 float vertical_speed = 0;
	 bool on_ground = false;

	 float GetxPosition() {
		  return body.getPosition().x;
	 }

	 Player() {
		  body.setSize(sf::Vector2f{width, height});
		  body.setPosition(x, y);
		  body.setFillColor(sf::Color(255,89,94));
	 }
};
