#include <SFML/Graphics.hpp>
#include <iostream>

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
  
  bool mousePressed;
  
  // Grass background texture (repeating tile)
  sf::Texture grasstex;
  grasstex.setRepeated(true);
  
  // Try to load grass.png
  bool grassyes = grasstex.loadFromFile(
    "grass.png", false, sf::IntRect({0, 0}, {32, 32})
  );
  
  sf::Vector2f scale = {3.f, 3.f};
  
  // Create a sprite for the grass background.
  // Divides the size of the screen by the scale of the sprite.
  sf::Sprite gsprite(grasstex); // start empty, change later
  gsprite.setScale(scale);
  gsprite.setTextureRect(sf::IntRect({0, 0}, {640, 360}));
  
  if (grassyes) { gsprite.setTexture(grasstex); }
  else          { std::cout << "Error! Can't find grass.png" << std::endl; }
  
  // Create texture image for the button
  sf::Texture btntex;
  
  // Try to load button default image
  bool btnyes = btntex.loadFromFile(
    "action-btn.png", false, sf::IntRect({0, 0}, {192, 32})
  );
  
  sf::Sprite btnsprite(btntex);
  btnsprite.setScale(scale);
  btnsprite.setPosition({96, 96});
  
  sf::IntRect unpressedRect({0, 0}, {96, 32});
  sf::IntRect pressedRect({96, 0}, {96, 32});
  btnsprite.setTextureRect(unpressedRect);
  bool buttonPressed;
  
  if (btnyes)  { btnsprite.setTexture(btntex); }
  else { std::cout << "Error! Can't find action-btn.png" << std::endl; }
  
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
      sf::Vector2f btn = btnsprite.getPosition();
      float w = 96 * scale.x, h = 32 * scale.y;
      
      // if the mouse is currently pressed (but was previously not)
      if (!mousePressed)
      {
        mousePressed = true;
        //std::cout << "MOUSE PRESSED" << std::endl;
        
        // If the mouse is inside the button
        if (mouse.x > btn.x && mouse.x < btn.x + w &&
            mouse.y > btn.y && mouse.y < btn.y + h)
        {
          // If the button was not pressed (but is now)
          if (!buttonPressed) {
            buttonPressed = true;
            btnsprite.setTextureRect(pressedRect);
          }
        }
      }
    }
    else {
      // If the mouse is no longer pressed (but was previously)
      if (mousePressed)
      {
        //std::cout << "MOUSE RELEASED" << std::endl;
        mousePressed = false;
      }
      
      // If the button is no longer pressed (but was previously)
      if (buttonPressed)
      {
        buttonPressed = false;
        btnsprite.setTextureRect(unpressedRect);
      }
    }
    
    window.clear();
    
    if (grassyes) { window.draw(gsprite); }
    if (btnyes)  { window.draw(btnsprite); }
    
    window.display();
  }
}

