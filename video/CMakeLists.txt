add_library(video
        video.c
)

target_include_directories(video
        PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(video
        PUBLIC
        SDL3::SDL3
)
