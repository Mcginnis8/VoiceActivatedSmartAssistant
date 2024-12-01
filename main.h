#ifndef MAIN_H
#define MAIN_H

#include <SFML/Graphics.hpp>
#include <string>

extern sf::RenderWindow window;
extern sf::Font font;
extern sf::Text text;

void updateSFMLText(const std::string& displayText);

#endif