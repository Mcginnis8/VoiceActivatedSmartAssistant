#include <stdlib.h>
#include <vector>
#include <iostream>
#include <algorithm>
#include <thread>
#include <chrono>
#include <fstream>
#include <string>
#include "listener.h"


// Function to have a 10 second countdown in the console:
void setTenSecondTimer() {
    for (int i = 10; i > 0; i--) {
        std::cout << i << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
    std::cout << "Time's up!" << std::endl;
}

// Function to say Hello to the user in the console:
void sayHello() {
    std::cout << "Hello!" << std::endl;
}

int main(int argc, char **argv) {
    std::cout << "Press 'l' to start listening..." << std::endl;

    while (true) {
        char ch = std::cin.get();
        if (ch == 'l' || ch == 'L') {
            std::cout << "Listening..." << std::endl;
            Listener::start_main_listen();
            std::cout << "Press 'l' to start listening again..." << std::endl;
        }
    }

    return 0;
}



// Setup: 
// build commands:
// cmake ../
// cmake --build .