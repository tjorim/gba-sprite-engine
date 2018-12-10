project(GBA_game)

add_executable(${PROJECT_NAME}.elf
        src/main.cpp
        src/start_scene.cpp
        src/start_scene.h
        src/background.h src/backgroundtest.h src/game_play_scene.cpp src/game_play_scene.h src/Sonic_sprites.h)

target_link_libraries(${PROJECT_NAME}.elf gba-sprite-engine)

add_custom_command(TARGET ${PROJECT_NAME}.elf POST_BUILD
        COMMAND ${CMAKE_OBJCOPY} -v -O binary ${PROJECT_NAME}.elf ${PROJECT_NAME}.gba
        )
