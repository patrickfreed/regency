#ifndef REGENCY_WORLD_DISJOINTSET_H
#define REGENCY_WORLD_DISJOINTSET_H

#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace regency {
namespace world {

typedef struct entry {
    int id;
    int rank;
    int parent;
} Entry;

class DisjointSet {
  public:
    void make_set(int);

    void union_elements(int, int);

    Entry& find(int);

    bool contains(int);

    int size();

    std::unordered_map<int, std::unordered_set<int>> get_sets();

  private:
    std::unordered_map<int, Entry> _data;
};
}
}

#endif // REGENCY_WORLD_DISJOINTSET_H
