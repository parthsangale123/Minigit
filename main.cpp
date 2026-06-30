#include "Repository.h"

#include <iostream>

int main(int argc,char* argv[])
{
    Repository repo;

    if(argc<2)
    {
        std::cout<<"MiniGit\n";
        std::cout<<"Commands:\n";
        std::cout<<"  init\n";
        std::cout<<"  add <file>\n";
        std::cout<<"  commit <message>\n";
        std::cout<<"  status\n";
        std::cout<<"  log\n";
        std::cout<<"  checkout <hash>\n";
        std::cout<<"  branch <name>\n";
        std::cout<<"  switch <name>\n";
        return 0;
    }

    std::string cmd=argv[1];

    if(cmd=="init")
    {
        repo.init();
    }

    else if(cmd=="add" && argc>=3)
    {
        repo.add(argv[2]);
    }

    else if(cmd=="commit" && argc>=3)
    {
        repo.commit(argv[2]);
    }

    else if(cmd=="status")
    {
        repo.status();
    }

    else if(cmd=="log")
    {
        repo.log();
    }

    else if(cmd=="checkout" && argc>=3)
    {
        repo.checkout(argv[2]);
    }

    else if(cmd=="branch" && argc>=3)
    {
        repo.createBranch(argv[2]);
    }

    else if(cmd=="switch" && argc>=3)
    {
        repo.switchBranch(argv[2]);
    }

    else
    {
        std::cout<<"Unknown command.\n";
    }

    return 0;
}