cmake_minimum_required(VERSION 3.16)
project(CHIP-8)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
# set the output directory for built objects.
# This makes sure that the dynamic library goes into the build directory automatically.
#set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/$<CONFIGURATION>")
#set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/$<CONFIGURATION>")

# This assumes the SDL source is available in vendored/SDL
add_subdirectory(vendored/SDL EXCLUDE_FROM_ALL)
add_subdirectory(video)
add_subdirectory(event)

# Create your game executable target as usual


add_executable(main  main.c)

# Link against the video library
target_link_libraries(main PRIVATE video)

target_link_libraries(main PRIVATE event)











