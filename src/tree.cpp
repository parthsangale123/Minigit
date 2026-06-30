#include "Tree.h"
#include "picosha2.h"

#include <fstream>
#include <sstream>
#include <filesystem>

namespace fs = std::filesystem;

std::string Tree::createTree()
{
    std::ifstream index(".minigit/index");

    if(!index)
        return "";

    std::stringstream buffer;
    buffer << index.rdbuf();

    std::string data = buffer.str();

    std::string hash;
    picosha2::hash256_hex_string(data, hash);

    std::ofstream out(".minigit/trees/" + hash);
    out << data;

    return hash;
}
bool Tree::restoreTree(const std::string& hash)
{
    std::ifstream tree(".minigit/trees/" + hash);

    if(!tree)
        return false;

    std::string filename, blobHash;

    while(tree >> filename >> blobHash)
    {
        std::ifstream blob(".minigit/objects/" + blobHash,
                           std::ios::binary);

        std::ofstream out(filename,
                          std::ios::binary);

        out << blob.rdbuf();
    }

    return true;
}