#include "functionality.h"
#include <iostream>
#include <thread>
#include <chrono>
#include <fstream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include "config.h"
#include <string>
#include <curl/curl.h>

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
        return;
    }

    int index = std::rand() % jokes.size();
    std::cout << jokes[index] << std::endl;
}

void Functionality::setTenSecondTimer() {
    for (int i = 10; i > 0; i--) {
        std::cout << i << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
    std::cout << "Time's up!" << std::endl;
}

void Functionality::setSixtySecondTimer() {
    for (int i = 60; i > 0; i--) {
        std::cout << i << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
    std::cout << "Time's up!" << std::endl;
}

void Functionality::setOneMinuteTimer() {
    for (int i = 60; i > 0; i--) {
        std::cout << i << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
    std::cout << "Time's up!" << std::endl;
}

void Functionality::sayHello() {
    std::cout << "Hello!" << std::endl;
}

void Functionality::openGoogle() {
    system("open -a \"Google Chrome\" https://www.google.com/");
}

void Functionality::snake() { //Maybe remove this later
    system("open -a \"Google Chrome\" https://snakegame.org");
}

void Functionality::canvas() {
    system("open -a \"Google Chrome\" https://gatech.instructure.com/courses/");
}

void Functionality::openYoutube() {
    system("open -a \"Google Chrome\" https://www.youtube.com/");
}

void Functionality::weatherAtlanta() {
    std::string command = "curl -s \"https://api.weatherapi.com/v1/current.json?q=30308&key=" + WEATHER_API_KEY + "\"";
    std::string response = "";
    char buffer[128];
    FILE* pipe = popen(command.c_str(), "r");
    if (!pipe) {
        std::cout << "Failed to get weather data." << std::endl;
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

    // Create informative paragraph
    std::cout << "Weather in " << location << ", " << region << ": " << condition << ". "
              << "Temperature is " << tempC << "°C (" << tempF << "°F) with a wind speed of " 
              << windKPH << " kph (" << windMPH << " mph) and humidity of " << humidity << "%." 
              << std::endl;
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
        default:
            std::cout << "Unknown command" << std::endl;
            break;
    }
}