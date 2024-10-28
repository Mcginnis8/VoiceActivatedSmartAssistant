#include <stdlib.h>
#include <vector>
#include <iostream>
#include <algorithm>
#include <thread>
#include <chrono>
#include <fstream>
#include <string>
#include "listener.h"
#include "functionality.h" // Include the header file

int main(int argc, char **argv) {
    std::cout << "Press 'l' to start listening..." << std::endl;

    while (true) {
        Functionality functionality;
        char ch = std::cin.get();
        if (ch == 'l' || ch == 'L') {
            std::cout << "Listening..." << std::endl;

            // from listener.cpp
            int predict = Listener::start_main_listen();
            
            // from functionality.cpp
            functionality.executeCommand(predict);
            
            std::cout << "Press 'l' to start listening again..." << std::endl;
        }
    }

    return 0;
}