#include <SFML/Graphics.hpp>
#include <iostream>
#include "button.h"

Button::Button(sf::Sprite& s, sf::IntRect u, sf::IntRect p)
    : isPressed{false}
    , sprite{s}
    , unpressedRect{u}
    , pressedRect{p}
{
  sprite.setTextureRect(unpressedRect);
}


void Button::mousePress(int mouseX, int mouseY) {
  sf::Vector2f scl = sprite.getScale();
  sf::Vector2f pos = sprite.getPosition();
  sf::Vector2i size = unpressedRect.size;
  
  float px = pos.x;
  float py = pos.y;
  
  float w = size.x * scl.x;
  float h = size.y * scl.y;
  
  /* DEBUG
  std::cout << "SCALE: "  << scl.x << " " << scl.y << std::endl;
  std::cout << "SIZE: "   << w << " " << h << std::endl;
  std::cout << "BUTTON: " << px << " " << py << std::endl;
  std::cout << "MOUSE: "  << mouseX << " " << mouseY << std::endl;
  std::cout << std::endl;
  */
  
  if (mouseX > px && mouseX < px + w &&
      mouseY > py && mouseY < py + h)
  {
      if (!isPressed) {
         isPressed = true;
         sprite.setTextureRect(pressedRect);
      }
  }
}

void Button::mouseRelease() {
  isPressed = false;
  sprite.setTextureRect(unpressedRect);
}

