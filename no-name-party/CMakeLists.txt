project(no-name-party)               # Create project "no-name-party"

add_executable(${PROJECT_NAME}.elf
        src/main.cpp
        src/book_scene/book_scene.cpp src/book_scene/book_scene.h
        src/book_scene/book.h
        src/book_scene/stair_case.cpp src/book_scene/stair_case.h
        src/dino_scene/dino_scene.cpp src/dino_scene/dino_scene.h
        src/dino_scene/dino.h
        src/end_scene/end_scene.cpp src/end_scene/end_scene.h
        src/enums/character.h src/enums/colour.h
        src/enums/direction.h src/enums/result.h
        src/game_scene/game_scene.cpp src/game_scene/game_scene.h
        src/game_scene/game_result.h
        src/game_scene/player.cpp src/game_scene/player.h
        src/profile_scene/profile_scene.cpp src/profile_scene/profile_scene.h
        src/race_scene/race_scene.cpp src/race_scene/race_scene.h
        src/race_scene/car.h
        src/select_scene/select_scene.cpp src/select_scene/select_scene.h
        src/simon_scene/simon_scene.cpp src/simon_scene/simon_scene.h
        src/start_scene/start_scene.cpp src/start_scene/start_scene.h
        src/start_scene/balloon.h src/start_scene/cloud.h
        src/start_scene/press_start.h src/start_scene/title.h)

target_link_libraries(${PROJECT_NAME}.elf gba-sprite-engine)

add_custom_command(TARGET ${PROJECT_NAME}.elf POST_BUILD
        COMMAND ${CMAKE_OBJCOPY} -v -O binary ${PROJECT_NAME}.elf ${PROJECT_NAME}.gba
        )
