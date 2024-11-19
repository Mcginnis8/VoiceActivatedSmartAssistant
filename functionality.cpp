#include "functionality.h"
#include <iostream>
#include <thread>
#include <chrono>

Functionality::Functionality() {}

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
        default:
            std::cout << "Unknown command" << std::endl;
            break;
    }
}