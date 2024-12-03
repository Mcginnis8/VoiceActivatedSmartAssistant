/*
Authors: Cole McGinnis, Alexander Snapp, John Donahoe
Class: ECE 6122 A
Last Date Modified: 12/3/24

Description:

Main Class header file. Allows for Functionality to call updateSFMLText.
*/
#ifndef MAIN_H
#define MAIN_H

#include <SFML/Graphics.hpp>
#include <string>

extern sf::RenderWindow window;
extern sf::Font font;
extern sf::Text text;

void updateSFMLText(const std::string& displayText);

#endif