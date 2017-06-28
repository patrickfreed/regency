
#ifndef TEST_PROJECT_DISJOINTSET_H
#define TEST_PROJECT_DISJOINTSET_H

#include <unordered_map>
#include <unordered_set>
#include <vector>

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

    std::unordered_map<int, std::unordered_set<int>> get_sets();
private:
    std::unordered_map<int, Entry> _data;
};

#endif //TEST_PROJECT_DISJOINTSET_H
