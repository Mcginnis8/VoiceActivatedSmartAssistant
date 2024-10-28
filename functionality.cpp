#include "functionality.h"
#include <iostream>
#include <thread>
#include <chrono>

void setTenSecondTimer() {
    for (int i = 10; i > 0; i--) {
        std::cout << i << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
    std::cout << "Time's up!" << std::endl;
}

void sayHello() {
    std::cout << "Hello!" << std::endl;
}

void executeCommand(int command) {
    switch (command) {
        case 1:
            sayHello();
            break;
        case 0:
            setTenSecondTimer();
            break;
        default:
            std::cout << "Unknown command" << std::endl;
            break;
    }
}
