#ifndef TESTDATAGENERATOR_H
#define TESTDATAGENERATOR_H

#include <string>

class TestDataGenerator {
public:
    static std::string generateUniqueEmail();
    static std::string generateRandomString(int length);
    static std::string getCurrentTimestamp();
    static std::string generateTestPassword();
};

#endif 