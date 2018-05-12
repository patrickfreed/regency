cmake_minimum_required(VERSION 3.6)
project(regency)

set(CMAKE_CXX_STANDARD 17)

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
        entity/action/Action.cpp
        entity/action/Action.h
        entity/action/objectives/Objective.cpp
        entity/action/objectives/Objective.h
        entity/action/objectives/NullObjective.cpp
        entity/action/objectives/NullObjective.h
        entity/action/Move.cpp
        entity/action/Move.h
        entity/action/objectives/LocationObjective.cpp
        entity/action/objectives/LocationObjective.h
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
        world/util/DisjointSet.cpp
        world/util/DisjointSet.h
        world/gen/StandardWorldGen.cpp
        world/gen/StandardWorldGen.h
        world/util/TileMap.cpp
        world/util/TileMap.h
        world/Location.cpp
        world/Location.h
        world/Direction.h
        world/util/PathFinder.cpp
        world/util/PathFinder.h
        world/Direction.cpp
        entity/action/Eat.cpp
        entity/action/Eat.h
        entity/action/Find.cpp
        entity/action/Find.h
        world/Tree.cpp world/Tree.h
        world/util/RenderLayer.cpp
        world/util/RenderLayer.h
        world/gen/fastnoise/FastNoise.cpp
        world/gen/fastnoise/FastNoise.h
        item/Inventory.cpp
        item/Inventory.h
        item/Item.cpp
        item/Item.h
        entity/action/Harvest.cpp
        entity/action/Harvest.h
        world/Region.cpp world/Region.h entity/action/Patrol.cpp entity/action/Patrol.h entity/action/Follow.cpp entity/action/Follow.h entity/action/Idle.cpp entity/action/Idle.h entity/DamageSprite.cpp entity/DamageSprite.h)

add_executable(${NAME} ${SOURCE_FILES})

set(CMAKE_MODULE_PATH "/lib/cmake_modules" ${CMAKE_MODULE_PATH})

find_package(SFML 2 REQUIRED system window graphics network audio)
if(SFML_FOUND)
    include_directories(${SFML_INCLUDE_DIR})
    target_link_libraries(${NAME} ${SFML_LIBRARIES})
endif()

include_directories(${NAME} "D:/Program\ Files\ (x86)/libnoise/include/")
target_link_libraries(${NAME} "D:/Program\ Files\ (x86)/libnoise/lib/libnoise.a")

include_directories(".")
include_directories("..")