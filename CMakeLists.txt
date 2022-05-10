cmake_minimum_required(VERSION 3.0.0)

project(breakout)

file(GLOB codeFiles *.cpp)


set(CMAKE_CXX_STANDARD, 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -Wall -Wextra")

# set color output
# set(ENV{GCC_COLORS} "error=01;31:warning=01;35:note=01;36:caret=01;32:locus=01:quote=01")

# place executable in /bin directory
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

add_executable(breakout ${codeFiles})

# link libraries
target_link_libraries(breakout sfml-graphics)
target_link_libraries(breakout sfml-window)
target_link_libraries(breakout sfml-system)
target_link_libraries(breakout sfml-audio)

