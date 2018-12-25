project(portal_2.5)

add_executable(${PROJECT_NAME}.elf
        src/main.cpp
        src/StartScene.cpp
        src/Level1_background.h
        src/LevelScene.cpp
        src/LevelScene.h "src/Scene_sprites.h" src/Portal_bullet.cpp src/Portal_bullet.h src/Portal_gun_sound.h src/StartScene.cpp src/StartScene.h src/Chell.cpp src/Chell.h src/Level.cpp src/Level.h src/WallTile.cpp src/WallTile.h src/Portal.cpp src/Portal.h src/Visier.cpp src/Visier.h src/GameOverScene.cpp src/GameOverScene.h src/Button.cpp src/Button.h src/PortalMusic.h)

target_link_libraries(${PROJECT_NAME}.elf gba-sprite-engine)

add_custom_command(TARGET ${PROJECT_NAME}.elf POST_BUILD
        COMMAND ${CMAKE_OBJCOPY} -v -O binary ${PROJECT_NAME}.elf ${PROJECT_NAME}.gba
        )
