project(GBA_Game)

add_executable(${PROJECT_NAME}.elf
        src/main.cpp src/BG_data.h src/MapData_L1.h src/Level2Scene.cpp src/Level2Scene.h src/Sprite.h src/MapData_L2.h src/DeadScene.cpp src/DeadScene.h src/StartScene.cpp src/StartScene.h src/MetaData.h src/EndScene.cpp src/EndScene.h)

target_link_libraries(${PROJECT_NAME}.elf gba-sprite-engine)

add_custom_command(TARGET ${PROJECT_NAME}.elf POST_BUILD
        COMMAND ${CMAKE_OBJCOPY} -v -O binary ${PROJECT_NAME}.elf ${PROJECT_NAME}.gba
        )
