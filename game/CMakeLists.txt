project(game)

add_executable(${PROJECT_NAME}.elf
        src/main.cpp
        src/StartScene.cpp
        src/StartScene.h
        src/Background_1.h src/BattleScene_EyeMonster.cpp src/BattleScene_EyeMonster.h src/Adventurer.cpp src/Adventurer.h src/Sprites_Palette.h src/EyeballMonster.cpp src/EyeballMonster.h src/DeathScene.cpp src/DeathScene.h src/Ghost.cpp src/Ghost.h src/skeleton_sprite.h src/BattleScene_Ghost.cpp src/BattleScene_Ghost.h src/Scene_2.h src/Victory_Scene.cpp src/Victory_Scene.h src/victory_data.h src/Victory.cpp src/Victory.h src/Chalice.cpp src/Chalice.h)


target_link_libraries(${PROJECT_NAME}.elf gba-sprite-engine)

add_custom_command(TARGET ${PROJECT_NAME}.elf POST_BUILD
        COMMAND ${CMAKE_OBJCOPY} -v -O binary ${PROJECT_NAME}.elf ${PROJECT_NAME}.gba
        )