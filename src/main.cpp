#include <SFML/Graphics.hpp>
#include <iostream>
#include "button.h"

int main()
{
  // Create window
  auto window = sf::RenderWindow(
    sf::VideoMode({1920u, 1080u}),  // size
    "CMake SFML Project",           // title
    sf::Style::Default,             // style
    sf::State::Fullscreen           // state
  );
  
  // Try to load at 60 frames per second
  window.setFramerateLimit(60);
  
  // Keep track of mouse state
  bool mousePressed;
  
  // Scale for all sprites
  sf::Vector2f scale = {3.f, 3.f};
  
  // Grass background texture (repeating tile)
  sf::Texture grasstex;
  grasstex.setRepeated(true);
  
  // Try to load grass.png
  bool grassyes = grasstex.loadFromFile(
    "assets/grass.png", false, sf::IntRect({0, 0}, {32, 32})
  );
  
  // Create a sprite for the grass background.
  // Divides the size of the screen by the scale of the sprite.
  sf::Sprite gsprite(grasstex);
  gsprite.setScale(scale);
  gsprite.setTextureRect( sf::IntRect({0, 0}, {640, 360}) );

  if (!grassyes)
  { std::cout << "Error! Can't find grass.png" << std::endl; }
  
  // Create texture image for the button
  sf::Texture btntex;
  
  // Try to load button default image
  bool btnyes = btntex.loadFromFile(
    "assets/action-btn.png", false, sf::IntRect({0, 0}, {192, 32})
  );
  
  if (!btnyes)
  { std::cout << "Error! Can't find action-btn.png" << std::endl; }
  
  // The button texture is a 1x2 (row x col) spritesheet for a button.
  // Left to right, the regions are: unpressed state, then pressed state.
  // If the button does not change appearance while the mouse is down,
  // you can also use the unpressed region as the pressed region.
  sf::IntRect unpressedRect({0, 0}, {96, 32});
  sf::IntRect pressedRect({96, 0}, {96, 32});
  
  // Create a sprite for the first button
  sf::Sprite btnsprite(btntex);
  btnsprite.scale(scale);
  btnsprite.move({96, 96});
  Button myButton1(btnsprite, unpressedRect, pressedRect);
  
  // Create a sprite for the second button
  sf::Sprite btnsprite2(btntex);
  btnsprite2.scale(scale);
  btnsprite2.move({450, 96});
  Button myButton2(btnsprite2, unpressedRect, pressedRect);
  
  // Game loop
  while (window.isOpen())
  {
    // Event loop (window events)
    while (const std::optional event = window.pollEvent())
    {
      if (event->is<sf::Event::Closed>()) { window.close(); }
    }
    
    // Mouse pressed?
    if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
    {
      sf::Vector2i mouse = sf::Mouse::getPosition(window);
      
      // if the mouse was previously unpressed (but is now pressed)
      if (!mousePressed)
      {
        //std::cout << "MOUSE PRESSED" << std::endl;
        mousePressed = true;
        
        myButton1.mousePress(mouse.x, mouse.y);
        myButton2.mousePress(mouse.x, mouse.y);
      }
    }
    else {
      // If the mouse was previously pressed (but is now not)
      if (mousePressed)
      {
        //std::cout << "MOUSE RELEASED" << std::endl;
        mousePressed = false;
        
        myButton1.mouseRelease();
        myButton2.mouseRelease();
      }
    }
    
    window.clear();
    window.draw(gsprite); // Grass background
    
    // Buttons
    window.draw(myButton1.sprite);
    window.draw(myButton2.sprite);
    
    window.display();
  }
}

