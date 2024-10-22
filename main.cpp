#include <stdlib.h>
#include <vector>
#include <iostream>
#include <algorithm>
#include <thread>
#include <chrono>
#include <fstream>
#include <string>

// Function to calculate the Levenshtein distance between two strings
int levenshteinDistance(const std::string &s1, const std::string &s2) {
    int m = s1.size();
    int n = s2.size();
    std::vector<std::vector<int>> d(m + 1, std::vector<int>(n + 1));

    for (int i = 0; i <= m; i++) {
        for (int j = 0; j <= n; j++) {
            if (i == 0) {
                d[i][j] = j;
            } else if (j == 0) {
                d[i][j] = i;
            } else {
                int cost = (s1[i - 1] != s2[j - 1]) ? 1 : 0;
                d[i][j] = std::min({d[i - 1][j - 1] + cost, d[i][j - 1] + 1, d[i - 1][j] + 1});
            }
        }
    }

    return d[m][n];
}

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

void start_main_listen() {
    system("sudo arecord -D plughw:1,0 -f cd -r 16000 -d 3 test.wav &");
    std::this_thread::sleep_for(std::chrono::seconds(3));
    system("sudo ../whisper.cpp/main -m ../whisper.cpp/models/ggml-tiny.en.bin -f test.wav -otxt");
    std::vector<std::string> targets = {"Set a 10 second timer", "Say Hello"};
    std::vector<std::string> closestMatches(targets.size());
    std::vector<int> minDistances(targets.size(), 9999999);

    std::ifstream file("test.wav.txt");
    if (file.is_open()) {
        std::string line;
        while (getline(file, line)) {
            for (int i = 0; i < targets.size(); i++) {
                int distance = levenshteinDistance(targets[i], line);
                if (distance < minDistances[i]) {
                    minDistances[i] = distance;
                    closestMatches[i] = line;
                }
            }
        }
        file.close();
    } else {
        std::cout << "Unable to open file";
    }

    int closestTargetIndex = 0;
    for (int i = 1; i < targets.size(); i++) {
        if (minDistances[i] < minDistances[closestTargetIndex]) {
            closestTargetIndex = i;
        }
    }
    std::this_thread::sleep_for(std::chrono::milliseconds(100));

    if (closestTargetIndex == 0) {
        setTenSecondTimer();
    } else if (closestTargetIndex == 1) {
        sayHello();
    }
}

int main(int argc, char **argv) {
    std::cout << "Press 'l' to start listening..." << std::endl;

    while (true) {
        char ch = std::cin.get();
        if (ch == 'l' || ch == 'L') {
            std::cout << "Listening..." << std::endl;
            start_main_listen();
            std::cout << "Press 'l' to start listening again..." << std::endl;
        }
    }

    return 0;
}



// Setup: 
// build commands:
// cmake ../
// cmake --build .