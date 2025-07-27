#ifndef BASEPAGE_H
#define BASEPAGE_H

#include <selenium/webdriver.h>
#include <selenium/by.h>
#include <selenium/web_element.h>
#include <string>
#include <chrono>

class BasePage {
protected:
    selenium::WebDriver* driver;
    int timeout;
    
    void waitForElementToBeClickable(const selenium::By& locator);
    void waitForElementToBeVisible(const selenium::By& locator);
    bool waitForElementToBePresent(const selenium::By& locator, int timeoutSeconds = 10);

public:
    BasePage();
    virtual ~BasePage() = default;
    
    void clickElement(const selenium::By& locator);
    void enterText(const selenium::By& locator, const std::string& text);
    std::string getText(const selenium::By& locator);
    bool isElementDisplayed(const selenium::By& locator);
    void scrollToElement(const selenium::By& locator);
    void waitForPageLoad();
    std::string getCurrentUrl();
};

#endif  