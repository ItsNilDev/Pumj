#include <SFML/Graphics.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Image.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderStates.hpp>
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

bool isCollied(const sf::Shape& p, const sf::Shape& o) {
	 return p.getGlobalBounds().intersects(o.getGlobalBounds());
}

int main() {
	 sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Pumj");
	 window.setFramerateLimit(60);
	 sf::Font font;
	 font.loadFromFile("assets/z.ttf");
	 bool gameover = false;

	 sf::View view(sf::Vector2f(0, 0), sf::Vector2f(1600, 800));

	 // player
	 Player player;


	 // floor
	 Floor floor;

	 Obstacle obstacle(2000, floor.upside);
	 Obstacle obstacle2(2400, floor.upside);
	 Obstacle obstacle3(2600, floor.upside);

	 Spell spell1(1400, floor.upside, Spells::FAST);

	 while (window.isOpen()) {
		  sf::Event event;
		  while (window.pollEvent(event)) {
			   if (event.type == sf::Event::Closed)
					window.close();
		  }
		  if(!gameover) {
			   window.clear(sf::Color(20, 20, 20));
			   window.setView(view);
			   window.draw(player.body);
			   window.draw(obstacle.body);
			   window.draw(obstacle2.body);
			   window.draw(obstacle3.body);
			   if(!spell1.collected) {
					window.draw(spell1.body);
			   }

			   view.setCenter(sf::Vector2f(player.GetxPosition() + 300, 500));
			   player.body.setPosition(player.x, player.y);

			   // Player-Floor Collision detection /////////////////////////////////////////////////////////
			   if(isCollied(player.body, floor.rect)) {
					player.y = floor.upside - player.height;
					player.vertical_speed = 0;
					player.on_ground = true;
			   } else {
					player.vertical_speed += GRAVITY_SPEED;
					player.y += player.vertical_speed;
			   }

			   // Player-Obstacle Collision detection /////////////////////////////////////////////////////////
			   if(isCollied(player.body, obstacle.body)
				  || isCollied(player.body, obstacle2.body)
				  || isCollied(player.body, obstacle3.body)) {
					gameover = true;
			   }

			   // Player-Spell Collision //////////////////////////////////////////////
			   if(isCollied(player.body, spell1.body) && true == !spell1.collected) {
					player.horizontal_speed += 5;
					spell1.collected = true;
			   }

			   // Jump Setup /////////////////////////////////////////////////////////
			   if(sf::Keyboard::isKeyPressed(sf::Keyboard::U) && player.on_ground) {
					player.vertical_speed = -20;
					player.y += player.vertical_speed;
					player.on_ground = false;
			   }

			   // moving player at a constant rate in x-axis /////////////////////////////////////////////////////////
			   player.x += player.horizontal_speed;

			   // Player Falling Detection  ////////////////////////////////////////////////////
			   if(player.y >= 800) {
					gameover = true;
			   }

			   window.draw(floor.rect);
			   window.display();
		  } else {
			   // Game Over Handle
			   window.clear();
			   window.setView(window.getDefaultView());
			   sf::Text gameover_text("Game Over", font, 150);
			   gameover_text.setPosition(SCREEN_WIDTH/2 - 250, SCREEN_HEIGHT/2);
			   gameover_text.setFillColor(sf::Color::Red);
			   player.x = PLAYER_START_POSITION_X;
			   player.y = PLAYER_START_POSITION_Y;
			   player.horizontal_speed = 10;
			   spell1.collected = false;
			   window.draw(gameover_text);
			   window.display();
			   if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
					gameover = false;
			   }
		  }
	 }

}
