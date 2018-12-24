project(GBA_Game)

add_executable(${PROJECT_NAME}.elf
        src/main.cpp src/background.h src/Bg.h src/Bg_edited_tileset.h src/Player.h src/MapData.h)

target_link_libraries(${PROJECT_NAME}.elf gba-sprite-engine)

add_custom_command(TARGET ${PROJECT_NAME}.elf POST_BUILD
        COMMAND ${CMAKE_OBJCOPY} -v -O binary ${PROJECT_NAME}.elf ${PROJECT_NAME}.gba
        )
