#ifndef REGENCY_TREE_H
#define REGENCY_TREE_H

namespace regency {
namespace world {

enum class TreeType {
    NONE,
    SPRUCE,
    ELM,
    EVERGREEN
};

class Tree {
  private:
    TreeType _type;
    int _height;

  public:
    Tree(TreeType type, int height);

    int get_height();
    TreeType get_type();
};

}
}
#endif //REGENCY_TREE_H
