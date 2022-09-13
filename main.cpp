#include <SFML/Graphics.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/View.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <iostream>
#include <spdlog/spdlog.h>
#include "Player.cpp"
#include "constants.h"
#include "Floor.cpp"
#include "Spells.cpp"
#include "Obstacle.cpp"

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
	 Obstacle obstacle3(3000, floor.upside);
	 Obstacle obstacle4(3400, floor.upside);
	 Obstacle obstacle5(3800, floor.upside);

	 Spell spell1(1400, floor.upside, Spells::FAST);
	 Spell spell2(3200, floor.upside, Spells::SLOW);

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
			   window.draw(obstacle4.body);
			   window.draw(obstacle5.body);
			   if(!spell1.collected) {
					window.draw(spell1.body);
			   }

			   if(!spell2.collected) {
					window.draw(spell2.body);
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
				  || isCollied(player.body, obstacle3.body)
				  || isCollied(player.body, obstacle4.body)
				  || isCollied(player.body, obstacle5.body)) {
					gameover = true;
			   }

			   // Player-Spell Collision //////////////////////////////////////////////
			   if(isCollied(player.body, spell1.body) && true == !spell1.collected) {
					player.horizontal_speed += 5;
					spell1.collected = true;
			   }
			   if(isCollied(player.body, spell2.body) && true == !spell2.collected) {
					player.horizontal_speed -= 5;
					spell2.collected = true;
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
			   spell2.collected = false;
			   window.draw(gameover_text);
			   window.display();
			   if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
					gameover = false;
			   }
		  }
	 }

}
