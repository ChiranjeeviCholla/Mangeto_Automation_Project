#include "SignUpTests.h"
#include "TestDataGenerator.h"
#include <iostream>
#include <thread>

SignUpTests::TestResult SignUpTests::testSuccessfulUserRegistration() {
    TestResult result;
    result.testName = "Successful User Registration";
    
    try {
        // Generate test data
        std::string email = TestDataGenerator::generateUniqueEmail();
        std::string password = TestDataGenerator::generateTestPassword();
        
        // Navigate to create account page
        homePage.navigateToCreateAccount();
        
        // Fill registration form
        createAccountPage.fillRegistrationForm("John", "Doe", email, password, password);
        
        // Submit form
        createAccountPage.clickCreateAccount();
        
        // Verify successful registration
        std::this_thread::sleep_for(std::chrono::seconds(3));
        
        if (myAccountPage.isMyAccountPageDisplayed()) {
            result.passed = true;
            result.message = "User registration successful - redirected to My Account page";
        } else {
            result.passed = false;
            result.message = "Registration failed - not redirected to My Account page";
        }
        
    }
    catch (const std::exception& e) {
        result.passed = false;
        result.message = "Exception occurred: " + std::string(e.what());
    }
    
    return result;
}

SignUpTests::TestResult SignUpTests::testRegistrationWithInvalidEmail() {
    TestResult result;
    result.testName = "Registration with Invalid Email";
    
    try {
        // Navigate to create account page
        homePage.navigateToHomepage();
        homePage.navigateToCreateAccount();
        
        // Fill form with invalid email
        createAccountPage.fillRegistrationForm("Jane", "Doe", "invalid-email", "Test@123", "Test@123");
        createAccountPage.clickCreateAccount();
        
        // Check for error message
        std::this_thread::sleep_for(std::chrono::seconds(2));
        
        if (createAccountPage.isEmailErrorDisplayed() || createAccountPage.isErrorMessageDisplayed()) {
            result.passed = true;
            result.message = "Invalid email validation working correctly";
        } else {
            result.passed = false;
            result.message = "Invalid email validation not working";
        }
        
    }
    catch (const std::exception& e) {
        result.passed = false;
        result.message = "Exception occurred: " + std::string(e.what());
    }
    
    return result;
}

SignUpTests::TestResult SignUpTests::testRegistrationWithMismatchedPasswords() {
    TestResult result;
    result.testName = "Registration with Mismatched Passwords";
    
    try {
        // Navigate to create account page
        homePage.navigateToHomepage();
        homePage.navigateToCreateAccount();
        
        // Generate test data
        std::string email = TestDataGenerator::generateUniqueEmail();
        
        // Fill form with mismatched passwords
        createAccountPage.fillRegistrationForm("Bob", "Smith", email, "Test@123", "Test@456");
        createAccountPage.clickCreateAccount();
        
        // Check for error message
        std::this_thread::sleep_for(std::chrono::seconds(2));
        
        if (createAccountPage.isPasswordErrorDisplayed() || createAccountPage.isErrorMessageDisplayed()) {
            result.passed = true;
            result.message = "Password mismatch validation working correctly";
        } else {
            result.passed = false;
            result.message = "Password mismatch validation not working";
        }
        
    }
    catch (const std::exception& e) {
        result.passed = false;
        result.message = "Exception occurred: " + std::string(e.what());
    }
    
    return result;
}

SignUpTests::TestResult SignUpTests::testRegistrationWithEmptyFields() {
    TestResult result;
    result.testName = "Registration with Empty Fields";
    
    try {
        // Navigate to create account page
        homePage.navigateToHomepage();
        homePage.navigateToCreateAccount();
        
        // Try to submit form with empty fields
        createAccountPage.clickCreateAccount();
        
        // Check for validation error messages
        std::this_thread::sleep_for(std::chrono::seconds(2));
        
        if (createAccountPage.isErrorMessageDisplayed()) {
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

void SignUpTests::runAllSignUpTests() {
    std::cout << "\n========== RUNNING SIGN UP TESTS ==========\n" << std::endl;
    
    printTestResult(testSuccessfulUserRegistration());
    printTestResult(testRegistrationWithInvalidEmail());
    printTestResult(testRegistrationWithMismatchedPasswords());
    printTestResult(testRegistrationWithEmptyFields());
    
    std::cout << "\n========== SIGN UP TESTS COMPLETED ==========\n" << std::endl;
}

void SignUpTests::printTestResult(const TestResult& result) {
    std::cout << "Test: " << result.testName << std::endl;
    std::cout << "Status: " << (result.passed ? "PASSED" : "FAILED") << std::endl;
    std::cout << "Message: " << result.message << std::endl;
    std::cout << "----------------------------------------" << std::endl;
}