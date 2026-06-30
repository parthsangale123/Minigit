#include "Commit.h"
#include "picosha2.h"

#include <filesystem>
#include <fstream>
#include <sstream>
#include <chrono>
#include <ctime>
#include "Tree.h"   


namespace fs = std::filesystem;

std::string Commit::createCommit(const std::string& message)
{
    std::string treeHash = Tree::createTree();

    if(treeHash.empty())
        return "";

    // Read current branch
    std::ifstream head(".minigit/HEAD");
    std::string branch;
    getline(head, branch);

    // Read latest commit
    std::ifstream branchFile(".minigit/branches/" + branch);
    std::string parent;
    getline(branchFile, parent);

    // Timestamp
    auto now = std::chrono::system_clock::now();
    std::time_t t = std::chrono::system_clock::to_time_t(now);

    std::stringstream commitData;

    commitData << "parent " << parent << "\n";
    commitData << "time " << std::ctime(&t);
    commitData << "message " << message << "\n";
    commitData << "tree:" << treeHash << "\n";

    std::string hash;
    picosha2::hash256_hex_string(commitData.str(), hash);

    // Save commit object
    std::ofstream out(".minigit/commits/" + hash);
    out << commitData.str();

    // Update branch pointer
    std::ofstream updateBranch(".minigit/branches/" + branch);
    updateBranch << hash;

    // Clear staging area
    std::ofstream clear(".minigit/index");

    return hash;
}