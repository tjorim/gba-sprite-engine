project(RollingStone)

add_executable(${PROJECT_NAME}.elf
        src/main.cpp
        src/Space_Kirby_scene.cpp
        src/Space_Kirby_scene.h
        src/SplashScreen.cpp
        src/SplashScreen.h
        src/SplashBackground.h src/splash_sprites.h src/theme_song.h src/splash_background_test.h src/Space_kirby_sprites.h src/Death_scene.cpp src/Death_scene.h)

target_link_libraries(${PROJECT_NAME}.elf gba-sprite-engine)

add_custom_command(TARGET ${PROJECT_NAME}.elf POST_BUILD
        COMMAND ${CMAKE_OBJCOPY} -v -O binary ${PROJECT_NAME}.elf ${PROJECT_NAME}.gba
        )
