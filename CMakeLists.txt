cmake_minimum_required(VERSION 3.21)
project(Breakout LANGUAGES CXX)

include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 2.6.x)
FetchContent_MakeAvailable(SFML)

add_executable(Breakout src/main.cpp src/direction.h src/ball.h src/ball.cpp src/brick.cpp src/brick.h src/bouncePad.cpp src/bouncePad.h)
target_link_libraries(Breakout PRIVATE sfml-graphics)
target_compile_features(Breakout PRIVATE cxx_std_17)
if (WIN32 AND BUILD_SHARED_LIBS)
    add_custom_command(TARGET Breakout POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_RUNTIME_DLLS:Breakout> $<TARGET_FILE_DIR:Breakout> COMMAND_EXPAND_LISTS
        COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/src/Assets $<TARGET_FILE_DIR:Breakout/Assets)
endif()

install(TARGETS Breakout)
