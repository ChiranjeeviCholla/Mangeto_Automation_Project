#include "BDDTestRunner.h"
#include "DriverManager.h"
#include "ConfigReader.h"
#include <iostream>
#include <vector>

void printBDDHeader() {
    std::cout << "==========================================" << std::endl;
    std::cout << "  MAGENTO BDD AUTOMATION FRAMEWORK" << std::endl;
    std::cout << "  Cucumber-CPP + Selenium WebDriver" << std::endl;
    std::cout << "==========================================" << std::endl;
}

int main(int argc, char* argv[]) {
    printBDDHeader();
    
    try {
        BDDTestRunner runner("features/");
        
        // Parse command line arguments for tags
        std::vector<std::string> tags;
        for (int i = 1; i < argc; ++i) {
            std::string arg = argv[i];
            if (arg.starts_with("--tags=")) {
                std::string tagList = arg.substr(7);
                // Parse comma-separated tags
                size_t pos = 0;
                while ((pos = tagList.find(',')) != std::string::npos) {
                    tags.push_back(tagList.substr(0, pos));
                    tagList.erase(0, pos + 1);
                }
                if (!tagList.empty()) {
                    tags.push_back(tagList);
                }
            }
        }
        
        bool success = false;
        
        if (!tags.empty()) {
            std::cout << "Running scenarios with specific tags..." << std::endl;
            success = runner.runTaggedScenarios(tags);
        } else {
            std::cout << "Running all BDD features..." << std::endl;
            success = runner.runAllFeatures();
        }
        
        // Generate reports
        runner.generateReport();
        runner.printExecutionSummary();
        
        return success ? 0 : 1;
        
    }
    catch (const std::exception& e) {
        std::cerr << "Fatal error in BDD execution: " << e.what() << std::endl;
        return 1;
    }
}
