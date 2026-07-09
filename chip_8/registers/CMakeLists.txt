add_library(register
        register.c
)

target_include_directories(register
        PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
)
