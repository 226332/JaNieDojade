cmake_minimum_required(VERSION 2.8)
project(JaNieDojade)
#add_subdirectory(test)
set(Boost_USE_STATIC_LIBS OFF)
set(Boost_USE_MULTITHREADED ON) 
set(Boost_USE_STATIC_RUNTIME OFF)
find_package(Boost COMPONENTS system filesystem unit_test_framework REQUIRED)

set(TSOURCES test/Tests.cpp )
set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_FLAGS "-std=c++14 -Wall -pedantic") # -fsanitize=address -std=c++14

if(Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS} ${CMAKE_CURRENT_SOURCE_DIR}/inc/)
    link_directories(${Boost_LIBRARY_DIRS})
    add_executable(${CMAKE_PROJECT_NAME} ${TSOURCES})
    target_link_libraries(${CMAKE_PROJECT_NAME}
                          ${Boost_LIBRARIES}
                          ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY})
else()
    message(FATAL_ERROR, "Please install boost!")
endif()

add_custom_target(run
    COMMAND ${CMAKE_PROJECT_NAME}
)







