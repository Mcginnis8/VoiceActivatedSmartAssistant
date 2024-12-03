#include "main.h"
#include <stdlib.h>
#include <vector>
#include <iostream>
#include <algorithm>
#include <thread>
#include <chrono>
#include <fstream>
#include <string>
#include <mutex>
#include "listener.h"
#include "functionality.h"

sf::VideoMode vm(1036, 569);
sf::RenderWindow window(vm, "Voice Assistant", sf::Style::Default);
sf::Font font;
sf::Text text;
sf::Text bottomText;
sf::Text timeText;

std::string currentTimeStr;
std::mutex timeMutex;

void updateSFMLText(const std::string& displayText) {
    text.setString(displayText);
    window.clear();
    window.draw(text);
    window.draw(bottomText);
    window.draw(timeText);
    window.display();
}

void displayCurrentTime() {
    std::thread timeThread([]() {
        while (true) {
            auto now = std::chrono::system_clock::now();
            std::time_t currentTime = std::chrono::system_clock::to_time_t(now);
            std::string timeStr = std::ctime(&currentTime);
            timeStr.pop_back(); // Remove the newline character

            {
                std::lock_guard<std::mutex> lock(timeMutex);
                currentTimeStr = "Current Time: " + timeStr;
            }

            std::this_thread::sleep_for(std::chrono::seconds(1));
        }
    });
    timeThread.detach();
}

int main(int argc, char **argv) {
    if (!font.loadFromFile("fonts/KOMIKAP_.ttf")) {
        std::cerr << "Failed to load font." << std::endl;
        return -1;
    }

    text.setFont(font);
    text.setCharacterSize(20);
    text.setFillColor(sf::Color::White);
    text.setPosition(20, 20);

    bottomText.setFont(font);
    bottomText.setCharacterSize(20);
    bottomText.setFillColor(sf::Color::Green);
    bottomText.setPosition(20, 520);
    bottomText.setString("");

    timeText.setFont(font);
    timeText.setCharacterSize(20);
    timeText.setFillColor(sf::Color::Yellow);

    std::string displayText = "Press 'l' to start listening...";
    text.setString(displayText);
    std::cout << displayText << std::endl;

    Functionality functionality;

    displayCurrentTime();

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed || 
               (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)) {
                window.close();
            }
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::L) {
                bottomText.setString("");
                updateSFMLText("Listening...");
                std::cout << "Listening..." << std::endl;

                int predict = Listener::start_main_listen();
                functionality.executeCommand(predict);
                
                bottomText.setString("Press 'l' to start listening again...");
                std::cout << displayText << std::endl;
            }
        }

        {
            std::lock_guard<std::mutex> lock(timeMutex);
            timeText.setString(currentTimeStr);
        }
        timeText.setPosition(vm.width - timeText.getGlobalBounds().width - 20, 520);

        window.clear();
        window.draw(text);
        window.draw(bottomText);
        window.draw(timeText);
        window.display();
    }

    return 0;
}