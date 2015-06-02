#ifndef MVFS_V1_HPP
#define MVFS_V1_HPP

#include <sys/types.h>
#include <dirent.h>
#include <errno.h>
#include <vector>
#include <string>
#include <fstream>
#include <iostream>

namespace MVFS
{
    namespace V1
    {
        void Pack (std::string pathToDir, std::string pathToArchive="", std::vector<char> key=std::vector<char>());
        void Unpack(std::string pathToArchive, std::string pathToDir="", std::vector<char> key=std::vector<char>());
    }
}

#endif
