project(portal_2.5)

add_executable(${PROJECT_NAME}.elf
        src/main.cpp
        src/Level1_background.h
        src/Level_scene.cpp
        src/Level_scene.h "src/Scene_sprites.h" src/Portal_bullet.cpp src/Portal_bullet.h src/Portal_music.h src/Portal_gun_sound.h src/Start_scene.cpp src/Start_scene.h)

target_link_libraries(${PROJECT_NAME}.elf gba-sprite-engine)

add_custom_command(TARGET ${PROJECT_NAME}.elf POST_BUILD
        COMMAND ${CMAKE_OBJCOPY} -v -O binary ${PROJECT_NAME}.elf ${PROJECT_NAME}.gba
        )
