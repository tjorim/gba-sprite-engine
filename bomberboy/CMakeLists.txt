project(bomberboy)

add_executable(${PROJECT_NAME}.elf
        src/main.cpp src/sound.h
        src/test_scene.cpp src/test_scene.h src/Models/Dude.cpp src/Models/Dude.h src/Controllers/PlayerController.cpp
        src/Controllers/PlayerController.h src/Lib/RCoord.cpp src/Lib/RCoord.h)

target_link_libraries(${PROJECT_NAME}.elf gba-sprite-engine)

add_custom_command(TARGET ${PROJECT_NAME}.elf POST_BUILD
        COMMAND ${CMAKE_OBJCOPY} -v -O binary ${PROJECT_NAME}.elf ${PROJECT_NAME}.gba
        )
