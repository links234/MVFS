#ifndef MVFS_HPP
#define MVFS_HPP

#include "MVFSNode.hpp"
#include "MVFSReader.hpp"

#include "MVFS_V1.hpp"
#include "MVFS_V1_Reader.hpp"
#include "MVFS_V1_Constants.hpp"

#include "FileReaderInterface.hpp"
#include "FileReaderCstdio.hpp"

namespace MVFS
{
    void Unpack(std::string pathToArchive, std::string pathToDir="", std::vector<char> key=std::vector<char>());
}

#endif
