cmake_minimum_required(VERSION 3.4)

include("cmake/HunterGate.cmake")
HunterGate(
        URL "https://github.com/cpp-pm/hunter/archive/v0.23.251.tar.gz"
        SHA1 "5659b15dc0884d4b03dbd95710e6a1fa0fc3258d"
)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

option(BUILD_EXAMPLES "Build examples" ON)
option(BUILD_TESTS "Build tests" ON)

project(alpha)
set(ALPHA_VERSION_MAJOR 0)
set(ALPHA_VERSION_MINOR 1)
set(ALPHA_VERSION_PATCH 0)
set(ALPHA_VERSION_TWEAK 0)
set(ALPHA_VERSION
        ${ALPHA_VERSION_MAJOR}.${ALPHA_VERSION_MINOR}.${ALPHA_VERSION_PATCH}.${ALPHA_VERSION_TWEAK})
set(ALPHA_VERSION_STRING "v${ALPHA_VERSION}")

hunter_add_package(GTest)
find_package(GTest CONFIG REQUIRED)

add_library(alpha STATIC ${CMAKE_CURRENT_SOURCE_DIR}/sources/alpha.cpp)

target_include_directories(alpha PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
        )

if(BUILD_EXAMPLES)
    file(GLOB EXAMPLE_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/examples/*.cpp")
    foreach(EXAMPLE_SOURCE ${EXAMPLE_SOURCES})
        get_filename_component(EXAMPLE_NAME ${EXAMPLE_SOURCE} NAME_WE)
        add_executable(${EXAMPLE_NAME} ${EXAMPLE_SOURCE} include/alpha.h sources/alpha.cpp)
        target_link_libraries(${EXAMPLE_NAME} alpha)
        install(TARGETS ${EXAMPLE_NAME}
                RUNTIME DESTINATION bin
                )
    endforeach(EXAMPLE_SOURCE ${EXAMPLE_SOURCES})
endif()

install(TARGETS alpha
        EXPORT alpha-config
        ARCHIVE DESTINATION lib
        LIBRARY DESTINATION lib
        )

install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/include/ DESTINATION include)
install(EXPORT alpha-config DESTINATION cmake)

if(BUILD_TESTS)
    enable_testing()
    file(GLOB ${PROJECT_NAME}_TEST_SOURCES tests/*.cpp)
    add_executable(check ${${PROJECT_NAME}_TEST_SOURCES})
    target_link_libraries(check ${PROJECT_NAME} GTest::gtest_main)
    add_test(NAME check COMMAND check)
endif()

include(CPackConfig.cmake)