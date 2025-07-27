#include "StepDefinitions.h"
#include "DriverManager.h"
#include <iostream>
#include <thread>
#include <cassert>

StepDefinitions::StepDefinitions() : registeredPassword("Test@123") {}

// ============================================================================
// CUCUMBER STEP DEFINITIONS
// ============================================================================

// Given steps
GIVEN("^I am on the Magento homepage$") {
    REGEX_PARAM(std::string, text);
    StepDefinitions stepDefs;
    stepDefs.navigateToHomepage();
}

GIVEN("^I have a registered user account$") {
    StepDefinitions stepDefs;
    stepDefs.createRegisteredAccount();
}

// When steps
WHEN("^I navigate to the Create Account page$") {
    StepDefinitions stepDefs;
    stepDefs.navigateToCreateAccount();
}

WHEN("^I navigate to the Sign In page$") {
    StepDefinitions stepDefs;
    stepDefs.navigateToSignIn();
}

WHEN("^I fill the registration form with the following details:$") {
    TABLE_PARAM(table);
    StepDefinitions stepDefs;
    
    std::map<std::string, std::string> formData;
    auto headers = table.hashes();
    
    for (const auto& row : headers) {
        for (const auto& cell : row) {
            formData[cell.first] = cell.second;
        }
    }
    
    stepDefs.fillRegistrationForm(formData);
}

WHEN("^I fill the registration form with missing \"([^\"]*)\"$") {
    REGEX_PARAM(std::string, missingField);
    StepDefinitions stepDefs;
    stepDefs.fillRegistrationFormWithMissingField(missingField);
}

WHEN("^I submit the registration form$") {
    StepDefinitions stepDefs;
    stepDefs.submitRegistrationForm();
}

WHEN("^I enter my valid email and password$") {
    StepDefinitions stepDefs;
    stepDefs.enterValidCredentials();
}

WHEN("^I enter invalid email \"([^\"]*)\"$") {
    REGEX_PARAM(std::string, email);
    StepDefinitions stepDefs;
    stepDefs.enterInvalidCredentials(email, "SomePassword123");
}

WHEN("^I enter password \"([^\"]*)\"$") {
    REGEX_PARAM(std::string, password);
    // This would be combined with email entry in actual implementation
}

WHEN("^I click the Sign In button$") {
    StepDefinitions stepDefs;
    stepDefs.submitSignInForm();
}

WHEN("^I leave email field empty$") {
    // Implementation for leaving email empty
    StepDefinitions stepDefs;
    stepDefs.enterInvalidCredentials("", "SomePassword");
}

WHEN("^I leave password field empty$") {
    // Implementation for leaving password empty  
    StepDefinitions stepDefs;
    stepDefs.enterInvalidCredentials("test@example.com", "");
}

// Then steps
THEN("^I should be redirected to My Account dashboard$") {
    StepDefinitions stepDefs;
    stepDefs.verifySuccessfulRegistration();
}

THEN("^I should see a welcome message$") {
    StepDefinitions stepDefs;
    stepDefs.verifyWelcomeMessage();
}

THEN("^my account information should be displayed$") {
    StepDefinitions stepDefs;
    stepDefs.verifySuccessfulSignIn();
}

THEN("^I should see an email validation error message$") {
    StepDefinitions stepDefs;
    stepDefs.verifyRegistrationError("email");
}

THEN("^I should see a password mismatch error message$") {
    StepDefinitions stepDefs;
    stepDefs.verifyRegistrationError("password_mismatch");
}

THEN("^I should see a validation error for \"([^\"]*)\"$") {
    REGEX_PARAM(std::string, fieldName);
    StepDefinitions stepDefs;
    stepDefs.verifyRegistrationError(fieldName);
}

THEN("^I should remain on the Create Account page$") {
    StepDefinitions stepDefs;
    stepDefs.verifyOnPage("Create Account");
}

THEN("^I should see an invalid credentials error message$") {
    StepDefinitions stepDefs;
    stepDefs.verifySignInError("invalid_credentials");
}

THEN("^I should remain on the Sign In page$") {
    StepDefinitions stepDefs;
    stepDefs.verifyOnPage("Sign In");
}

THEN("^I should see required field validation messages$") {
    StepDefinitions stepDefs;
    stepDefs.verifySignInError("required_fields");
}
void StepDefinitions::navigateToHomepage() {
    homePage.navigateToHomepage();
    std::cout << "Navigated to Magento homepage" << std::endl;
}

void StepDefinitions::navigateToCreateAccount() {
    homePage.navigateToCreateAccount();
    std::cout << "Navigated to Create Account page" << std::endl;
}

void StepDefinitions::navigateToSignIn() {
    homePage.navigateToSignIn();
    std::cout << "Navigated to Sign In page" << std::endl;
}

void StepDefinitions::fillRegistrationForm(const std::map<std::string, std::string>& data) {
    formData = data;
    
    // Generate unique email if needed
    std::string email = data.at("email");
    if (email == "auto-generated-email") {
        generatedEmail = TestDataGenerator::generateUniqueEmail();
        email = generatedEmail;
    }
    
    createAccountPage.fillRegistrationForm(
        data.at("firstName"),
        data.at("lastName"),
        email,
        data.at("password"),
        data.at("confirmPassword")
    );
    
    std::cout << "Filled registration form with provided data" << std::endl;
}

void StepDefinitions::fillRegistrationFormWithMissingField(const std::string& missingField) {
    std::string firstName = (missingField == "firstName") ? "" : "John";
    std::string lastName = (missingField == "lastName") ? "" : "Doe";
    std::string email = (missingField == "email") ? "" : TestDataGenerator::generateUniqueEmail();
    std::string password = (missingField == "password") ? "" : "Test@123";
    std::string confirmPassword = (missingField == "confirmPassword") ? "" : "Test@123";
    
    createAccountPage.fillRegistrationForm(firstName, lastName, email, password, confirmPassword);
    std::cout << "Filled registration form with missing field: " << missingField << std::endl;
}

void StepDefinitions::submitRegistrationForm() {
    createAccountPage.clickCreateAccount();
    std::this_thread::sleep_for(std::chrono::seconds(3));
    std::cout << "Submitted registration form" << std::endl;
}

void StepDefinitions::verifySuccessfulRegistration() {
    bool isOnAccountPage = myAccountPage.isMyAccountPageDisplayed();
    assert(isOnAccountPage && "User should be redirected to My Account page after successful registration");
    std::cout << "Verified successful registration - user on My Account page" << std::endl;
}

void StepDefinitions::verifyRegistrationError(const std::string& errorType) {
    bool hasError = false;
    std::string errorMessage;
    
    if (errorType == "email") {
        hasError = createAccountPage.isEmailErrorDisplayed() || createAccountPage.isErrorMessageDisplayed();
        errorMessage = "Email validation error";
    }
    else if (errorType == "password_mismatch") {
        hasError = createAccountPage.isPasswordErrorDisplayed() || createAccountPage.isErrorMessageDisplayed();
        errorMessage = "Password mismatch error";
    }
    else {
        hasError = createAccountPage.isErrorMessageDisplayed();
        errorMessage = "Validation error for " + errorType;
    }
    
    assert(hasError && ("Expected " + errorMessage + " to be displayed").c_str());
    std::cout << "Verified registration error: " << errorMessage << std::endl;
}

void StepDefinitions::createRegisteredAccount() {
    registeredEmail = TestDataGenerator::generateUniqueEmail();
    
    // Navigate and create account
    homePage.navigateToCreateAccount();
    createAccountPage.fillRegistrationForm("Test", "User", registeredEmail, registeredPassword, registeredPassword);
    createAccountPage.clickCreateAccount();
    
    std::this_thread::sleep_for(std::chrono::seconds(3));
    
    bool accountCreated = myAccountPage.isMyAccountPageDisplayed();
    assert(accountCreated && "Failed to create test account");
    
    std::cout << "Created registered test account with email: " << registeredEmail << std::endl;
}

void StepDefinitions::enterValidCredentials() {
    signInPage.performSignIn(registeredEmail, registeredPassword);
    std::cout << "Entered valid credentials for sign in" << std::endl;
}

void StepDefinitions::enterInvalidCredentials(const std::string& email, const std::string& password) {
    signInPage.performSignIn(email, password);
    std::cout << "Entered invalid credentials: " << email << std::endl;
}

void StepDefinitions::submitSignInForm() {
    signInPage.clickSignIn();
    std::this_thread::sleep_for(std::chrono::seconds(2));
    std::cout << "Submitted sign in form" << std::endl;
}

void StepDefinitions::verifySuccessfulSignIn() {
    bool isSignedIn = myAccountPage.isMyAccountPageDisplayed() || homePage.isUserLoggedIn();
    assert(isSignedIn && "User should be signed in successfully");
    std::cout << "Verified successful sign in" << std::endl;
}

void StepDefinitions::verifySignInError(const std::string& errorType) {
    bool hasError = false;
    std::string errorMessage;
    
    if (errorType == "invalid_credentials") {
        hasError = signInPage.isErrorMessageDisplayed();
        errorMessage = "Invalid credentials error";
    }
    else if (errorType == "required_fields") {
        hasError = signInPage.isEmailErrorDisplayed() || signInPage.isPasswordErrorDisplayed() || signInPage.isErrorMessageDisplayed();
        errorMessage = "Required fields validation error";
    }
    else {
        hasError = signInPage.isErrorMessageDisplayed();
        errorMessage = "Sign in error: " + errorType;
    }
    
    assert(hasError && ("Expected " + errorMessage + " to be displayed").c_str());
    std::cout << "Verified sign in error: " << errorMessage << std::endl;
}

void StepDefinitions::verifyOnPage(const std::string& pageName) {
    std::string currentUrl = DriverManager::getDriver()->getCurrentUrl();
    
    if (pageName == "Create Account") {
        assert(currentUrl.find("customer/account/create") != std::string::npos && "Should be on Create Account page");
    }
    else if (pageName == "Sign In") {
        assert(currentUrl.find("customer/account/login") != std::string::npos && "Should be on Sign In page");
    }
    
    std::cout << "Verified user is on " << pageName << " page" << std::endl;
}

void StepDefinitions::verifyWelcomeMessage() {
    bool hasWelcomeMessage = myAccountPage.isContactInformationDisplayed() || !myAccountPage.getWelcomeMessage().empty();
    assert(hasWelcomeMessage && "Welcome message should be displayed");
    std::cout << "Verified welcome message is displayed" << std::endl;
}
