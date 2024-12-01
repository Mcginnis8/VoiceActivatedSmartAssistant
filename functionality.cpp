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
    CURL *curl;
    CURLcode res;
    std::string response;
    if ((curl = curl_easy_init()) != nullptr) {
        curl_easy_setopt(curl, CURLOPT_URL, "https://api.tomorrow.io/v4/weather/forecast?location=42.3478,-71.0466&apikey=" + WEATHER_API_KEY);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writeCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);
        res = curl_easy_perform(curl);
        curl_easy_cleanup(curl);
    }
    std::cout << response << std::endl;
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
        default:
            std::cout << "Unknown command" << std::endl;
            break;
    }
}