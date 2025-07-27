#ifndef SIGNINPAGE_H
#define SIGNINPAGE_H

#include "BasePage.h"

class SignInPage : public BasePage {
private:
    selenium::By emailField = selenium::By::id("email");
    selenium::By passwordField = selenium::By::id("pass");
    selenium::By signInButton = selenium::By::cssSelector("button[id='send2']");
    selenium::By errorMessage = selenium::By::cssSelector(".message-error");
    selenium::By emailErrorMessage = selenium::By::id("email-error");
    selenium::By passwordErrorMessage = selenium::By::id("pass-error");

public:
    void enterEmail(const std::string& email);
    void enterPassword(const std::string& password);
    void clickSignIn();
    void performSignIn(const std::string& email, const std::string& password);
    bool isErrorMessageDisplayed();
    bool isEmailErrorDisplayed();
    bool isPasswordErrorDisplayed();
    std::string getErrorMessage();
};

#endif