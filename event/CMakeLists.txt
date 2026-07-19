add_library(event
        event.c
)

target_include_directories(event
        PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(event
        PUBLIC
        SDL3::SDL3
)
target_link_libraries(event
        PUBLIC
        imgui
)