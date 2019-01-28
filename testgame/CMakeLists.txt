project(testgame)

add_executable(${PROJECT_NAME}.elf
        src/main.cpp
        src/MainScene.cpp
        src/MainScene.h
        src/mooiman.h
        src/bird1.h
        src/bird1.c
        src/fb1MAP.h
        src/flappybird.c
        src/flappybird.h)

target_link_libraries(${PROJECT_NAME}.elf gba-sprite-engine)

add_custom_command(TARGET ${PROJECT_NAME}.elf POST_BUILD
        COMMAND ${CMAKE_OBJCOPY} -v -O binary ${PROJECT_NAME}.elf ${PROJECT_NAME}.gba
        )
