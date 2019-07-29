project(jetjoy)

add_executable(${PROJECT_NAME}.elf
        src/main.cpp
        src/jetjoy_start_scene.cpp src/jetjoy_start_scene.h
        src/jetjoy_game_scene.cpp src/jetjoy_game_scene.h
        src/z_background.h src/z_sharedpal.h src/ship.cpp src/ship.h src/z_ghost.h src/z_ship.h src/ghost.cpp src/ghost.h src/z_laser.h src/jetjoy_dead_scene.cpp src/jetjoy_dead_scene.h src/laser.cpp src/laser.h)

target_link_libraries(${PROJECT_NAME}.elf gba-sprite-engine)

add_custom_command(TARGET ${PROJECT_NAME}.elf POST_BUILD
        COMMAND ${CMAKE_OBJCOPY} -v -O binary ${PROJECT_NAME}.elf ${PROJECT_NAME}.gba
        )