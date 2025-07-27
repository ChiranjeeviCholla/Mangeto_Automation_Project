#include "HomePage.h"
#include "ConfigReader.h"
#include <iostream>

void HomePage::navigateToCreateAccount() {
    try {
        clickElement(createAccountLink);
        waitForPageLoad();
        std::cout << "Navigated to Create Account page" << std::endl;
    }
    catch (const std::exception& e) {
        std::cerr << "Error navigating to Create Account: " << e.what() << std::endl;
        throw;
    }
}

void HomePage::navigateToSignIn() {
    try {
        clickElement(signInLink);
        waitForPageLoad();
        std::cout << "Navigated to Sign In page" << std::endl;
    }
    catch (const std::exception& e) {
        std::cerr << "Error navigating to Sign In: " << e.what() << std::endl;
        throw;
    }
}

bool HomePage::isUserLoggedIn() {
    return isElementDisplayed(customerMenuToggle) || isElementDisplayed(welcomeMessage);
}

void HomePage::navigateToHomepage() {
    driver->get(ConfigReader::getBaseUrl());
    waitForPageLoad();
}
