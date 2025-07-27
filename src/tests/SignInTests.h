#ifndef SIGNINTESTS_H
#define SIGNINTESTS_H

#include "HomePage.h"
#include "SignInPage.h"
#include "CreateAccountPage.h"
#include "MyAccountPage.h"
#include <string>

class SignInTests {
private:
    HomePage homePage;
    SignInPage signInPage;
    CreateAccountPage createAccountPage;
    MyAccountPage myAccountPage;
    
    struct TestResult {
        bool passed;
        std::string message;
        std::string testName;
    };
    
    std::string registeredEmail;
    std::string registeredPassword;

public:
    TestResult testSuccessfulUserSignIn();
    TestResult testSignInWithInvalidCredentials();
    TestResult testSignInWithEmptyFields();
    TestResult testSignInWithInvalidEmail();
    void runAllSignInTests();
    void printTestResult(const TestResult& result);
    bool createTestAccount();
};

#endif