project(GBA_game)

add_executable(${PROJECT_NAME}.elf
        src/main.cpp
        src/start_scene.cpp
        src/start_scene.h
        src/background.h src/backgroundtest.h src/scene_level1.cpp src/scene_level1.h src/Sonic_sprites.h src/Sound.h src/player.cpp src/player.h src/background_level1.h src/scene_level2.cpp src/scene_level2.h)

target_link_libraries(${PROJECT_NAME}.elf gba-sprite-engine)

add_custom_command(TARGET ${PROJECT_NAME}.elf POST_BUILD
        COMMAND ${CMAKE_OBJCOPY} -v -O binary ${PROJECT_NAME}.elf ${PROJECT_NAME}.gba
        )
