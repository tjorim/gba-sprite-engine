project(SuperLuigi)

add_executable(${PROJECT_NAME}.elf
        src/main.cpp
        src/level1.cpp
        src/level1.h
        src/background.h
        src/LuigiTiles.h
        src/start_scene.cpp
        src/start_scene.h
        src/goombaTiles.h
        src/sharedPal.h src/music.h src/music.h src/QuestionBlockTiles.h src/Luigi.cpp src/Luigi.h src/goomba.cpp src/goomba.h src/QuestionBlock.cpp src/QuestionBlock.h src/KoopaTiles.h src/Koopa.cpp src/Koopa.h)

target_link_libraries(${PROJECT_NAME}.elf gba-sprite-engine)

add_custom_command(TARGET ${PROJECT_NAME}.elf POST_BUILD
        COMMAND ${CMAKE_OBJCOPY} -v -O binary ${PROJECT_NAME}.elf ${PROJECT_NAME}.gba
        )