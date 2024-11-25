#include "listener.h"
#include <vector>
#include <algorithm>
#include <chrono>
#include <thread>
#include <fstream>
#include <stdlib.h>
#include <iostream>

// Function to calculate the Levenshtein distance between two strings
int Listener::levenshteinDistance(const std::string &s1, const std::string &s2) {
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

int Listener::start_main_listen() {
    system("sox -d -r 16000 -c 1 -b 16 test.wav trim 0 3");
    std::this_thread::sleep_for(std::chrono::seconds(3));
    system("../whisper.cpp/main -m ../whisper.cpp/models/ggml-tiny.en.bin -f test.wav -otxt");
    std::vector<std::string> targets = {"Set a 10 second timer", "Set a 60 second timer", "Set a 1 minute timer",
            "Say Hello", "Open Google", "Play Snake", "Open Canvas", "Open Youtube", "Tell me a joke"};
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

    return closestTargetIndex;
    
}