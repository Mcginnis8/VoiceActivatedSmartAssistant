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

void Functionality::sayHello() {
    std::cout << "Hello!" << std::endl;
}

void Functionality::openGoogle() {
     system("open -a \"Google Chrome\" https://www.google.com/");
}

void Functionality::openGoogle() {
     system("nsnake");
}


void Functionality::executeCommand(int command) {
    switch (command) {
        case 0:
            setTenSecondTimer();
            break;
        case 1:
            sayHello();
            break;
        case 2:
            openGoogle();
            break;
        case 3:
            openGoogle();
            break;
        default:
            std::cout << "Unknown command" << std::endl;
            break;
    }
}