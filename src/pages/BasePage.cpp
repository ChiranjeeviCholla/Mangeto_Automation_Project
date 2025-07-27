#include "BasePage.h"
#include "DriverManager.h"
#include "ConfigReader.h"
#include <thread>
#include <iostream>

BasePage::BasePage() {
    driver = DriverManager::getDriver();
    timeout = ConfigReader::getTimeout();
}

void BasePage::waitForElementToBeClickable(const selenium::By& locator) {
    auto endTime = std::chrono::steady_clock::now() + std::chrono::seconds(timeout);
    
    while (std::chrono::steady_clock::now() < endTime) {
        try {
            auto element = driver->findElement(locator);
            if (element.isDisplayed() && element.isEnabled()) {
                return;
            }
        }
        catch (const std::exception&) {
            // Element not found, continue waiting
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }
    
    throw std::runtime_error("Element not clickable within timeout");
}

void BasePage::waitForElementToBeVisible(const selenium::By& locator) {
    auto endTime = std::chrono::steady_clock::now() + std::chrono::seconds(timeout);
    
    while (std::chrono::steady_clock::now() < endTime) {
        try {
            auto element = driver->findElement(locator);
            if (element.isDisplayed()) {
                return;
            }
        }
        catch (const std::exception&) {
            // Element not found, continue waiting
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }
    
    throw std::runtime_error("Element not visible within timeout");
}

bool BasePage::waitForElementToBePresent(const selenium::By& locator, int timeoutSeconds) {
    auto endTime = std::chrono::steady_clock::now() + std::chrono::seconds(timeoutSeconds);
    
    while (std::chrono::steady_clock::now() < endTime) {
        try {
            driver->findElement(locator);
            return true;
        }
        catch (const std::exception&) {
            std::this_thread::sleep_for(std::chrono::milliseconds(500));
        }
    }
    return false;
}

void BasePage::clickElement(const selenium::By& locator) {
    waitForElementToBeClickable(locator);
    auto element = driver->findElement(locator);
    element.click();
}

void BasePage::enterText(const selenium::By& locator, const std::string& text) {
    waitForElementToBeVisible(locator);
    auto element = driver->findElement(locator);
    element.clear();
    element.sendKeys(text);
}

std::string BasePage::getText(const selenium::By& locator) {
    waitForElementToBeVisible(locator);
    auto element = driver->findElement(locator);
    return element.getText();
}

bool BasePage::isElementDisplayed(const selenium::By& locator) {
    try {
        auto element = driver->findElement(locator);
        return element.isDisplayed();
    }
    catch (const std::exception&) {
        return false;
    }
}

void BasePage::scrollToElement(const selenium::By& locator) {
    auto element = driver->findElement(locator);
    driver->executeScript("arguments[0].scrollIntoView(true);", element);
}

void BasePage::waitForPageLoad() {
    std::this_thread::sleep_for(std::chrono::seconds(2));
}

std::string BasePage::getCurrentUrl() {
    return driver->getCurrentUrl();
}