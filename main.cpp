#include <stdlib.h>
#include <vector>
#include <iostream>
#include <algorithm>
#include <thread>
#include <chrono>
#include <fstream>
#include <string>
#include "listener.h"
#include "functionality.h" 
#include <SFML/Graphics.hpp>

int main(int argc, char **argv) {
    sf::VideoMode vm(1036, 569);
    sf::RenderWindow window(vm, "Voice Assistant", sf::Style::Default);

    std::cout << "Press 'l' to start listening..." << std::endl;
    Functionality functionality;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed || (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape))
            {
                window.close();
            }
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::L) {
                std::cout << "Listening..." << std::endl;

                // from listener.cpp
                int predict = Listener::start_main_listen();
                
                // from functionality.cpp
                functionality.executeCommand(predict);
                
                std::cout << "Press 'l' to start listening again..." << std::endl;
            }
        }

        window.clear();

        window.display();
    }

    return 0;
}