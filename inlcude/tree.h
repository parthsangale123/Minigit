#ifndef TREE_H
#define TREE_H

#include <string>

class Tree
{
public:
    static std::string createTree();

    static bool restoreTree(const std::string& hash);
};

#endif