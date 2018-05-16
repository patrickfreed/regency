#include <world/gen/RandomGenerator.h>
#include <iostream>
#include "Faction.h"

namespace regency::entity {

Faction::Faction(std::string name) : _name(std::move(name)), _population(0), _defeater{nullptr} {
    world::gen::RandomGenerator rnd{1, 10};
    _friendly = rnd.next_int() <= 5;
}

std::string Faction::get_name() {
    return _name;
}

bool Faction::friendly() {
    return _friendly;
}

void Faction::add_settlement(std::string name) {
    _settlements.push_back(name);
}

std::vector<std::string>& Faction::get_settlments() {
    return _settlements;
}

void Faction::increase_population() {
    _population += 1;
}

void Faction::decrease_population() {
    _population -= 1;
}

int Faction::get_population() {
    return _population;
}

void Faction::defeat(Faction& defeater) {
    if (get_population() == 0 && !_defeater) {
        _defeater = &defeater;
    }
}

Faction *Faction::get_defeater() {
    return _defeater;
}
}
