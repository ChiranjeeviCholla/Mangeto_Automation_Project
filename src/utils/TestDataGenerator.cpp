#include "TestDataGenerator.h"
#include <chrono>
#include <random>
#include <sstream>
#include <iomanip>

std::string TestDataGenerator::generateUniqueEmail() {
    std::string timestamp = getCurrentTimestamp();
    return "testuser" + timestamp + "@automation.test";
}

std::string TestDataGenerator::generateRandomString(int length) {
    const std::string chars = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789";
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, chars.length() - 1);
    
    std::string result;
    for (int i = 0; i < length; ++i) {
        result += chars[dis(gen)];
    }
    return result;
}

std::string TestDataGenerator::getCurrentTimestamp() {
    auto now = std::chrono::system_clock::now();
    auto time_t = std::chrono::system_clock::to_time_t(now);
    auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(
        now.time_since_epoch()) % 1000;
    
    std::stringstream ss;
    ss << std::put_time(std::localtime(&time_t), "%Y%m%d%H%M%S");
    ss << std::setfill('0') << std::setw(3) << ms.count();
    return ss.str();
}

std::string TestDataGenerator::generateTestPassword() {
    return "Test@123";
}
