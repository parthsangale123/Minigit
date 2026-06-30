#ifndef REPOSITORY_H
#define REPOSITORY_H

#include <string>

class Repository
{
public:

    bool init();

    bool add(const std::string& filename);

    bool commit(const std::string& message);

    void status();

    void log();

    bool checkout(const std::string& hash);

    bool createBranch(const std::string& name);

    bool switchBranch(const std::string& name);

};

#endif