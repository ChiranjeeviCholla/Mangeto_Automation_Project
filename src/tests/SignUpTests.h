#ifndef SIGNUPTESTS_H
#define SIGNUPTESTS_H

#include "HomePage.h"
#include "CreateAccountPage.h"
#include "MyAccountPage.h"
#include <string>

class SignUpTests {
private:
    HomePage homePage;
    CreateAccountPage createAccountPage;
    MyAccountPage myAccountPage;
    
    struct TestResult {
        bool passed;
        std::string message;
        std::string testName;
    };

public:
    TestResult testSuccessfulUserRegistration();
    TestResult testRegistrationWithInvalidEmail();
    TestResult testRegistrationWithMismatchedPasswords();
    TestResult testRegistrationWithEmptyFields();
    void runAllSignUpTests();
    void printTestResult(const TestResult& result);
};

#endif