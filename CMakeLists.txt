cmake_minimum_required(VERSION 3.8)

#Project config
set(PROJECT_NAME "manTest")
if(DEFINED ENV{TRAVIS_BUILD_NUMBER})
  project(${PROJECT_NAME} VERSION 0.0.$ENV{TRAVIS_BUILD_NUMBER})
else()
  project(${PROJECT_NAME} VERSION 0.0.1)
endif()



#Packages
#set (GTEST_ROOT /usr/src/gtest)

find_package(fmt CONFIG REQUIRED)
find_package(glfw3 CONFIG REQUIRED)

#add_subdirectory("include/api")

#Targets
add_executable(${PROJECT_NAME} tests/ManualTestingSandbox.cpp)

#Compilation setings
set_target_properties(${PROJECT_NAME}
PROPERTIES
	CXX_STANDARD 20
    CXX_STANDARD_REQUIRED ON
    COMPILE_OPTIONS "/std:c++latest;"
)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)
target_link_libraries(${PROJECT_NAME} PRIVATE fmt::fmt fmt::fmt-header-only)
target_link_libraries(${PROJECT_NAME} PRIVATE glfw)
