#include <SFML/Graphics.hpp>

class TextButton
{
    public:
        bool isPressed;
        
        sf::Text text;
        sf::RectangleShape shape;
        sf::Color unpressedColor;
        sf::Color pressedColor;
        sf::Color textColor;
        
        TextButton(sf::Text);
        TextButton(sf::Text, sf::Color, sf::Color, sf::Color);
        
        void mousePress(int, int);
        void mouseRelease();
        
        void move(sf::Vector2f);
        void draw(sf::RenderWindow&);
};

