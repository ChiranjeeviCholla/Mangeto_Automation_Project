#include "SignInTests.h"
#include "TestDataGenerator.h"
#include <iostream>
#include <thread>

bool SignInTests::createTestAccount() {
    try {
        registeredEmail = TestDataGenerator::generateUniqueEmail();
        registeredPassword = TestDataGenerator::generateTestPassword();
        
        homePage.navigateToHomepage();
        homePage.navigateToCreateAccount();
        
        createAccountPage.fillRegistrationForm("Test", "User", registeredEmail, registeredPassword, registeredPassword);
        createAccountPage.clickCreateAccount();
        
        std::this_thread::sleep_for(std::chrono::seconds(3));
        
        if (myAccountPage.isMyAccountPageDisplayed()) {
            std::cout << "Test account created successfully with email: " << registeredEmail << std::endl;
            return true;
        }
        return false;
    }
    catch (const std::exception& e) {
        std::cerr << "Error creating test account: " << e.what() << std::endl;
        return false;
    }
}

SignInTests::TestResult SignInTests::testSuccessfulUserSignIn() {
    TestResult result;
    result.testName = "Successful User Sign In";
    
    try {
        // Create a test account first
        if (!createTestAccount()) {
            result.passed = false;
            result.message = "Failed to create test account";
            return result;
        }
        
        // Navigate to sign in page
        homePage.navigateToHomepage();
        homePage.navigateToSignIn();
        
        // Perform sign in
        signInPage.performSignIn(registeredEmail, registeredPassword);
        
        // Verify successful sign in
        std::this_thread::sleep_for(std::chrono::seconds(3));
        
        if (myAccountPage.isMyAccountPageDisplayed() || homePage.isUserLoggedIn()) {
            result.passed = true;
            result.message = "User sign in successful";
        } else {
            result.passed = false;
            result.message = "Sign in failed - not redirected to account page";
        }
        
    }
    catch (const std::exception& e) {
        result.passed = false;
        result.message = "Exception occurred: " + std::string(e.what());
    }
    
    return result;
}

SignInTests::TestResult SignInTests::testSignInWithInvalidCredentials() {
    TestResult result;
    result.testName = "Sign In with Invalid Credentials";
    
    try {
        // Navigate to sign in page
        homePage.navigateToHomepage();
        homePage.navigateToSignIn();
        
        // Try to sign in with invalid credentials
        signInPage.performSignIn("invalid@test.com", "WrongPassword123");
        
        // Check for error message
        std::this_thread::sleep_for(std::chrono::seconds(2));
        
        if (signInPage.isErrorMessageDisplayed()) {
            result.passed = true;
            result.message = "Invalid credentials validation working correctly";
        } else {
            result.passed = false;
            result.message = "Invalid credentials validation not working";
        }
        
    }
    catch (const std::exception& e) {
        result.passed = false;
        result.message = "Exception occurred: " + std::string(e.what());
    }
    
    return result;
}

SignInTests::TestResult SignInTests::testSignInWithEmptyFields() {
    TestResult result;
    result.testName = "Sign In with Empty Fields";
    
    try {
        // Navigate to sign in page
        homePage.navigateToHomepage();
        homePage.navigateToSignIn();
        
        // Try to sign in with empty fields
        signInPage.clickSignIn();
        
        // Check for validation error messages
        std::this_thread::sleep_for(std::chrono::seconds(2));
        
        if (signInPage.isEmailErrorDisplayed() || signInPage.isPasswordErrorDisplayed() || signInPage.isErrorMessageDisplayed()) {
            result.passed = true;
            result.message = "Empty fields validation working correctly";
        } else {
            result.passed = false;
            result.message = "Empty fields validation not working";
        }
        
    }
    catch (const std::exception& e) {
        result.passed = false;
        result.message = "Exception occurred: " + std::string(e.what());
    }
    
    return result;
}

SignInTests::TestResult SignInTests::testSignInWithInvalidEmail() {
    TestResult result;
    result.testName = "Sign In with Invalid Email Format";
    
    try {
        // Navigate to sign in page
        homePage.navigateToHomepage();
        homePage.navigateToSignIn();
        
        // Try to sign in with invalid email format
        signInPage.performSignIn("invalid-email-format", "SomePassword123");
        
        // Check for error message
        std::this_thread::sleep_for(std::chrono::seconds(2));
        
        if (signInPage.isErrorMessageDisplayed() || signInPage.isEmailErrorDisplayed()) {
            result.passed = true;
            result.message = "Invalid email format validation working correctly";
        } else {
            result.passed = false;
            result.message = "Invalid email format validation not working";
        }
        
    }
    catch (const std::exception& e) {
        result.passed = false;
        result.message = "Exception occurred: " + std::string(e.what());
    }
    
    return result;
}

void SignInTests::runAllSignInTests() {
    std::cout << "\n========== RUNNING SIGN IN TESTS ==========\n" << std::endl;
    
    printTestResult(testSuccessfulUserSignIn());
    printTestResult(testSignInWithInvalidCredentials());
    printTestResult(testSignInWithEmptyFields());
    printTestResult(testSignInWithInvalidEmail());
    
    std::cout << "\n========== SIGN IN TESTS COMPLETED ==========\n" << std::endl;
}

void SignInTests::printTestResult(const TestResult& result) {
    std::cout << "Test: " << result.testName << std::endl;
    std::cout << "Status: " << (result.passed ? "PASSED" : "FAILED") << std::endl;
    std::cout << "Message: " << result.message << std::endl;
    std::cout << "----------------------------------------" << std::endl;
}

// ============================================================================
// 22. src/main.cpp
// ============================================================================
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