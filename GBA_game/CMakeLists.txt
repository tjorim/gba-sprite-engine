project(GBA_game)

add_executable(${PROJECT_NAME}.elf
        src/main.cpp src/StartScene.cpp src/StartScene.h src/background.h src/background.cpp src/linkUpWalk.h src/linkWalkSide.h src/levelSound.h src/linkDownWalk.h src/sign.h src/linkAnimation.h src/Direction.h src/shared.h src/type.cpp src/type.h src/mapMatrix.h)

target_link_libraries(${PROJECT_NAME}.elf gba-sprite-engine)

add_custom_command(TARGET ${PROJECT_NAME}.elf POST_BUILD
        COMMAND ${CMAKE_OBJCOPY} -v -O binary ${PROJECT_NAME}.elf ${PROJECT_NAME}.gba
        )
