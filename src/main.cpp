#include "DriverManager.h"
#include "ConfigReader.h"
#include "SignUpTests.h"
#include "SignInTests.h"
#include <iostream>
#include <exception>

void printHeader() {
    std::cout << "=========================================" << std::endl;
    std::cout << "  MAGENTO AUTOMATION TEST FRAMEWORK" << std::endl;
    std::cout << "=========================================" << std::endl;
}

void printFooter() {
    std::cout << "=========================================" << std::endl;
    std::cout << "  ALL TESTS COMPLETED" << std::endl;
    std::cout << "=========================================" << std::endl;
}

int main() {
    printHeader();
    
    try {
        // Initialize configuration
        std::string browser = ConfigReader::getBrowser();
        std::string baseUrl = ConfigReader::getBaseUrl();
        
        std::cout << "Browser: " << browser << std::endl;
        std::cout << "Base URL: " << baseUrl << std::endl;
        std::cout << "Timeout: " << ConfigReader::getTimeout() << " seconds" << std::endl;
        
        // Initialize WebDriver
        DriverManager::initializeDriver(browser);
        
        // Navigate to base URL
        DriverManager::getDriver()->get(baseUrl);
        
        // Run Sign Up Tests
        SignUpTests signUpTests;
        signUpTests.runAllSignUpTests();
        
        // Run Sign In Tests
        SignInTests signInTests;
        signInTests.runAllSignInTests();
        
    }
    catch (const std::exception& e) {
        std::cerr << "Fatal error occurred: " << e.what() << std::endl;
        return 1;
    }
    
    // Clean up
    try {
        DriverManager::quitDriver();
    }
    catch (const std::exception& e) {
        std::cerr << "Error during cleanup: " << e.what() << std::endl;
    }
    
    printFooter();
    return 0;
}