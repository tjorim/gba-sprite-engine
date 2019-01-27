project(bomberboy)

add_executable(${PROJECT_NAME}.elf
        src/main.cpp
        src/scenes/end_scene.cpp src/scenes/end_scene.h
        src/scenes/game_scene.cpp src/scenes/game_scene.h
        src/scenes/start_scene.cpp src/scenes/start_scene.h
        src/sound.h
        src/thing.h
        src/thing/bomb.cpp src/thing/bomb.h
        src/thing/player.cpp src/thing/player.h
        src/thing/solid.h
        src/thing/solid/crate.cpp src/thing/solid/crate.h
        src/thing/solid/wall.cpp src/thing/solid/wall.h
        src/thing/surface.h
        src/thing/surface/floor.cpp src/thing/surface/floor.h
        src/thing/surface/floor.cpp src/thing/surface/floor.h
        src/thing/surface/gunpowder.cpp src/thing/surface/gunpowder.h
        src/thing/surface/gunpowder.cpp src/thing/surface/gunpowder.h
        src/thing/surface/portal.cpp src/thing/surface/portal.h
        src/thing/surface/portal.cpp src/thing/surface/portal.h
        src/thing/surface/power_up.cpp src/thing/surface/power_up.h
        img/bullet_data.h
        src/scenes/item_life.h
        )

target_link_libraries(${PROJECT_NAME}.elf gba-sprite-engine)

add_custom_command(TARGET ${PROJECT_NAME}.elf POST_BUILD
        COMMAND ${CMAKE_OBJCOPY} -v -O binary ${PROJECT_NAME}.elf ${PROJECT_NAME}.gba
        )
