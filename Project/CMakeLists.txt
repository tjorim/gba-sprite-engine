project(RollingStone)

add_executable(${PROJECT_NAME}.elf
        src/main.cpp
        src/space_Kirby_game_scene.cpp
        src/space_Kirby_game_scene.h
        src/start_screen.cpp
        src/start_screen.h
        src/background_image.h src/start_screen_palette.h src/theme_song.h src/space_kirby_game_palette.h src/death_scene.cpp src/death_scene.h src/dead_sound.h src/Kirby.h src/enemy.h src/platform.h src/Kirby_title.h src/press_start.h src/space_title.h src/startscene_Kirby.h)

target_link_libraries(${PROJECT_NAME}.elf gba-sprite-engine)

add_custom_command(TARGET ${PROJECT_NAME}.elf POST_BUILD
        COMMAND ${CMAKE_OBJCOPY} -v -O binary ${PROJECT_NAME}.elf ${PROJECT_NAME}.gba
        )
