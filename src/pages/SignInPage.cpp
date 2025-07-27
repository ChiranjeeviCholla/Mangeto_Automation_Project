#include "SignInPage.h"
#include <iostream>

void SignInPage::enterEmail(const std::string& email) {
    enterText(emailField, email);
}

void SignInPage::enterPassword(const std::string& password) {
    enterText(passwordField, password);
}

void SignInPage::clickSignIn() {
    try {
        clickElement(signInButton);
        waitForPageLoad();
        std::cout << "Clicked Sign In button" << std::endl;
    }
    catch (const std::exception& e) {
        std::cerr << "Error clicking Sign In button: " << e.what() << std::endl;
        throw;
    }
}

void SignInPage::performSignIn(const std::string& email, const std::string& password) {
    try {
        enterEmail(email);
        enterPassword(password);
        clickSignIn();
        std::cout << "Sign in performed with email: " << email << std::endl;
    }
    catch (const std::exception& e) {
        std::cerr << "Error performing sign in: " << e.what() << std::endl;
        throw;
    }
}

bool SignInPage::isErrorMessageDisplayed() {
    return isElementDisplayed(errorMessage);
}

bool SignInPage::isEmailErrorDisplayed() {
    return isElementDisplayed(emailErrorMessage);
}

bool SignInPage::isPasswordErrorDisplayed() {
    return isElementDisplayed(passwordErrorMessage);
}

std::string SignInPage::getErrorMessage() {
    if (isErrorMessageDisplayed()) {
        return getText(errorMessage);
    }
    return "";
}