# VoiceActivatedSmartAssistant
Gatech ECE 4122/6122 Project
by Aki Snapp, Cole McGinnis, and John Donahoe

# OS:
macOS Sequoia 15.1

# External libraries and APIs used:
Whisper.cpp: https://github.com/ggerganov/whisper.cpp
SFML: https://github.com/SFML/SFML
Open Weather API: https://home.openweathermap.org/users/sign_in
Alpha Vantage Stock API: https://www.alphavantage.co/

# To rebuild the code:
You will need to have ffmpeg which can be installed using `brew install ffmpeg`
You will also need to make sure you have all the requirements to run SFML and Whisper.cpp.
After this you will need to add your own keys to the config.h file where indicated. We have left ours out for security reasons.
Once these steps are done you can make a build directory, run cmake like normal and then run make in order to build the code.
Once this is complete simply run the SmartAssistant executable in the build folder in order to run the code.

# API Keys
Additionally Add the following Config File in the top level directory
config.h:
```cpp
#ifndef CONFIG_H
#define CONFIG_H

#include <string>

std::string WEATHER_API_KEY = "<YOUR KEY HERE>";

std::string STOCK_MARKET_API_KEY = "<YOUR KEY HERE>";

#endif
```
