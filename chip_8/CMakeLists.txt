add_library(chip_8
        chip_8.c
)
target_include_directories(chip_8
        PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
)

add_subdirectory(registers)

target_link_libraries(chip_8
        PRIVATE
        register
)
