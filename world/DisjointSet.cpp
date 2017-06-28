
#include "DisjointSet.h"

void DisjointSet::make_set(int id) {
    Entry new_entry;

    new_entry.id = id;
    new_entry.rank = 1;
    new_entry.parent = id;

    _data[id] = new_entry;
}

void DisjointSet::union_elements(int x, int y) {
    Entry& x_root = find(x);
    Entry& y_root = find(y);

    if (x_root.id == y_root.id) {
        return;
    }

    if (x_root.rank < y_root.rank) {
        x_root.parent = y_root.id;
    } else if (x_root.rank > y_root.rank) {
        y_root.parent = x_root.id;
    } else {
        y_root.parent = x_root.id;
        x_root.rank++;
    }
}

Entry& DisjointSet::find(int x) {
    Entry& x_entry = _data[x];

    if (x_entry.parent != x) {
        x_entry.parent = find(x_entry.parent).id;
    }

    return _data[x_entry.parent];
}

std::unordered_map<int, std::unordered_set<int>> DisjointSet::get_sets() {
    std::vector<std::unordered_set<int>> sets;
    std::unordered_map<int, std::unordered_set<int>> mapped_sets;

    for (auto i : _data) {
        mapped_sets[find(i.first).id].insert(i.first);
    }

    //for (auto i : mapped_sets) {
    //    sets.push_back(i.second);
    //}

    return std::move(mapped_sets);
}
