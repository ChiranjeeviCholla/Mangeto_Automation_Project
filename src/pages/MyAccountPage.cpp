#include "MyAccountPage.h"
#include <iostream>

bool MyAccountPage::isMyAccountPageDisplayed() {
    try {
        if (waitForElementToBePresent(pageTitle, 5)) {
            std::string title = getText(pageTitle);
            return title.find("My Account") != std::string::npos;
        }
        return isDashboardDisplayed();
    }
    catch (const std::exception& e) {
        std::cerr << "Error checking My Account page: " << e.what() << std::endl;
        return false;
    }
}

std::string MyAccountPage::getWelcomeMessage() {
    if (isElementDisplayed(welcomeMessage)) {
        return getText(welcomeMessage);
    }
    return "";
}

bool MyAccountPage::isContactInformationDisplayed() {
    return isElementDisplayed(contactInformation);
}

bool MyAccountPage::isDashboardDisplayed() {
    return isElementDisplayed(myAccountDashboard);
}

std::string MyAccountPage::getPageTitle() {
    if (isElementDisplayed(pageTitle)) {
        return getText(pageTitle);
    }
    return "";
}
