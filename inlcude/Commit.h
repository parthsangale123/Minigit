#ifndef COMMIT_H
#define COMMIT_H

#include <string>

class Commit
{
public:
    static std::string createCommit(const std::string& message);
};

#endif