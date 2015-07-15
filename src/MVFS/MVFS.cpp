#include "MVFS.hpp"

using namespace std;

namespace MVFS
{
    void Unpack(string pathToArchive, string pathToDir, vector<char> key)
    {
        if(pathToDir=="")
        {
            //TODO
        }

        FileReaderInterface *pFileReaderItf = FileReaderCstdio::Open(pathToArchive.c_str());
        MVFS::Reader *pReader = MVFS::Reader::Open(pFileReaderItf);

        delete pFileReaderItf;
        delete pReader;
    }
}
