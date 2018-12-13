project(portal_2.5)

add_executable(${PROJECT_NAME}.elf
        src/main.cpp
        src/Level1_background.h
        src/Level1_scene.cpp
        src/Level1_scene.h "src/Scene_sprites.h" src/Portal_physics.cpp src/Portal_physics.h src/Red_bullet.cpp src/Red_bullet.h)

target_link_libraries(${PROJECT_NAME}.elf gba-sprite-engine)

add_custom_command(TARGET ${PROJECT_NAME}.elf POST_BUILD
        COMMAND ${CMAKE_OBJCOPY} -v -O binary ${PROJECT_NAME}.elf ${PROJECT_NAME}.gba
        )
