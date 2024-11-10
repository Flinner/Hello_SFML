
#include <SFML/Graphics.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/WindowStyle.hpp>
#include <cmath>
#include <cstdlib>
#include <iostream>

int main() {
  const uint WINDOW_WIDTH = 1024;
  const uint WINDOW_HEIGHT = 200u;
  auto window = sf::RenderWindow({WINDOW_WIDTH, WINDOW_HEIGHT}, "Hello SFML");
  window.setFramerateLimit(60);

  sf::Sprite sprite;
  sf::Texture texture;
  uint frame = 0;
  auto texturePath = "assets/WalkingMan.png";
  if (!texture.loadFromFile(texturePath)) {
    // error...
    std::cerr << "Texture couldn't be loaded! " << texturePath;
    return EXIT_FAILURE;
  }
  // Our texture's image is 1200x1200
  // I will scale it so it fits in the window
  // I take `min` as it is best fit... (not really sure)
  while (window.isOpen()) {
    ////////////////
    // EVENT LOOP //
    ////////////////
    for (auto event = sf::Event(); window.pollEvent(event);) {
      if (event.type == sf::Event::Closed) {
        window.close();
      }
      // if (event.type == sf::Event::KeyPressed)
      //   if (event.key.scancode == sf::Keyboard::Scan::Space)
      //     ;
    }

    window.clear(sf::Color::White);
    ///////////////
    // DRAW HERE //
    ///////////////
    double window_x = window.getSize().x;
    double window_y = window.getSize().y;

    double texture_height = texture.getSize().y;
    double texture_width = texture.getSize().x;

    double scaling_x = window_x / texture_width;
    double scaling_y = window_y / texture_height * 2;

    frame++;

    sprite.setTexture(texture);
    // advanced black magic bit manipulaions
    uint sprite_left = ((frame >> 3) & 7) * texture_width / 8;
    sprite.setTextureRect(sf::IntRect(sprite_left, 0, //
                                      texture_width / 8, texture_height));
    sprite.setScale(sf::Vector2f(scaling_x, scaling_y));

    // trying to center the ~bastard~ gentleman
    // nah I give up
    // sprite.setOrigin(texture_width / 60.0 * (((frame >> 3) & 7) + 1), 0);
    sprite.setPosition(1.5 * (frame & int(pow(2, floor(log2(window_x))) - 1)),
                       0);
    window.draw(sprite);
    window.display();
  }
}
