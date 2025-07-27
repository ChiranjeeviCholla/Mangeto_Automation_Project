#ifndef DRIVERMANAGER_H
#define DRIVERMANAGER_H

#include <selenium/webdriver.h>
#include <selenium/chrome_driver.h>
#include <selenium/firefox_driver.h>
#include <memory>
#include <string>

class DriverManager {
private:
    static std::unique_ptr<selenium::WebDriver> driver;
    static std::string currentBrowser;

public:
    static void initializeDriver(const std::string& browserName);
    static selenium::WebDriver* getDriver();
    static void quitDriver();
    static void maximizeWindow();
    static void deleteAllCookies();
};

#endif