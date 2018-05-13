
#ifndef REGENCY_FACTION_H
#define REGENCY_FACTION_H

#include <string>
#include <vector>

namespace regency::entity {

class Faction {
  public:
    explicit Faction(std::string name);

    std::string get_name();

    bool friendly();

    void add_settlement(std::string name);

    std::vector<std::string>& get_settlments();

    void increase_population();

    void decrease_population();

    int get_population();

  private:
    int _population;

    std::string _name;

    std::vector<std::string> _settlements;

    bool _friendly;
};

}

#endif //REGENCY_FACTION_H
