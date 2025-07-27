cmake_minimum_required(VERSION 3.16)
project(MagentoAutomation)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find packages
find_package(PkgConfig REQUIRED)
pkg_check_modules(SELENIUM REQUIRED selenium-cpp)

# Include directories
include_directories(${SELENIUM_INCLUDE_DIRS})
include_directories(src/pages)
include_directories(src/utils)
include_directories(src/tests)

# Source files
set(SOURCES
    src/main.cpp
    src/pages/BasePage.cpp
    src/pages/HomePage.cpp
    src/pages/CreateAccountPage.cpp
    src/pages/SignInPage.cpp
    src/pages/MyAccountPage.cpp
    src/utils/DriverManager.cpp
    src/utils/ConfigReader.cpp
    src/utils/TestDataGenerator.cpp
    src/tests/SignUpTests.cpp
    src/tests/SignInTests.cpp
)

# Create executable
add_executable(${PROJECT_NAME} ${SOURCES})

# Link libraries
target_link_libraries(${PROJECT_NAME} ${SELENIUM_LIBRARIES} pthread)

# Compiler flags
target_compile_options(${PROJECT_NAME} PRIVATE ${SELENIUM_CFLAGS_OTHER})