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
  const sf::FloatRect bounds = sprite.getGlobalBounds();
  sf::Vector2f mouse( sf::Vector2i(mouseX, mouseY) );
  
  if ( bounds.contains(mouse) )
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

