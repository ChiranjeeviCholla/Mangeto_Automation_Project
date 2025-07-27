#ifndef CONFIGREADER_H
#define CONFIGREADER_H

#include <string>
#include <map>

class ConfigReader {
private:
    static std::map<std::string, std::string> properties;
    static bool loaded;
    static void loadProperties();

public:
    static std::string getProperty(const std::string& key);
    static std::string getBaseUrl();
    static std::string getBrowser();
    static int getTimeout();
};

#endif