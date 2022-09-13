#include <SFML/Graphics/RectangleShape.hpp>
struct Floor {
	 sf::RectangleShape rect;
	 float x = 0;
	 float y = 700;
	 float outline_thickness = 10;
	 float upside = y - outline_thickness;

	 Floor() {
		  rect.setSize(sf::Vector2f{6000, 30});
		  rect.setPosition(x, y);
		  rect.setFillColor(sf::Color(252,163,17));
		  rect.setOutlineColor(sf::Color(20,33,61));
		  rect.setOutlineThickness(10);
	 }

};
