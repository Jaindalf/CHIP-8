add_library(chip_8
        chip_8.c
        registers/register.c
        instructions/instructions.c
)
target_include_directories(chip_8
        PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
)

#add_subdirectory(registers)
#add_subdirectory(instructions)


#target_link_libraries(chip_8
 #       PRIVATE
  #      register
#)
#target_link_libraries(chip_8
#        PRIVATE
#        instructions
#)