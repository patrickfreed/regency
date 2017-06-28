
#ifndef TEST_PROJECT_BIOME_H
#define TEST_PROJECT_BIOME_H

/*
 * Like world gen, I want this to eventually to be read from json like file
 */

#include <string>
#include <unordered_map>
#include <unordered_set>
#include "../../Tile.h"

typedef std::pair<unsigned int, unsigned int> CoordinatePair;
typedef std::pair<CoordinatePair, std::pair<double, double>> TileInfo;
typedef std::vector<struct region *> Cluster;

typedef struct region {
    std::vector<TileInfo> tile_info;
    std::string name;
} Region;

struct pair_hash {
    inline std::size_t operator()(const CoordinatePair & v) const {
        return v.first*31+v.second;
    }
};

class Biome {
private:
    std::string name;
    const std::pair<double, double> e_range;
    const std::pair<double, double> m_range;

    std::vector<std::unique_ptr<Region>> regs;
    std::unordered_map<CoordinatePair, std::pair<double, double>, pair_hash> tile_infos;
public:
    ~Biome();
    virtual const Material *get_tile(double e, double m) = 0;
    std::string& get_name() { return name; }
    const std::pair<double, double> get_elevation_range();
    const std::pair<double, double> get_moisture_range();

    void add_tile(unsigned int x, unsigned int y, double e, double m);
    void generate_regions();
    virtual std::string& get_region_name(Region& r);
    virtual void generate_tiles(std::vector<std::vector<Tile *>>& tiles);
protected:
    Biome(std::string name, double min_e, double max_e, double min_m, double max_m);
    std::unordered_set<Cluster *> regions;
};

#endif //TEST_PROJECT_BIOME_H
