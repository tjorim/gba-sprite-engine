project(Apple_A_Day)

add_executable(${PROJECT_NAME}.elf
        src/main.cpp
        src/StartScene.cpp src/StartScene.h
        src/background1.h src/background1.cpp
        # src/linkUpWalk.h
        src/levelSound.h src/sign.h src/linkAnimation.h src/Direction.h src/shared.h src/type.cpp src/type.h src/mapMatrix.h
        src/CityScene.cpp src/CityScene.h
        src/levelControl.h
        src/background2.cpp src/background2.h
        src/apple.h src/sharedPalette.h src/windowBullet.h src/enemy.h)

target_link_libraries(${PROJECT_NAME}.elf gba-sprite-engine)

add_custom_command(TARGET ${PROJECT_NAME}.elf POST_BUILD
        COMMAND ${CMAKE_OBJCOPY} -v -O binary ${PROJECT_NAME}.elf ${PROJECT_NAME}.gba
        )
