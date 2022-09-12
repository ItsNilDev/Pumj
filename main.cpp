#include <SFML/Graphics.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Image.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/View.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <iostream>
#include <limits>
#include <spdlog/spdlog.h>

const float SCREEN_WIDTH = 1600;
const float SCREEN_HEIGHT = 800;
const float PLAYER_START_POSITION_X = 300;
const float PLAYER_START_POSITION_Y = SCREEN_HEIGHT / 2;
const float GRAVITY_SPEED = 1.5;


struct Player {
	 sf::RectangleShape rect;
	 float width = 50;
	 float height = 50;
	 float x = PLAYER_START_POSITION_X;
	 float y = PLAYER_START_POSITION_Y;
	 float vertical_speed = 0;
	 bool on_ground = false;

	 float GetxPosition() {
		  return rect.getPosition().x;
	 }

	 sf::Vector2f GetmiddlePosition() {
		  return sf::Vector2f(x + width/2, y + height/2);
	 }

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
	 float upside = y - outline_thickness;

	 Floor() {
		  rect.setSize(sf::Vector2f{6000, 30});
		  rect.setPosition(x, y);
		  rect.setFillColor(sf::Color(252,163,17));
		  rect.setOutlineColor(sf::Color(20,33,61));
		  rect.setOutlineThickness(10);
	 }

};

struct Obstacle {
	 sf::CircleShape trian;
	 float x = 0;
	 float y = 0;
	 float height = 40;
	 float upside = 0;
	 float width = 50;
	 float height2 = 50;
	 sf::Vector2f GetmiddlePosition() {
		  return sf::Vector2f(x + width/2, y + height2/2 - 50);
	 }

	 Obstacle(float x, float y) {
		  this->x = x;
		  this->y = y;
		  upside = y - height2;
		  trian.setPointCount(3);
		  trian.setRadius(height);
		  trian.setPosition(x, upside);
	 }
};

bool iscollied(const Player& p, const Obstacle& o) {
	 return p.rect.getGlobalBounds().intersects(o.trian.getGlobalBounds());
}

int main() {
	 sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Pumj");
	 window.setFramerateLimit(60);
	 // sf::Image map;
	 // map.loadFromFile("assets/map.png");
	 sf::Texture texture;
	 texture.loadFromFile("assets/background.png");
	 sf::Sprite background;
	 background.setTexture(texture);
	 background.setScale(sf::Vector2f{1.6, 1.2});
	 sf::Font font;
	 font.loadFromFile("assets/z.ttf");
	 bool gameover = false;

	 sf::View view(sf::Vector2f(0, 0), sf::Vector2f(1600, 800));

	 // player
	 Player player;


	 // floor
	 Floor floor;

	 Obstacle obstacle(1600, floor.upside);
	 Obstacle obstacle2(2000, floor.upside);
	 Obstacle obstacle3(2200, floor.upside);

	 while (window.isOpen()) {
		  sf::Event event;
		  while (window.pollEvent(event)) {
			   if (event.type == sf::Event::Closed)
					window.close();
		  }
		  if(!gameover) {
			   window.clear();
			   window.setView(view);
			   window.draw(background);
			   window.draw(player.rect);
			   window.draw(obstacle.trian);
			   window.draw(obstacle2.trian);
			   window.draw(obstacle3.trian);

			   view.setCenter(sf::Vector2f(player.GetxPosition() + 300, 500));
			   player.rect.setPosition(player.x, player.y);

			   // Player-Floor Collision detection /////////////////////////////////////////////////////////
			   if(player.rect.getGlobalBounds().intersects(floor.rect.getGlobalBounds())) {
					player.y = floor.upside - player.height;
					player.vertical_speed = 0;
					player.on_ground = true;
			   } else {
					player.vertical_speed += GRAVITY_SPEED;
					player.y += player.vertical_speed;
			   }

			   // Player-Obstacle Collision detection /////////////////////////////////////////////////////////
			   if(iscollied(player, obstacle)
				  || iscollied(player, obstacle2)
				  || iscollied(player, obstacle3)) {
					gameover = true;
				  }

			   // Jump Setup /////////////////////////////////////////////////////////
			   if(sf::Keyboard::isKeyPressed(sf::Keyboard::U) && player.on_ground) {
					player.vertical_speed = -20;
					player.y += player.vertical_speed;
					player.on_ground = false;
			   }

			   // moving player at a constant rate in x-axis /////////////////////////////////////////////////////////
			   player.x += 10;

			   window.draw(floor.rect);
			   window.display();
		  } else {
			   window.clear();
			   window.setView(window.getDefaultView());
			   sf::Text gameover_text("Game Over", font, 150);
			   gameover_text.setPosition(SCREEN_WIDTH/2 - 250, SCREEN_HEIGHT/2);
			   gameover_text.setFillColor(sf::Color::Red);
			   window.draw(gameover_text);
			   window.display();
			   if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
					player.x = PLAYER_START_POSITION_X;
					player.y = PLAYER_START_POSITION_Y;
					gameover = false;
			   }
		  }
	 }

}
