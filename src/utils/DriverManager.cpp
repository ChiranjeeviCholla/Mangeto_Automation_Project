#include "DriverManager.h"
#include <iostream>
#include <stdexcept>

std::unique_ptr<selenium::WebDriver> DriverManager::driver = nullptr;
std::string DriverManager::currentBrowser = "";

void DriverManager::initializeDriver(const std::string& browserName) {
    try {
        if (browserName == "chrome") {
            selenium::ChromeOptions options;
            options.addArgument("--disable-notifications");
            options.addArgument("--disable-popup-blocking");
            options.addArgument("--disable-web-security");
            options.addArgument("--allow-running-insecure-content");
            
            driver = std::make_unique<selenium::ChromeDriver>(options);
            currentBrowser = "chrome";
        }
        else if (browserName == "firefox") {
            selenium::FirefoxOptions options;
            driver = std::make_unique<selenium::FirefoxDriver>(options);
            currentBrowser = "firefox";
        }
        else {
            throw std::invalid_argument("Unsupported browser: " + browserName);
        }
        
        maximizeWindow();
        deleteAllCookies();
        
        std::cout << "Driver initialized successfully for: " << browserName << std::endl;
    }
    catch (const std::exception& e) {
        std::cerr << "Error initializing driver: " << e.what() << std::endl;
        throw;
    }
}

selenium::WebDriver* DriverManager::getDriver() {
    if (!driver) {
        throw std::runtime_error("Driver not initialized. Call initializeDriver() first.");
    }
    return driver.get();
}

void DriverManager::quitDriver() {
    if (driver) {
        try {
            driver->quit();
            driver.reset();
            std::cout << "Driver quit successfully" << std::endl;
        }
        catch (const std::exception& e) {
            std::cerr << "Error quitting driver: " << e.what() << std::endl;
        }
    }
}

void DriverManager::maximizeWindow() {
    if (driver) {
        driver->manage().window().maximize();
    }
}

void DriverManager::deleteAllCookies() {
    if (driver) {
        driver->manage().deleteAllCookies();
    }
}