project(bomberboy)

add_executable(${PROJECT_NAME}.elf
        src/end_scene.cpp src/end_scene.h
        src/game_scene.cpp src/game_scene.h
        src/main.cpp src/sound.h
        src/start_scene.cpp src/start_scene.h
        src/thing.h
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
        )

target_link_libraries(${PROJECT_NAME}.elf gba-sprite-engine)

add_custom_command(TARGET ${PROJECT_NAME}.elf POST_BUILD
        COMMAND ${CMAKE_OBJCOPY} -v -O binary ${PROJECT_NAME}.elf ${PROJECT_NAME}.gba
        )
