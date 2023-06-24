#ifndef FIRST_SCREEN_HPP
#define FIRST_SCREEN_HPP

#include <SFML/Graphics.hpp>
#include <iostream>

class FirstScreen
{
public:
    FirstScreen(sf::RenderWindow& window, int& activeScreen);

    void handleEvent(const sf::Event& event);
    void update();
    void render();

private:
    sf::RenderWindow& window;
    int& activeScreen;
    sf::Font font;
    sf::Texture backgroundTexture;
    sf::Sprite backgroundSprite;
    sf::RectangleShape button;
    sf::Text buttonText;
    sf::RectangleShape titleRectangle;
    sf::Text titleText;
    sf::RectangleShape nameLabelRectangle;
    sf::Text nameLabel;
    sf::RectangleShape nameInputRectangle;
    sf::Text nameInputText;
};

#endif // FIRST_SCREEN_HPP
