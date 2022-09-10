#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Image.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <iostream>

const float SCREEN_WIDTH = 1600;
const float SCREEN_HEIGHT = 800;
const float PLAYER_START_POSITION = 300;
const float GRAVITY_SPEED = 1.5;


struct Player {
	 sf::RectangleShape rect;
	 float width = 50;
	 float height = 50;
	 float x = PLAYER_START_POSITION;
	 float y = SCREEN_HEIGHT / 2;
	 float vertical_speed = 0;
	 bool on_ground = false;
	 Player() {
		  // sf::RectangleShape rect(sf::Vector2f{50,50});
		  rect.setSize(sf::Vector2f{width, height});
		  rect.setPosition(x, y);
		  rect.setFillColor(sf::Color(255,89,94));
	 }
};

struct Floor {
	 sf::RectangleShape rect;
	 float x = 0;
	 float y = 700;
	 float outline_thickness = 10;
	 Floor() {
		  rect.setSize(sf::Vector2f{2500, 30});
		  rect.setPosition(x, y);
		  rect.setFillColor(sf::Color(252,163,17));
		  rect.setOutlineColor(sf::Color(20,33,61));
		  rect.setOutlineThickness(10);
	 }

};

int main() {
	 sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "SFML works!");
	 window.setFramerateLimit(60);
	 // sf::Image map;
	 // map.loadFromFile("assets/map.png");
	 sf::Texture texture;
	 texture.loadFromFile("assets/background.png");
	 sf::Sprite sprite;
	 sprite.setTexture(texture);
	 sprite.setScale(sf::Vector2f{1.6, 1.2});

	 // player
	 Player player;

	 // floor
	 Floor floor;

	 while (window.isOpen()) {
		  sf::Event event;
		  while (window.pollEvent(event)) {
			   if (event.type == sf::Event::Closed)
					window.close();
		  }
		  window.clear();

		  window.draw(sprite);
		  window.draw(player.rect);

		  player.rect.setPosition(player.x, player.y);
		  // std::cout << "Player:" << player.y
		  // << "Floor: " << floor.y  << std::endl;
		  if(player.y + player.height >= floor.y - floor.outline_thickness) {
			   player.y = floor.y - player.height - floor.outline_thickness;
			   player.vertical_speed = 0;
			   player.on_ground = true;
		  } else {
			   player.vertical_speed += GRAVITY_SPEED;
			   player.y += player.vertical_speed;
		  }

		  if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && player.on_ground) {
			   player.vertical_speed = -20;
			   player.y += player.vertical_speed;
			   player.on_ground = false;
		  }
		  window.draw(floor.rect);

		  window.display();
	 }

	 return 0;
}
