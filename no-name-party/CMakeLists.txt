project(no-name-party)               # Create project "no-name-party"

add_executable(${PROJECT_NAME}.elf
        src/main.cpp
        src/scenes/end_scene.cpp src/scenes/end_scene.h
        src/scenes/game_scene.cpp src/scenes/game_scene.h
        src/scenes/select_scene.cpp src/scenes/select_scene.h
        src/scenes/start_scene.cpp src/scenes/start_scene.h
        src/balloon.h src/character.h src/result.h
        src/player.cpp src/player.h
        )

target_link_libraries(${PROJECT_NAME}.elf gba-sprite-engine)

add_custom_command(TARGET ${PROJECT_NAME}.elf POST_BUILD
        COMMAND ${CMAKE_OBJCOPY} -v -O binary ${PROJECT_NAME}.elf ${PROJECT_NAME}.gba
        )
