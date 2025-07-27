#ifndef BDDTESTRUNNER_H
#define BDDTESTRUNNER_H

#include <string>
#include <vector>

class BDDTestRunner {
private:
    std::string featuresPath;
    std::string stepDefinitionsPath;
    std::vector<std::string> tags;
    
public:
    BDDTestRunner(const std::string& featuresPath = "features/");
    
    void addTag(const std::string& tag);
    void clearTags();
    void setFeaturesPath(const std::string& path);
    
    bool runFeature(const std::string& featureFile);
    bool runAllFeatures();
    bool runTaggedScenarios(const std::vector<std::string>& includeTags);
    
    void generateReport(const std::string& outputPath = "test-results/");
    void printExecutionSummary();
    
private:
    bool executeScenario(const std::string& scenarioName);
    void setupEnvironment();
    void teardownEnvironment();
};

#endif 