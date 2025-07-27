#ifndef STEPDEFINITIONS_H
#define STEPDEFINITIONS_H

#include <cucumber-cpp/autodetect.hpp>
#include "HomePage.h"
#include "CreateAccountPage.h"
#include "SignInPage.h"
#include "MyAccountPage.h"
#include "TestDataGenerator.h"
#include <string>
#include <map>

class StepDefinitions {
private:
    HomePage homePage;
    CreateAccountPage createAccountPage;
    SignInPage signInPage;
    MyAccountPage myAccountPage;
    
    std::string generatedEmail;
    std::string registeredEmail;
    std::string registeredPassword;
    std::map<std::string, std::string> formData;

public:
    StepDefinitions();
    
    // Common steps
    void navigateToHomepage();
    void navigateToCreateAccount();
    void navigateToSignIn();
    
    // Registration steps
    void fillRegistrationForm(const std::map<std::string, std::string>& data);
    void fillRegistrationFormWithMissingField(const std::string& missingField);
    void submitRegistrationForm();
    void verifySuccessfulRegistration();
    void verifyRegistrationError(const std::string& errorType);
    
    // Sign in steps
    void createRegisteredAccount();
    void enterValidCredentials();
    void enterInvalidCredentials(const std::string& email, const std::string& password);
    void submitSignInForm();
    void verifySuccessfulSignIn();
    void verifySignInError(const std::string& errorType);
    
    // Verification steps
    void verifyOnPage(const std::string& pageName);
    void verifyErrorMessage(const std::string& messageType);
    void verifyWelcomeMessage();
};

#endif