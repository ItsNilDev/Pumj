#include <SFML/Graphics/CircleShape.hpp>

enum Spells {
	 SLOW = 0,
	 FAST
};

struct Spell {
	 sf::CircleShape body;
	 Spells type;
	 float x = 0;
	 float y = 0;
	 float height = 20;
	 float upside = 0;
	 bool collected = false;
	 Spell(float x, float y, Spells type) {
		  this->x = x;
		  this->y = y;
		  this->type = type;
		  upside = y - 50;
		  switch(type) {
		  case Spells::FAST:
			   body.setFillColor(sf::Color::Green);
			   break;
		  case Spells::SLOW:
			   body.setFillColor(sf::Color::Cyan);
			   break;
		  }
		  body.setPointCount(100.0f);
		  body.setRadius(height);
		  body.setPosition(x, upside);
	 }
};
