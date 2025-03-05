#include <SFML/Graphics.hpp>
#include <iostream>

#include "button.h"
#include "textbutton.h"

sf::Color getColor(int color)
{
  switch (color)
  {
  case 0: return sf::Color::Black;
  case 1: return sf::Color::White;
  case 2: return sf::Color::Red;
  case 3: return sf::Color::Green;
  case 4: return sf::Color::Blue;
  case 5: return sf::Color::Yellow;
  case 6: return sf::Color::Magenta;
  case 7: return sf::Color::Cyan;
  default: return sf::Color::Black;
  }
}

int main()
{
  // Create window
  auto window = sf::RenderWindow(
    sf::VideoMode({1920u, 1080u}),  // size
    "CMake SFML Project",           // title
    sf::Style::Default,             // style
    sf::State::Fullscreen           // state
  );
  
  // Set the viewport to match the screen (fixes stretching in fullscreen)
  window.setView( sf::View(sf::FloatRect({0, 0}, {1920, 1080})) );
  
  // Try to load at 60 frames per second
  window.setFramerateLimit(60);
  
  // Keep track of mouse state
  bool mousePressed;
  
  // Scale for sprites
  sf::Vector2f scale = {3.f, 3.f};
  
  // Grass background texture (repeating tile)
  sf::Texture grasstex;
  grasstex.setRepeated(true);
  
  // Try to load grass.png
  bool grassyes = grasstex.loadFromFile(
    "assets/grass.png", false, sf::IntRect({0, 0}, {32, 32})
  );
  
  if (!grassyes)
  { std::cout << "Error! Can't find grass.png" << std::endl; }
  
  // Create a sprite for the grass background.
  // Divides the size of the screen by the scale of the sprite.
  sf::Sprite gsprite(grasstex);
  gsprite.setScale(scale);
  gsprite.setTextureRect( sf::IntRect({0, 0}, {640, 360}) );
  
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
  btnsprite.move({645, 96});
  Button myButton1(btnsprite, unpressedRect, pressedRect);
  
  // Create a sprite for the second button
  sf::Sprite btnsprite2(btntex);
  btnsprite2.scale(scale);
  btnsprite2.move({995, 96});
  Button myButton2(btnsprite2, unpressedRect, pressedRect);
  
  // Load font and create text button
  sf::Font font("assets/fonts/ProcessingSans-Bold.ttf");
  sf::Text text(font, "Click the buttons!");
  TextButton textbutton(text);
  
  const sf::Vector2f tsize = text.getLocalBounds().size;
  textbutton.move({1920/2 - tsize.x/2 - 15, 30});
  
  // Create a hexagon
  sf::CircleShape hexagon(300, 6);
  hexagon.setOrigin( hexagon.getGeometricCenter() );
  hexagon.setPosition({1920/2, 1080/2});
  
  hexagon.setOutlineThickness(3);
  hexagon.setOutlineColor(sf::Color::Red);
  
  // Create a circle
  sf::CircleShape circle(50, 50);
  circle.setOrigin( circle.getGeometricCenter() );
  circle.setPosition({1920/2, 1080/2});
  
  circle.setOutlineThickness(3);
  circle.setOutlineColor(sf::Color::Red);
  
  int color = 0;
  hexagon.setFillColor( getColor(color) );
  
  sf::Clock clock;
  
  // Game loop
  while (window.isOpen())
  {
    // Event loop (window events)
    while (const std::optional event = window.pollEvent())
    {
      if (event->is<sf::Event::Closed>()) { window.close(); }
    }
    
    // Rotate hexagon
    // Left button: go left, right button: go right, no button: no go
    float rotspeed = myButton1.isPressed ? -45 : myButton2.isPressed ? 45 : 0;
    float delta = clock.restart().asSeconds();
    hexagon.rotate( sf::degrees(rotspeed * delta) );
    
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
        textbutton.mousePress(mouse.x, mouse.y);
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
        
        if (textbutton.isPressed)
        {
          color = (color + 1) % 8;
          hexagon.setFillColor( getColor(color) );
        }
        
        textbutton.mouseRelease();
      }
    }
    
    window.clear();
    window.draw(gsprite); // Grass background
    
    // Buttons
    window.draw(myButton1.sprite);
    window.draw(myButton2.sprite);
    textbutton.draw(window);
    
    // Hexagon
    window.draw(hexagon);
    window.draw(circle);
    
    window.display();
  }
}

