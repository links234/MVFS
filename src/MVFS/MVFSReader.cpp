#include "MVFSReader.hpp"

#include <cstddef>

#include "MVFS_V1_Reader.hpp"

#include <cstdio>

namespace MVFS
{
    Reader::Reader(FileReaderInterface *pFileReaderItf, std::vector<char> key)
        : m_pFileReaderItf(pFileReaderItf), m_version(0), m_key(key)
    {
    }

    Reader::~Reader()
    {
        delete m_pRoot;
    }

    Reader* Reader::Open(FileReaderInterface *pFileReaderItf, std::vector<char> key)
    {
        unsigned char version = ReadVersion(pFileReaderItf);

        printf("Reader::Open version = %d\n", version);

        if(version == 1)
        {
            pFileReaderItf->Reset();
            return new V1::Reader(pFileReaderItf,key);
        }
        //SHOULD PRINT ERROR HERE!!
        return NULL;
    }

    unsigned char Reader::ReadVersion(FileReaderInterface *pFileReaderItf)
    {
        unsigned char version = 0;
        pFileReaderItf->ReadFrom(0,(char*)(&version),1);
        return (version>>4);
    }

    unsigned char Reader::GetVersion()
    {
        return m_version;
    }
}
