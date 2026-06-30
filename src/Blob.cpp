#include "Blob.h"
#include "picosha2.h"

#include <fstream>
#include <sstream>
#include <filesystem>

namespace fs = std::filesystem;

std::string Blob::createBlob(const std::string& filename)
{
    std::ifstream file(filename,std::ios::binary);

    if(!file)
        return "";

    std::stringstream buffer;
    buffer<<file.rdbuf();

    std::string content=buffer.str();

    std::string hash;

    picosha2::hash256_hex_string(content,hash);

    std::ofstream out(".minigit/objects/"+hash,std::ios::binary);

    out<<content;

    return hash;
}