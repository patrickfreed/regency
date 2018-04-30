cmake_minimum_required(VERSION 3.6)
project(regency)

set(CMAKE_CXX_STANDARD 14)

set(NAME regency)

set(SOURCE_FILES
        main.cpp
        Game.cpp
        Game.h
        world/World.cpp
        world/World.h
        world/Tile.cpp
        world/Tile.h
        world/Material.cpp
        world/Material.h
        entity/Entity.cpp
        entity/Entity.h
        entity/Actor.cpp
        entity/Actor.h
        entity/HumanActor.cpp
        entity/HumanActor.h
        entity/misc/Task.cpp
        entity/misc/Task.h
        entity/misc/objectives/Objective.cpp
        entity/misc/objectives/Objective.h
        entity/misc/objectives/NullObjective.cpp
        entity/misc/objectives/NullObjective.h
        entity/misc/tasks/Move.cpp
        entity/misc/tasks/Move.h
        entity/misc/objectives/LocationObjective.cpp
        entity/misc/objectives/LocationObjective.h
        Mouse.cpp
        Mouse.h
        Defines.h
        world/gen/WorldGen.cpp
        world/gen/WorldGen.h
        world/gen/biome/Biome.cpp
        world/gen/biome/Biome.h
        world/gen/biome/GrasslandBiome.cpp
        world/gen/biome/GrasslandBiome.h
        world/gen/biome/WaterBiome.cpp
        world/gen/biome/WaterBiome.h
        world/gen/biome/MountainBiome.cpp
        world/gen/biome/MountainBiome.h
        world/gen/biome/DesertBiome.cpp
        world/gen/biome/DesertBiome.h
        world/gen/RandomGenerator.cpp
        world/gen/RandomGenerator.h
        Assets.cpp
        Assets.h
        world/gen/FlatWorldGen.cpp
        world/gen/FlatWorldGen.h
        world/DisjointSet.cpp
        world/DisjointSet.h
        world/gen/StandardWorldGen.cpp
        world/gen/StandardWorldGen.h world/TileMap.cpp world/TileMap.h world/Location.cpp world/Location.h world/Direction.h world/PathFinder.cpp world/PathFinder.h world/Direction.cpp entity/misc/tasks/Eat.cpp entity/misc/tasks/Eat.h entity/misc/tasks/Find.cpp entity/misc/tasks/Find.h world/Tree.cpp world/Tree.h world/RenderLayer.cpp world/RenderLayer.h)

add_executable(${NAME} ${SOURCE_FILES})

set(CMAKE_MODULE_PATH "/lib/cmake_modules" ${CMAKE_MODULE_PATH})

find_package(SFML 2 REQUIRED system window graphics network audio)
if(SFML_FOUND)
    include_directories(${SFML_INCLUDE_DIR})
    target_link_libraries(${NAME} ${SFML_LIBRARIES})
endif()

include_directories(${NAME} "D:/Program\ Files\ (x86)/libnoise/include/")
target_link_libraries(${NAME} "D:/Program\ Files\ (x86)/libnoise/lib/libnoise.a")