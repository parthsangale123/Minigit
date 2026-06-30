#include "Repository.h"
#include "Blob.h"
#include <filesystem>
#include <fstream>
#include <iostream>
#include "Commit.h"
#include "Tree.h"
namespace fs = std::filesystem;
bool Repository::createBranch(const std::string& name)
{
    std::ifstream head(".minigit/HEAD");

    std::string current;

    getline(head,current);

    std::ifstream currentBranch(".minigit/branches/"+current);

    std::string latest;

    getline(currentBranch,latest);

    std::ofstream newBranch(".minigit/branches/"+name);

    newBranch<<latest;

    std::cout<<"Created branch "<<name<<"\n";

    return true;
}
bool Repository::switchBranch(const std::string& name)
{
    if(!fs::exists(".minigit/branches/"+name))
    {
        std::cout<<"Branch not found\n";
        return false;
    }

    std::ofstream head(".minigit/HEAD");

    head<<name;

    std::ifstream branch(".minigit/branches/"+name);

    std::string commit;

    getline(branch,commit);

    if(!commit.empty())
        checkout(commit);

    std::cout<<"Switched to "<<name<<"\n";

    return true;
}
bool Repository::init()
{

    if(fs::exists(".minigit"))
    {
        std::cout<<"Repository already exists.\n";
        return false;
    }

    fs::create_directory(".minigit");
    fs::create_directory(".minigit/objects");
    fs::create_directory(".minigit/commits");
    fs::create_directory(".minigit/branches");
    fs::create_directory(".minigit/trees");
    std::ofstream(".minigit/index");

    std::ofstream head(".minigit/HEAD");
    head<<"main";

    std::ofstream branch(".minigit/branches/main");
    branch<<"";

    std::cout<<"Initialized empty MiniGit repository.\n";

    return true;
}
bool Repository::checkout(const std::string& commitHash)
{
    std::ifstream commit(".minigit/commits/" + commitHash);

    if(!commit)
        return false;

    std::string line;

    while(getline(commit,line))
    {
        if(line.rfind("tree:",0)==0)
        {
            std::string tree=line.substr(5);

            Tree::restoreTree(tree);

            std::cout<<"Checked out "<<commitHash<<"\n";

            return true;
        }
    }

    return false;
}
bool Repository::add(const std::string& filename)
{
    if(!fs::exists(filename))
    {
        std::cout<<"File does not exist.\n";
        return false;
    }

    std::string hash = Blob::createBlob(filename);

    if(hash.empty())
    {
        std::cout<<"Unable to create blob.\n";
        return false;
    }

    std::ofstream index(".minigit/index",std::ios::app);

    index<<filename<<" "<<hash<<"\n";

    std::cout<<"Added "<<filename<<"\n";
    std::cout<<"Hash: "<<hash<<"\n";

    return true;
}

bool Repository::commit(const std::string& message)
{
    std::string hash = Commit::createCommit(message);

    if(hash.empty())
    {
        std::cout<<"Nothing to commit.\n";
        return false;
    }

    std::cout<<"Created commit\n";
    std::cout<<hash<<"\n";

    return true;
}

void Repository::status()
{
    std::ifstream head(".minigit/HEAD");

    std::string branch;

    getline(head,branch);

    std::cout<<"On branch "<<branch<<"\n\n";

    std::ifstream index(".minigit/index");

    std::string file;
    std::string hash;

    bool empty=true;

    std::cout<<"Staged files:\n\n";

    while(index>>file>>hash)
    {
        empty=false;
        std::cout<<file<<"\n";
    }

    if(empty)
        std::cout<<"Nothing staged.\n";
}

void Repository::log()
{
    std::ifstream head(".minigit/HEAD");

    std::string branch;
    getline(head, branch);

    std::ifstream branchFile(".minigit/branches/" + branch);

    std::string current;
    getline(branchFile, current);

    while(!current.empty())
    {
        std::ifstream commit(".minigit/commits/" + current);

        if(!commit)
            break;

        std::cout<<"commit "<<current<<"\n\n";

        std::string line;
        std::string parent;

        while(getline(commit,line))
        {
            if(line.rfind("parent:",0)==0)
                parent=line.substr(7);

            std::cout<<line<<"\n";
        }

        std::cout<<"\n--------------------------\n\n";

        current=parent;
    }
}




