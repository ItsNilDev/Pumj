#include <SFML/Graphics/CircleShape.hpp>

struct Obstacle {
	 sf::CircleShape body;
	 float x = 0;
	 float y = 0;
	 float height = 40;
	 float upside = 0;
	 float width = 50;

	 Obstacle(float x, float y) {
		  this->x = x;
		  this->y = y;
		  upside = y - height;
		  body.setPointCount(3);
		  body.setRadius(height);
		  body.setPosition(x, upside);
	 }
};
