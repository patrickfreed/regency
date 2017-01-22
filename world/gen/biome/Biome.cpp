
#include <sstream>
#include <iostream>
#include "Biome.h"
#include "../../../Defines.h"

Biome::Biome(string name, double min_e, double max_e, double min_m, double max_m) : e_range(min_e, max_e), m_range(min_m, max_m) {
    this->name = name;
}

const pair<double, double> Biome::get_elevation_range() {
    return this->e_range;
}

const pair<double, double> Biome::get_moisture_range() {
    return this->m_range;
}

/*void add_tile(unsigned int x, unsigned int y, double e, double m) {
    unsigned int start_x = x ? x - 1 : x;

    TileInfo t_info(pair<unsigned int, unsigned int>(x, y), pair<double,double>(e, m));

    ostringstream now_coords;
    now_coords << x << "," << y;
    unordered_set<Region *> neighboring_regions;
    unordered_set<Cluster *> neighboring_clusters;

    /*if (y) {
        for (int xc = start_x; xc < x + 2; xc++) {
            ostringstream coords;
            coords << xc << "," << y - 1;

            if (this->coord_to_region.count(coords.str())) {
                Region *i = this->coord_to_region[coords.str()];

                if (!neighboring_clusters.count(i->parent)) {
                    neighboring_regions.insert(i);
                    neighboring_clusters.insert(i->parent);
                }
            }
        }
    }

    if (x) {
        ostringstream coords;
        coords << x - 1 << "," << y;

        if (this->coord_to_region.count(coords.str())) {
            Region *i = this->coord_to_region[coords.str()];
            neighboring_regions.insert(i);
        }
    }

    if (false && neighboring_regions.size() > 1) {
        Cluster *a = new Cluster;
        regions.insert(a);
        unordered_set<Cluster *> clusters_to_free;

        for (auto it = neighboring_regions.begin(); it != neighboring_regions.end(); ++it) {
            clusters_to_free.insert((*it)->parent);
            (*it)->parent = a;
        }

        for (auto c_it = clusters_to_free.begin(); c_it != clusters_to_free.end(); ++c_it) {
            Cluster *cluster = *c_it;
            for (auto it = cluster->begin(); it != cluster->end(); ++it) {
                Region *r = *it;
                r->parent = a;
                a->push_back(r);
            }
            regions.erase(*c_it);
            delete *c_it;
        }

        Region *r = new Region;
        r->parent = a;
        r->tile_info.push_back(t_info);
        a->push_back(r);
        this->coord_to_region[now_coords.str()] = r;
    } else if (false && neighboring_regions.size() >= 1) {
        Region *region = *(neighboring_regions.begin());
        region->tile_info.push_back(t_info);
        this->coord_to_region[now_coords.str()] = region;
    } else if (false) {
        Region *next_region = new Region;
        Cluster *next_cluster = new Cluster;
        next_region->tile_info.push_back(t_info);
        next_region->parent = next_cluster;
        next_cluster->push_back(next_region);
        this->regions.insert(next_cluster);
        this->coord_to_region[now_coords.str()] = next_region;
    } else {
        if (this->regions.size() == 0) {
            Region *next_region = new Region;
            Cluster *next_cluster = new Cluster;
            next_region->tile_info.push_back(t_info);
            next_region->parent = next_cluster;
            next_cluster->push_back(next_region);
            this->regions.insert(next_cluster);
            this->coord_to_region[now_coords.str()] = next_region;
        } else {
            ((*(this->regions.begin()))[0])[0]->tile_info.push_back(t_info);
        }
    }
}*/

void Biome::add_tile(unsigned int x, unsigned int y, double e, double m) {
    ostringstream oss;
    oss << x << "," << y;

    this->tile_infos[oss.str()] = make_pair(e, m);
}

void Biome::generate_regions(vector<vector<Tile *>> &tiles) {
    unordered_set<string> coords;

    for (auto it = this->tile_infos.begin(); it != this->tile_infos.end(); ++it) {
        string coord = it->first;
        coords.insert(coord);
    }

    vector<vector<TileInfo>> regs;
    while (coords.size()) {
        vector<TileInfo> region;
        string root = *coords.begin();
        unordered_set<string> to_check;

        to_check.insert(root);
        coords.erase(root);

        while (to_check.size()) {
            string next = *(to_check.begin());

            stringstream iss;
            char comma;
            int x;
            int y;

            iss << next;
            iss >> x >> comma >> y;

            to_check.erase(next);
            region.push_back(make_pair(make_pair(x, y), tile_infos[next]));

            for (int xx = max(x - 1, 0); xx <= min(x + 1, WORLD_SIZE); xx++) {
                for (int yy = max(y - 1, 0); yy <= min(y + 1, WORLD_SIZE); yy++) {
                    if (xx == x && yy == y) continue;
                    ostringstream oss;
                    oss << xx << "," << yy;

                    if (coords.count(oss.str())) {
                        to_check.insert(oss.str());
                        coords.erase(oss.str());
                    }
                }
            }
        }
        regs.push_back(region);
    }

    int c = 0;

    for (auto it = regs.begin(); it != regs.end(); ++it) {
        //Cluster *cluster = *it;
        vector<TileInfo> region = *it;
        c++;

       // for (auto c_it = cluster->begin(); c_it != cluster->end(); ++c_it) {
            //Region *r = *c_it;
            for (int t = 0; t < region.size(); t++) {
                ostringstream r_name;

                TileInfo t_info = region[t];

                unsigned int x = t_info.first.first;
                unsigned int y = t_info.first.second;

                double e = t_info.second.first;
                double m = t_info.second.second;

                r_name << this->get_name() << " " << c;

                tiles[x][y] = new Tile(x, y, this->get_tile(e, m), r_name.str());
            }
       //}
    }
}

Biome::~Biome() {
    for (auto it = this->regions.begin(); it != regions.end(); ++it) {
        for (auto r = (*it)->begin(); r != (*it)->end(); ++r) {
            delete (*r);
        }
        delete (*it);
    }
}
