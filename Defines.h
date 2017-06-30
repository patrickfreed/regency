
#ifndef TEST_PROJECT_DEFINES_H
#define TEST_PROJECT_DEFINES_H

// Maybe a class in future
typedef std::vector<std::vector<std::unique_ptr<Tile>>> TileMap;

// Maybe a class in future
typedef struct mat_def {
    const Material *material;
    std::pair<double, double> e_range;
    std::pair<double, double> m_range;
} MaterialDefinition;

#define WORLD_SIZE 1000
#define DUP_FACTOR 1

#define OCEAN_SIZE 25000
#define LAKE_SIZE 2500
#define CONTINENT_SIZE 10000
#define DEFAULT_WATER_LEVEL 0.4

#define RENDER_SIZE 100
#define WINDOW_SIZE 1000

#endif //TEST_PROJECT_DEFINES_H
