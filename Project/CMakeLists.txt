project(project)

add_executable(${PROJECT_NAME}.elf
        src/main.cpp
        src/start_scene.cpp
        src/start_scene.h
        src/game_scene.cpp
        src/game_scene.h

        src/space_ship.cpp src/space_ship.h src/level.cpp src/level.h src/ground.cpp src/ground.h src/groundbackground.h)

target_link_libraries(${PROJECT_NAME}.elf gba-sprite-engine)

add_custom_command(TARGET ${PROJECT_NAME}.elf POST_BUILD
        COMMAND ${CMAKE_OBJCOPY} -v -O binary ${PROJECT_NAME}.elf ${PROJECT_NAME}.gba
        )