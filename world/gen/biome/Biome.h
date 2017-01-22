
#ifndef TEST_PROJECT_BIOME_H
#define TEST_PROJECT_BIOME_H

/*
 * Like world gen, I want this to eventually to be read from json like file
 */

#include <string>
#include <unordered_map>
#include <unordered_set>
#include "../../Tile.h"

using namespace std;

typedef pair<pair<unsigned int, unsigned int>, pair<double, double>> TileInfo;
typedef vector<struct region *> Cluster;
typedef struct region {
    vector<TileInfo> tile_info;
    Cluster *parent;
} Region;

class Biome {
private:
    string name;
    const pair<double, double> e_range;
    const pair<double, double> m_range;

    unordered_map<string, Region *> coord_to_region;
    unordered_map<string, pair<double, double>> tile_infos;
public:
    ~Biome();
    virtual const Material *get_tile(double e, double m) = 0;
    string& get_name() { return name; }
    const pair<double, double> get_elevation_range();
    const pair<double, double> get_moisture_range();

    void add_tile(unsigned int x, unsigned int y, double e, double m);
    virtual void generate_regions(vector<vector<Tile *>>& tiles);
protected:
    Biome(string name, double min_e, double max_e, double min_m, double max_m);
    unordered_set<Cluster *> regions;
};

#endif //TEST_PROJECT_BIOME_H
