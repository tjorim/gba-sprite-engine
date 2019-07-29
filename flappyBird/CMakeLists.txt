project(flappyBird)

add_executable(${PROJECT_NAME}.elf
        src/main.cpp
        src/MainScene.cpp src/MainScene.h
        src/achtergrondWolkjes.h
        src/bird1.h
        src/flappybird.h
        src/StartScene.cpp
        src/StartScene.h
        src/flappybirdachtergrond.h
        src/startschermachtergrondFB.h src/birdstartscherm.h)

target_link_libraries(${PROJECT_NAME}.elf gba-sprite-engine)

add_custom_command(TARGET ${PROJECT_NAME}.elf POST_BUILD
        COMMAND ${CMAKE_OBJCOPY} -v -O binary ${PROJECT_NAME}.elf ${PROJECT_NAME}.gba
        )
