#ifndef REGENCY_REGION_H
#define REGENCY_REGION_H

#include <regency/world/Location.h>
#include <regency/world/Tile.h>

namespace regency::world {

class World;

// Rectangular region
// May support more complex regions (circles, triangles, n-gons) in future.

class Region {
  public:
    Region(Location a = {0, 0}, Location b = {WORLD_SIZE, WORLD_SIZE}, bool checks = false);

    Region(const Region& other) = default;

    Region& operator=(const Region& other);

    Location get_closest_point(Location other);

    bool is_on_border(const Location& l);

    bool intersects(Region& other);

    int get_width();

    int get_height();

    bool is_marked(int x, int y)const;

    bool is_marked(const Tile &t);

    void set_marked(const Tile& t, bool mark);

    void set_marked(int x, int y, bool mark);

    int get_number_marked()const;

    int get_min_x();

    int get_max_x();

    int get_min_y();

    int get_max_y();

    int size();

    bool contains(const Location& loc) const;

    class RegionIterator;

    RegionIterator begin() const;

    RegionIterator end() const;

    friend class RegionIterator;

    class RegionIterator : public std::iterator<std::forward_iterator_tag, world::Tile> {
      public:
        RegionIterator() = default;

        explicit RegionIterator(const Region& region);

        RegionIterator(const RegionIterator& other) = default;

        ~RegionIterator() = default;

        RegionIterator& operator=(const RegionIterator& other) = default;

        bool operator==(const RegionIterator& other) const;

        bool operator!=(const RegionIterator& other) const;

        RegionIterator& operator++();

        Tile& operator*();

      private:
        world::World *_world;

        int _x;
        int _y;

        int _min_x;
        int _max_x;
        int _min_y;
        int _max_y;

        friend class Region;
    };

  private:
    bool _using_marks;
    std::vector<bool> _marks;

    World& _world;
    world::Location _a;
    world::Location _b;

    int _min_x;
    int _min_y;

    int _max_x;
    int _max_y;
};
}

#endif //REGENCY_REGION_H
