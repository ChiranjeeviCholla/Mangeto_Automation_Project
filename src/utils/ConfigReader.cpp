#include "ConfigReader.h"
#include <fstream>
#include <iostream>
#include <sstream>

std::map<std::string, std::string> ConfigReader::properties;
bool ConfigReader::loaded = false;

void ConfigReader::loadProperties() {
    if (loaded) return;
    
    std::ifstream file("config/config.properties");
    if (!file.is_open()) {
        std::cerr << "Could not open config.properties file" << std::endl;
        return;
    }
    
    std::string line;
    while (std::getline(file, line)) {
        if (line.empty() || line[0] == '#') continue;
        
        size_t delimiterPos = line.find('=');
        if (delimiterPos != std::string::npos) {
            std::string key = line.substr(0, delimiterPos);
            std::string value = line.substr(delimiterPos + 1);
            properties[key] = value;
        }
    }
    
    file.close();
    loaded = true;
}

std::string ConfigReader::getProperty(const std::string& key) {
    if (!loaded) loadProperties();
    
    auto it = properties.find(key);
    return (it != properties.end()) ? it->second : "";
}

std::string ConfigReader::getBaseUrl() {
    return getProperty("base.url");
}

std::string ConfigReader::getBrowser() {
    return getProperty("browser");
}

int ConfigReader::getTimeout() {
    std::string timeoutStr = getProperty("timeout");
    return timeoutStr.empty() ? 10 : std::stoi(timeoutStr);
}