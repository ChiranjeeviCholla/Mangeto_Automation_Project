#ifndef MYACCOUNTPAGE_H
#define MYACCOUNTPAGE_H

#include "BasePage.h"

class MyAccountPage : public BasePage {
private:
    selenium::By pageTitle = selenium::By::cssSelector(".page-title");
    selenium::By welcomeMessage = selenium::By::cssSelector(".box-content p");
    selenium::By contactInformation = selenium::By::cssSelector(".box-information .box-content");
    selenium::By myAccountDashboard = selenium::By::cssSelector(".account-dashboard");

public:
    bool isMyAccountPageDisplayed();
    std::string getWelcomeMessage();
    bool isContactInformationDisplayed();
    bool isDashboardDisplayed();
    std::string getPageTitle();
};

#endif