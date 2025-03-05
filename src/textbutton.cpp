#include <SFML/Graphics.hpp>
#include <iostream>
#include "textbutton.h"

TextButton::TextButton(sf::Text text): isPressed{false}, text{text}
{
  const sf::FloatRect bounds = text.getLocalBounds();
  sf::Vector2f padding = {32, 32};
  shape = sf::RectangleShape(bounds.size + padding);
  
  unpressedColor = sf::Color(200, 200, 200);
  pressedColor = sf::Color(128, 128, 128);
  shape.setFillColor(unpressedColor);
  
  textColor = sf::Color::Black;
  this->text.setFillColor(textColor);
  
  this->shape.setPosition({0, 0});
  this->text.setPosition({16, 8});
}

TextButton::TextButton(sf::Text text, sf::Color uc, sf::Color pc, sf::Color tc)
    : isPressed{false}
    , text{text}
    , unpressedColor{uc}
    , pressedColor{pc}
    , textColor{tc}
{
  const sf::FloatRect bounds = text.getLocalBounds();
  sf::Vector2f padding = {32, 32};
  shape = sf::RectangleShape(bounds.size + padding);
  
  shape.setFillColor(unpressedColor);
  this->text.setFillColor(textColor);
  
  this->shape.setPosition({0, 0});
  this->text.setPosition({16, 8});
}

void TextButton::mousePress(int mouseX, int mouseY) {
  const sf::FloatRect bounds = shape.getGlobalBounds();
  sf::Vector2f mouse( sf::Vector2i(mouseX, mouseY) );
  
  if ( bounds.contains(mouse) )
  {
      if (!isPressed) {
         isPressed = true;
         shape.setFillColor(pressedColor);
      }
  }
}

void TextButton::mouseRelease() {
  isPressed = false;
  shape.setFillColor(unpressedColor);
}

void TextButton::move(sf::Vector2f offset) {
  shape.move(offset);
  text.move(offset);
}

void TextButton::draw(sf::RenderWindow& window)
{
  window.draw(shape);
  window.draw(text);
}

