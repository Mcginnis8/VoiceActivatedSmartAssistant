/*
Authors: Cole McGinnis, Alexander Snapp, John Donahoe
Class: ECE 6122 A
Last Date Modified: 12/3/24

Description:

Main file for the Voice Assistant. This file controls the SFML
Window and the overall functionality of the Assistant.
*/
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

sf::CircleShape pulseCircle(50); // Initial radius of 50 pixels
std::mutex pulseMutex;

// Function that can be called in functionality.cpp to update the SFML window
void updateSFMLText(const std::string& displayText)
{
    text.setString(displayText);
    window.clear();
    window.draw(text);
    window.draw(bottomText);
    window.draw(timeText);
    window.draw(pulseCircle); // Draw the pulse circle
    window.display();
}

// Function that displays the current time in the bottom right corner of the window
// Using the thread library to always run concurrently.
void displayCurrentTime()
{
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

// Function that creates a pulse effect on the circle in the center of the window
void pulseCircleEffect()
{
    float initialRadius = pulseCircle.getRadius();
    sf::Clock clock;
    while (clock.getElapsedTime().asSeconds() < 3.0f)
    {
        float elapsedTime = clock.getElapsedTime().asSeconds();
        float scale = 1.0f + 0.5f * std::sin(elapsedTime * 2 * 3.14159f); //use pi here

        pulseCircle.setRadius(initialRadius * scale);
        pulseCircle.setFillColor(sf::Color(255, 255, 255, static_cast<sf::Uint8>(255 * (1 - elapsedTime / 3.0f))));

        pulseCircle.setPosition((vm.width - pulseCircle.getGlobalBounds().width) / 2, (vm.height - pulseCircle.getGlobalBounds().height) / 2);
        
        updateSFMLText("Listening...");
        std::this_thread::sleep_for(std::chrono::milliseconds(16));
    }

    pulseCircle.setRadius(50);
    pulseCircle.setFillColor(sf::Color::Blue);
}

// Main function
int main(int argc, char **argv)
{
    if (!font.loadFromFile("fonts/KOMIKAP_.ttf"))
    {
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

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed || 
               (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape))
            {
                window.close();
            }
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::L)
            {
                bottomText.setString("");
                updateSFMLText("Listening...");
                std::cout << "Listening..." << std::endl;

                // Start the pulse effect in a separate thread
                std::thread pulseThread(pulseCircleEffect);
                pulseThread.detach(); // Detach the thread to run independently

                int predict = Listener::start_main_listen();
                functionality.executeCommand(predict);

                bottomText.setString("Press 'l' to start listening again...");
                std::cout << displayText << std::endl;
            }
        }

        { // needs to be sequential
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
