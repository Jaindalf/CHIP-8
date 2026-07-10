add_library(instructions
        instructions.c
)

target_include_directories(instructions
        PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/..
)

