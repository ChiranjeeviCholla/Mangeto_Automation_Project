#ifndef CREATEACCOUNTPAGE_H
#define CREATEACCOUNTPAGE_H

#include "BasePage.h"

class CreateAccountPage : public BasePage {
private:
    selenium::By firstNameField = selenium::By::id("firstname");
    selenium::By lastNameField = selenium::By::id("lastname");
    selenium::By emailField = selenium::By::id("email_address");
    selenium::By passwordField = selenium::By::id("password");
    selenium::By confirmPasswordField = selenium::By::id("password-confirmation");
    selenium::By createAccountButton = selenium::By::cssSelector("button[title='Create an Account']");
    selenium::By errorMessage = selenium::By::cssSelector(".message-error");
    selenium::By emailErrorMessage = selenium::By::id("email_address-error");
    selenium::By passwordErrorMessage = selenium::By::id("password-confirmation-error");
    selenium::By successMessage = selenium::By::cssSelector(".message-success");

public:
    void enterFirstName(const std::string& firstName);
    void enterLastName(const std::string& lastName);
    void enterEmail(const std::string& email);
    void enterPassword(const std::string& password);
    void enterConfirmPassword(const std::string& confirmPassword);
    void clickCreateAccount();
    void fillRegistrationForm(const std::string& firstName, const std::string& lastName,
                             const std::string& email, const std::string& password,
                             const std::string& confirmPassword);
    bool isErrorMessageDisplayed();
    bool isEmailErrorDisplayed();
    bool isPasswordErrorDisplayed();
    bool isSuccessMessageDisplayed();
    std::string getErrorMessage();
};

#endif