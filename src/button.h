#include <SFML/Graphics.hpp>

class Button
{
    public:
        bool isPressed;
        
        sf::Sprite sprite;
        sf::IntRect unpressedRect;
        sf::IntRect pressedRect;

        Button(sf::Sprite&, sf::IntRect, sf::IntRect);
        void mousePress(int, int);
        void mouseRelease();
};
