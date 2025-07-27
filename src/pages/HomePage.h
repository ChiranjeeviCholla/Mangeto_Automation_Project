#ifndef HOMEPAGE_H
#define HOMEPAGE_H

#include "BasePage.h"

class HomePage : public BasePage {
private:
    selenium::By createAccountLink = selenium::By::linkText("Create an Account");
    selenium::By signInLink = selenium::By::linkText("Sign In");
    selenium::By welcomeMessage = selenium::By::cssSelector(".logged-in");
    selenium::By customerMenuToggle = selenium::By::cssSelector(".customer-name");

public:
    void navigateToCreateAccount();
    void navigateToSignIn();
    bool isUserLoggedIn();
    void navigateToHomepage();
};

#endif