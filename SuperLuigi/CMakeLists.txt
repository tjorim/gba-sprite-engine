project(SuperLuigi)

add_executable(${PROJECT_NAME}.elf
        src/main.cpp
        src/level1.cpp
        src/level1.h src/background.h src/Luigi.h src/start_scene.cpp src/start_scene.h src/goomba.h src/sharedPal.h)

target_link_libraries(${PROJECT_NAME}.elf gba-sprite-engine)

add_custom_command(TARGET ${PROJECT_NAME}.elf POST_BUILD
        COMMAND ${CMAKE_OBJCOPY} -v -O binary ${PROJECT_NAME}.elf ${PROJECT_NAME}.gba
        )