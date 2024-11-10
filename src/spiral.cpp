#include <SFML/Graphics.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/WindowStyle.hpp>
#include <cstdlib>
#include <iostream>

int main() {
  const uint WINDOW_WIDTH = 800u;
  const uint WINDOW_HEIGHT = 800u;
  auto window = sf::RenderWindow({WINDOW_WIDTH, WINDOW_HEIGHT}, "Hello SFML");
  window.setFramerateLimit(60);

  int rotate_on = 1;
  double rotate_speed = 10;
  sf::Sprite sprite;
  sf::Texture texture;
  auto texturePath = "assets/spiral.png";
  if (!texture.loadFromFile(texturePath)) {
    // error...
    std::cerr << "Texture couldn't be loaded! " << texturePath;
    return EXIT_FAILURE;
  }
  // Our texture's image is 1200x1200
  // I will scale it so it fits in the window
  // I take `min` as it is best fit... (not really sure)
  while (window.isOpen()) {
    double scaling =
        std::min(double(window.getSize().x) / double(texture.getSize().x),
                 double(window.getSize().y) / double(texture.getSize().y));
    ////////////////
    // EVENT LOOP //
    ////////////////
    for (auto event = sf::Event(); window.pollEvent(event);) {
      if (event.type == sf::Event::Closed) {
        window.close();
      }
      if (event.type == sf::Event::KeyPressed) {
        if (event.key.scancode == sf::Keyboard::Scan::Space) {
          rotate_on = rotate_on ^ 1;
        }
      }
    }

    window.clear(sf::Color::White);
    ///////////////
    // DRAW HERE //
    ///////////////

    // Note: After scaling, the image is 600x600
    sprite.setTexture(texture);
    sprite.setScale(sf::Vector2f(scaling, scaling));
    // 600 - WINDOW_WIDTH/2 = 200
    // 600 - WINDOW_HEIGHT/2 = 250
    sprite.setPosition(200, 200);
    // 1200/2 = 600
    sprite.setOrigin(600, 600);
    sprite.rotate(rotate_on ? rotate_speed : 0);
    // std::cout << sprite.getPosition().y << "\n";

    window.draw(sprite);
    window.display();
  }
}
