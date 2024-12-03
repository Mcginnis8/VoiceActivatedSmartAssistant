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
#include <stack>

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

void Functionality::playBeethoven() {
    std::string command = "ffplay -autoexit -nodisp -t 10 beethoven.mp3";
    system(command.c_str());
    updateSFMLText("Playback finished.");
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
    sf::Text stock_label_SandP;
    sf::Text stock_label_DowJones;
    sf::Text stock_label_Nasdaq;

    sf::Clock stock_clock;

    if (!stock_font.loadFromFile("fonts/KOMIKAP_.ttf")) {
        std::cerr << "Failed to load font." << std::endl;
        return;
    }

    // Set up labels
    stock_label_SandP.setFont(stock_font);
    stock_label_SandP.setCharacterSize(36);
    stock_label_SandP.setFillColor(sf::Color::Yellow);
    stock_label_SandP.setPosition(20, 20);
    stock_label_SandP.setString("S&P 500:");

    stock_label_DowJones.setFont(stock_font);
    stock_label_DowJones.setCharacterSize(36);
    stock_label_DowJones.setFillColor(sf::Color::Yellow);
    stock_label_DowJones.setPosition(350, 20);
    stock_label_DowJones.setString("DJI/DIA");

    stock_label_Nasdaq.setFont(stock_font);
    stock_label_Nasdaq.setCharacterSize(36);
    stock_label_Nasdaq.setFillColor(sf::Color::Yellow);
    stock_label_Nasdaq.setPosition(700, 20);
    stock_label_Nasdaq.setString("Nasdaq:");

    // Set up text
    stock_text_SandP.setFont(stock_font);
    stock_text_SandP.setCharacterSize(36);
    stock_text_SandP.setFillColor(sf::Color::White);
    stock_text_SandP.setPosition(20, 60);

    stock_text_DowJones.setFont(stock_font);
    stock_text_DowJones.setCharacterSize(36);
    stock_text_DowJones.setFillColor(sf::Color::White);
    stock_text_DowJones.setPosition(350, 60);

    stock_text_Nasdaq.setFont(stock_font);
    stock_text_Nasdaq.setCharacterSize(36);
    stock_text_Nasdaq.setFillColor(sf::Color::White);
    stock_text_Nasdaq.setPosition(700, 60);

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

        stock_text_SandP.setString(price_SandP);
        stock_text_DowJones.setString(price_DowJones);
        stock_text_Nasdaq.setString(price_Nasdaq);

        stock_window.clear();
        stock_window.draw(stock_label_SandP);
        stock_window.draw(stock_text_SandP);
        stock_window.draw(stock_label_DowJones);
        stock_window.draw(stock_text_DowJones);
        stock_window.draw(stock_label_Nasdaq);
        stock_window.draw(stock_text_Nasdaq);
        stock_window.display();

        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
}

void Functionality::visualizeBubbleSort() {
    sf::VideoMode vm(1036, 569);
    sf::RenderWindow window(vm, "Bubble Sort", sf::Style::Default);

    const int arraySize = 100;
    std::vector<int> array(arraySize);

    // Initialize the array with random values
    for (int i = 0; i < arraySize; ++i) {
        array[i] = std::rand() % window.getSize().y;
    }

    sf::Font font;
    if (!font.loadFromFile("fonts/KOMIKAP_.ttf")) {
        std::cerr << "Failed to load font." << std::endl;
        return;
    }

    sf::Text title("Bubble Sort", font, 30);
    title.setFillColor(sf::Color::White);
    title.setPosition(20, 20);

    bool sorted = false;
    sf::Clock clock;
    sf::Clock displayClock;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed ||
               (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)) {
                window.close();
            }
        }

        if (!sorted) {
            sorted = true;
            for (int i = 0; i < arraySize - 1; ++i) {
                if (array[i] > array[i + 1]) {
                    std::swap(array[i], array[i + 1]);
                    sorted = false;
                }

                // Render the array
                window.clear();
                window.draw(title);
                for (int j = 0; j < arraySize; ++j) {
                    sf::RectangleShape bar;
                    bar.setSize(sf::Vector2f(window.getSize().x / arraySize, array[j]));
                    bar.setPosition(j * (window.getSize().x / arraySize), window.getSize().y - array[j]);
                    bar.setFillColor(sf::Color::White);
                    window.draw(bar);
                }
                window.display();

                // Delay to visualize the sorting process
                sf::sleep(sf::milliseconds(10));

                // Handle window events during sorting
                if (!window.isOpen()) {
                    break;
                }
            }
            clock.restart(); // Restart the timer after sorting is done
        } else {
            // Keep the window open for 10 more seconds after sorting
            if (clock.getElapsedTime().asSeconds() >= 10) {
                window.close();
            } else {
                window.clear();
                window.draw(title);
                for (int j = 0; j < arraySize; ++j) {
                    sf::RectangleShape bar;
                    bar.setSize(sf::Vector2f(window.getSize().x / arraySize, array[j]));
                    bar.setPosition(j * (window.getSize().x / arraySize), window.getSize().y - array[j]);
                    bar.setFillColor(sf::Color::Green);
                    window.draw(bar);
                }
                window.display();
            }
        }
    }
}

void Functionality::visualizeInsertionSort() {
    sf::VideoMode vm(1036, 569);
    sf::RenderWindow window(vm, "Insertion Sort", sf::Style::Default);

    const int arraySize = 100;
    std::vector<int> array(arraySize);

    // Initialize the array with random values
    for (int i = 0; i < arraySize; ++i) {
        array[i] = std::rand() % window.getSize().y;
    }

    sf::Font font;
    if (!font.loadFromFile("fonts/KOMIKAP_.ttf")) {
        std::cerr << "Failed to load font." << std::endl;
        return;
    }

    sf::Text title("Insertion Sort", font, 30);
    title.setFillColor(sf::Color::White);
    title.setPosition(20, 20);

    bool sorted = false;
    sf::Clock clock;

    int i = 1;
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed ||
               (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)) {
                window.close();
            }
        }

        if (!sorted) {
            if (i < arraySize) {
                int key = array[i];
                int j = i - 1;

                while (j >= 0 && array[j] > key) {
                    array[j + 1] = array[j];
                    j--;

                    // Render the array
                    window.clear();
                    window.draw(title);
                    for (int k = 0; k < arraySize; ++k) {
                        sf::RectangleShape bar;
                        bar.setSize(sf::Vector2f(window.getSize().x / arraySize, array[k]));
                        bar.setPosition(k * (window.getSize().x / arraySize), window.getSize().y - array[k]);
                        if (k == j + 1) {
                            bar.setFillColor(sf::Color::Red);
                        } else {
                            bar.setFillColor(sf::Color::White);
                        }
                        window.draw(bar);
                    }
                    window.display();

                    sf::sleep(sf::milliseconds(5));

                    if (!window.isOpen()) {
                        break;
                    }
                }
                array[j + 1] = key;
                i++;
            } else {
                sorted = true;
                clock.restart();
            }
        } else {
            if (clock.getElapsedTime().asSeconds() >= 10) {
                window.close();
            } else {
                window.clear();
                window.draw(title);
                for (int k = 0; k < arraySize; ++k) {
                    sf::RectangleShape bar;
                    bar.setSize(sf::Vector2f(window.getSize().x / arraySize, array[k]));
                    bar.setPosition(k * (window.getSize().x / arraySize), window.getSize().y - array[k]);
                    bar.setFillColor(sf::Color::Green);
                    window.draw(bar);
                }
                window.display();
            }
        }
    }
}

void Functionality::visualizeSelectionSort() {
    sf::VideoMode vm(1036, 569);
    sf::RenderWindow window(vm, "Selection Sort", sf::Style::Default);

    const int arraySize = 100;
    std::vector<int> array(arraySize);

    // Initialize the array with random values
    for (int i = 0; i < arraySize; ++i) {
        array[i] = std::rand() % window.getSize().y;
    }

    sf::Font font;
    if (!font.loadFromFile("fonts/KOMIKAP_.ttf")) {
        std::cerr << "Failed to load font." << std::endl;
        return;
    }

    sf::Text title("Selection Sort", font, 30);
    title.setFillColor(sf::Color::White);
    title.setPosition(20, 20);

    bool sorted = false;
    sf::Clock clock;

    int i = 0;
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed ||
               (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)) {
                window.close();
            }
        }

        if (!sorted) {
            if (i < arraySize - 1) {
                int minIndex = i;
                for (int j = i + 1; j < arraySize; ++j) {
                    if (array[j] < array[minIndex]) {
                        minIndex = j;
                    }

                    // Render the array
                    window.clear();
                    window.draw(title);
                    for (int k = 0; k < arraySize; ++k) {
                        sf::RectangleShape bar;
                        bar.setSize(sf::Vector2f(window.getSize().x / arraySize, array[k]));
                        bar.setPosition(k * (window.getSize().x / arraySize), window.getSize().y - array[k]);
                        if (k == minIndex) {
                            bar.setFillColor(sf::Color::Red);
                        } else if (k == i) {
                            bar.setFillColor(sf::Color::Blue);
                        } else {
                            bar.setFillColor(sf::Color::White);
                        }
                        window.draw(bar);
                    }
                    window.display();

                    sf::sleep(sf::milliseconds(5));

                    if (!window.isOpen()) {
                        break;
                    }
                }
                std::swap(array[i], array[minIndex]);
                i++;
            } else {
                sorted = true;
                clock.restart();
            }
        } else {
            if (clock.getElapsedTime().asSeconds() >= 10) {
                window.close();
            } else {
                window.clear();
                window.draw(title);
                for (int k = 0; k < arraySize; ++k) {
                    sf::RectangleShape bar;
                    bar.setSize(sf::Vector2f(window.getSize().x / arraySize, array[k]));
                    bar.setPosition(k * (window.getSize().x / arraySize), window.getSize().y - array[k]);
                    bar.setFillColor(sf::Color::Green);
                    window.draw(bar);
                }
                window.display();
            }
        }
    }
}

void Functionality::visualizeQuickSort() {
    sf::VideoMode vm(1036, 569);
    sf::RenderWindow window(vm, "Quick Sort", sf::Style::Default);

    const int arraySize = 100;
    std::vector<int> array(arraySize);

    // Initialize the array with random values
    for (int i = 0; i < arraySize; ++i) {
        array[i] = std::rand() % window.getSize().y;
    }

    sf::Font font;
    if (!font.loadFromFile("fonts/KOMIKAP_.ttf")) {
        std::cerr << "Failed to load font." << std::endl;
        return;
    }

    sf::Text title("Quick Sort", font, 30);
    title.setFillColor(sf::Color::White);
    title.setPosition(20, 20);

    bool sorted = false;
    sf::Clock clock;

    std::stack<std::pair<int, int>> stack;
    stack.push({0, arraySize - 1});

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed ||
               (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)) {
                window.close();
            }
        }

        if (!sorted) {
            if (!stack.empty()) {
                int low = stack.top().first;
                int high = stack.top().second;
                stack.pop();

                if (low < high) {
                    int pivot = array[high];
                    int i = low - 1;

                    for (int j = low; j <= high - 1; ++j) {
                        if (array[j] < pivot) {
                            i++;
                            std::swap(array[i], array[j]);
                        }

                        // Render the array
                        window.clear();
                        window.draw(title);
                        for (int k = 0; k < arraySize; ++k) {
                            sf::RectangleShape bar;
                            bar.setSize(sf::Vector2f(window.getSize().x / arraySize, array[k]));
                            bar.setPosition(k * (window.getSize().x / arraySize), window.getSize().y - array[k]);
                            if (k == i || k == j) {
                                bar.setFillColor(sf::Color::Red);
                            } else if (k == high) {
                                bar.setFillColor(sf::Color::Blue);
                            } else {
                                bar.setFillColor(sf::Color::White);
                            }
                            window.draw(bar);
                        }
                        window.display();

                        sf::sleep(sf::milliseconds(5));

                        if (!window.isOpen()) {
                            break;
                        }
                    }
                    std::swap(array[i + 1], array[high]);
                    int pi = i + 1;

                    stack.push({low, pi - 1});
                    stack.push({pi + 1, high});
                }
            } else {
                sorted = true;
                clock.restart();
            }
        } else {
            if (clock.getElapsedTime().asSeconds() >= 10) {
                window.close();
            } else {
                window.clear();
                window.draw(title);
                for (int k = 0; k < arraySize; ++k) {
                    sf::RectangleShape bar;
                    bar.setSize(sf::Vector2f(window.getSize().x / arraySize, array[k]));
                    bar.setPosition(k * (window.getSize().x / arraySize), window.getSize().y - array[k]);
                    bar.setFillColor(sf::Color::Green);
                    window.draw(bar);
                }
                window.display();
            }
        }
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
        case 11:
            visualizeBubbleSort();
            break;
        case 12:
            visualizeInsertionSort();
            break;
        case 13:
            visualizeSelectionSort();
            break;
        case 14:
            visualizeQuickSort();
            break;
        case 15:
            playBeethoven();
            break;
        default:
            std::cout << "Unknown command" << std::endl;
            updateSFMLText("Unknown command");
            break;
    }
}