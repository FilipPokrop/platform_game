cmake_minimum_required( VERSION 3.18)

project(Platform_Game)

set(SFML_STATIC_LIBRARIES TRUE)
find_package(SFML 2.5 COMPONENTS audio graphics window system REQUIRED)

set(SOURCES
    src/main.cpp
    src/Animation.cpp
    src/Duck.cpp
    src/Entity.cpp
    src/Player.cpp
    src/TileMapData.cpp
    src/Collision.cpp
    src/Enemy.cpp
    src/Lives.cpp
    src/TileMap.cpp
    src/World.cpp
    src/State.cpp
    src/StateStack.cpp
    src/GameState.cpp
    src/GameOverState.cpp
    src/MainCharacter.cpp
    src/Slime.cpp
)

set(HEADERS
    include/Animation.h
    include/Duck.h
    include/Entity.h
    include/Player.h
    include/TileMapData.h
    include/Collision.h
    include/Enemy.h
    include/Lives.h
    include/TileMap.h
    include/World.h
    include/ResourceHolder.h
    include/ResourceHolder.inl
    include/ResourceIdentifiers.h
    include/State.h
    include/StateStack.h
    include/StateIdentifiers.h
    include/GameState.h
    include/GameOverState.h
    include/MainCharacter.h
    include/Slime.h
)

add_executable(game ${SOURCES} ${HEADERS})

target_link_libraries(game sfml-graphics sfml-audio sfml-window sfml-system)

include_directories(game
    PUBLIC 
        ${PROJECT_SOURCE_DIR}/include
)