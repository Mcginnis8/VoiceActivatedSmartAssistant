#include "functionality.h"
#include <iostream>
#include <thread>
#include <chrono>
#include <fstream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <iomanip>
#include <sstream>
#include "config.h"
#include <string>
#include <curl/curl.h>
#include "main.h"

static size_t writeCallback(void* contents, size_t size, size_t nmemb, std::string* userp) {
    userp->append((char*)contents, size * nmemb);
    return size * nmemb;
}


Functionality::Functionality() {
    // Initialize random seed
    std::srand(std::time(nullptr));
}

void Functionality::tellJoke() {
    std::ifstream file("jokes.txt");
    if (!file.is_open()) {
        std::cout << "Error opening jokes.txt" << std::endl;
        updateSFMLText("Error opening jokes.txt");
        return;
    }

    std::vector<std::string> jokes;
    std::string line;
    while (std::getline(file, line)) {
        jokes.push_back(line);
    }
    file.close();

    if (jokes.empty()) {
        std::cout << "No jokes found." << std::endl;
        updateSFMLText("No jokes found.");
        return;
    }

    int index = std::rand() % jokes.size();
    std::cout << jokes[index] << std::endl;
}

void Functionality::setTenSecondTimer() {
    for (int i = 10; i > 0; i--) {
        std::cout << i << std::endl;
        updateSFMLText(std::to_string(i));
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
    std::cout << "Time's up!" << std::endl;
    updateSFMLText("Time's up!");
}

void Functionality::setSixtySecondTimer() {
    for (int i = 60; i > 0; i--) {
        std::cout << i << std::endl;
        updateSFMLText(std::to_string(i));
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
    std::cout << "Time's up!" << std::endl;
}

void Functionality::setOneMinuteTimer() {
    for (int i = 60; i > 0; i--) {
        std::cout << i << std::endl;
        updateSFMLText(std::to_string(i));
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
    updateSFMLText("Time's up!");
    std::cout << "Time's up!" << std::endl;
}

void Functionality::sayHello() {
    std::cout << "Hello!" << std::endl;
    updateSFMLText("Hello!");
}

void Functionality::openGoogle() {
    system("open -a \"Google Chrome\" https://www.google.com/");
    updateSFMLText("Opened Google");
}

void Functionality::snake() { //Maybe remove this later
    system("open -a \"Google Chrome\" https://snakegame.org");
}

void Functionality::canvas() {
    system("open -a \"Google Chrome\" https://gatech.instructure.com/courses/");
    updateSFMLText("Opened Canvas");
}

void Functionality::openYoutube() {
    system("open -a \"Google Chrome\" https://www.youtube.com/");
    updateSFMLText("Opened Youtube");
}

void Functionality::weatherAtlanta() {
    std::string command = "curl -s \"https://api.weatherapi.com/v1/current.json?q=30308&key=" + WEATHER_API_KEY + "\"";
    std::string response = "";
    char buffer[128];
    FILE* pipe = popen(command.c_str(), "r");
    if (!pipe) {
        std::cout << "Failed to get weather data." << std::endl;
        updateSFMLText("Failed to get weather data.");
        return;
    }
    while (fgets(buffer, sizeof(buffer), pipe) != nullptr) {
        response += buffer;
    }
    pclose(pipe);

    // Manual JSON parsing
    std::string location, region, condition;
    double tempC, windKPH;
    int humidity;

    // Helper lambda to extract value by key
    auto extract = [&](const std::string& key) -> std::string {
        size_t pos = response.find("\"" + key + "\":");
        if (pos == std::string::npos) return "";
        pos += key.length() + 3;
        size_t end;
        if (response[pos] == '\"') {
            pos++;
            end = response.find("\"", pos);
            return response.substr(pos, end - pos);
        } else {
            end = response.find(",", pos);
            return response.substr(pos, end - pos);
        }
    };

    location = extract("name");
    region = extract("region");
    condition = extract("text");
    tempC = std::stod(extract("temp_c"));
    windKPH = std::stod(extract("wind_kph"));
    humidity = std::stoi(extract("humidity"));

    // Convert temperature to Fahrenheit and wind speed to MPH
    double tempF = (tempC * 9/5) + 32;
    double windMPH = windKPH * 0.621371;

    // Create informative paragraph with 2 decimal places
    std::ostringstream oss;
    oss << std::fixed << std::setprecision(2);
    oss << "Weather in " << location << ", " << region << ": " << condition << ". "
        << "Temperature is " << tempC << "°C (" << tempF << "°F) \nwith a wind speed of " 
        << windKPH << " kph (" << windMPH << " mph) \nand humidity of " << humidity << "%.";

    std::string output = oss.str();
    std::cout << output << std::endl;
    updateSFMLText(output);
}

void Functionality::viewStockMarket() {
    sf::VideoMode stock_vm(1036, 569);
    sf::RenderWindow stock_window(stock_vm, "Stock Market", sf::Style::Default);
    sf::Font stock_font;
    sf::Text stock_text_SandP;
    sf::Text stock_text_DowJones;
    sf::Text stock_text_Nasdaq;

    sf::Clock stock_clock;

    if (!stock_font.loadFromFile("fonts/KOMIKAP_.ttf")) {
        std::cerr << "Failed to load font." << std::endl;
        return;
    }

    stock_text_SandP.setFont(stock_font);
    stock_text_SandP.setCharacterSize(20);
    stock_text_SandP.setFillColor(sf::Color::White);
    stock_text_SandP.setPosition(20, 20);

    stock_text_DowJones.setFont(stock_font);
    stock_text_DowJones.setCharacterSize(20);
    stock_text_DowJones.setFillColor(sf::Color::White);
    stock_text_DowJones.setPosition(20, 50);

    stock_text_Nasdaq.setFont(stock_font);
    stock_text_Nasdaq.setCharacterSize(20);
    stock_text_Nasdaq.setFillColor(sf::Color::White);
    stock_text_Nasdaq.setPosition(20, 80);

    bool firstRun = true;

    while (stock_window.isOpen()) {
        sf::Event event;
        while (stock_window.pollEvent(event)) {
            if (event.type == sf::Event::Closed || 
               (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)) {
                stock_window.close();
            }
        }
        // only update every 60 seconds
        if (!firstRun && stock_clock.getElapsedTime().asSeconds() < 60) {
            continue;
        } else {
            firstRun = false;
        }
        stock_clock.restart();
        // call api to find S&P 500, Dow Jones, and Nasdaq
        std::string command_SandP = "curl -s 'https://www.alphavantage.co/query?function=GLOBAL_QUOTE&symbol=SPY&apikey=" + STOCK_MARKET_API_KEY + "'";
        std::string response_SandP = "";
        char buffer_SandP[128];
        FILE* pipe_SandP = popen(command_SandP.c_str(), "r");
        if (!pipe_SandP) {
            std::cout << "Failed to get stock data." << std::endl;
            return;
        }
        while (fgets(buffer_SandP, sizeof(buffer_SandP), pipe_SandP) != nullptr) {
            response_SandP += buffer_SandP;
        }
        pclose(pipe_SandP);

        std::string command_DowJones = "curl -s 'https://www.alphavantage.co/query?function=GLOBAL_QUOTE&symbol=DIA&apikey=" + STOCK_MARKET_API_KEY + "'";
        std::string response_DowJones = "";
        char buffer_DowJones[128];
        FILE* pipe_DowJones = popen(command_DowJones.c_str(), "r");
        if (!pipe_DowJones) {
            std::cout << "Failed to get stock data." << std::endl;
            return;
        }
        while (fgets(buffer_DowJones, sizeof(buffer_DowJones), pipe_DowJones) != nullptr) {
            response_DowJones += buffer_DowJones;
        }
        pclose(pipe_DowJones);

        std::string command_Nasdaq = "curl -s 'https://www.alphavantage.co/query?function=GLOBAL_QUOTE&symbol=QQQ&apikey=" + STOCK_MARKET_API_KEY + "'";
        std::string response_Nasdaq = "";
        char buffer_Nasdaq[128];
        FILE* pipe_Nasdaq = popen(command_Nasdaq.c_str(), "r");
        if (!pipe_Nasdaq) {
            std::cout << "Failed to get stock data." << std::endl;
            return;
        }
        while (fgets(buffer_Nasdaq, sizeof(buffer_Nasdaq), pipe_Nasdaq) != nullptr) {
            response_Nasdaq += buffer_Nasdaq;
        }
        pclose(pipe_Nasdaq);

        // Helper lambda to extract value by key
        auto extract = [&](const std::string& key, const std::string& response) -> std::string {
            size_t pos = response.find("\"" + key + "\":");
            if (pos == std::string::npos) return "";
            pos += key.length() + 3;
            size_t end;
            if (response[pos] == '\"') {
                pos++;
                end = response.find("\"", pos);
                return response.substr(pos, end - pos);
            } else {
                end = response.find(",", pos);
                return response.substr(pos, end - pos);
            }
        };

        std::string price_SandP = extract("05. price", response_SandP);
        std::string price_DowJones = extract("05. price", response_DowJones);
        std::string price_Nasdaq = extract("05. price", response_Nasdaq);

        stock_text_SandP.setString("S&P 500: " + price_SandP);
        stock_text_DowJones.setString("Dow Jones ETF (DIA): " + price_DowJones);
        stock_text_Nasdaq.setString("Nasdaq: " + price_Nasdaq);

        stock_window.clear();
        stock_window.draw(stock_text_SandP);
        stock_window.draw(stock_text_DowJones);
        stock_window.draw(stock_text_Nasdaq);
        stock_window.display();

        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
}

void Functionality::executeCommand(int command) {
    switch (command) {
        case 0:
            setTenSecondTimer();
            break;
        case 1:
            setSixtySecondTimer();
            break;
        case 2:
            setOneMinuteTimer();
            break;
        case 3:
            sayHello();
            break;
        case 4:
            openGoogle();
            break;
        case 5:
            snake();
            break;
        case 6:
            canvas();
            break;
        case 7:
            openYoutube();
            break;
        case 8:
            tellJoke();
            break;
        case 9:
            weatherAtlanta();
            break;
        case 10:
            viewStockMarket();
            break;
        default:
            std::cout << "Unknown command" << std::endl;
            updateSFMLText("Unknown command");
            break;
    }
}