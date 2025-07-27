#include "CreateAccountPage.h"
#include <iostream>

void CreateAccountPage::enterFirstName(const std::string& firstName) {
    enterText(firstNameField, firstName);
}

void CreateAccountPage::enterLastName(const std::string& lastName) {
    enterText(lastNameField, lastName);
}

void CreateAccountPage::enterEmail(const std::string& email) {
    enterText(emailField, email);
}

void CreateAccountPage::enterPassword(const std::string& password) {
    enterText(passwordField, password);
}

void CreateAccountPage::enterConfirmPassword(const std::string& confirmPassword) {
    enterText(confirmPasswordField, confirmPassword);
}

void CreateAccountPage::clickCreateAccount() {
    try {
        scrollToElement(createAccountButton);
        clickElement(createAccountButton);
        waitForPageLoad();
        std::cout << "Clicked Create Account button" << std::endl;
    }
    catch (const std::exception& e) {
        std::cerr << "Error clicking Create Account button: " << e.what() << std::endl;
        throw;
    }
}

void CreateAccountPage::fillRegistrationForm(const std::string& firstName, const std::string& lastName,
                                           const std::string& email, const std::string& password,
                                           const std::string& confirmPassword) {
    try {
        enterFirstName(firstName);
        enterLastName(lastName);
        enterEmail(email);
        enterPassword(password);
        enterConfirmPassword(confirmPassword);
        std::cout << "Registration form filled successfully" << std::endl;
    }
    catch (const std::exception& e) {
        std::cerr << "Error filling registration form: " << e.what() << std::endl;
        throw;
    }
}

bool CreateAccountPage::isErrorMessageDisplayed() {
    return isElementDisplayed(errorMessage);
}

bool CreateAccountPage::isEmailErrorDisplayed() {
    return isElementDisplayed(emailErrorMessage);
}

bool CreateAccountPage::isPasswordErrorDisplayed() {
    return isElementDisplayed(passwordErrorMessage);
}

bool CreateAccountPage::isSuccessMessageDisplayed() {
    return isElementDisplayed(successMessage);
}

std::string CreateAccountPage::getErrorMessage() {
    if (isErrorMessageDisplayed()) {
        return getText(errorMessage);
    }
    return "";
}