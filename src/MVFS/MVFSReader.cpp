#include "MVFSReader.hpp"

#include <cstddef>

#include "MVFS_V1_Reader.hpp"

#include <cstdio>

namespace MVFS
{
    Reader::Reader(FileReaderInterface *pReaderItf)
        : m_pReaderItf(pReaderItf), m_version(0)
    {
    }

    Reader::~Reader()
    {
    }

    Reader* Reader::Open(FileReaderInterface *pReaderItf)
    {
        unsigned char version = ReadVersion(pReaderItf);

        printf("Reader::Open version = %d\n", version);

        if(version == 1)
        {
            pReaderItf->Reset();
            return new V1::Reader(pReaderItf);
        }
        //SHOULD PRINT ERROR HERE!!
        return NULL;
    }

    unsigned char Reader::ReadVersion(FileReaderInterface *pReaderItf)
    {
        unsigned char version = 0;
        pReaderItf->ReadFrom(0,(char*)(&version),1);
        return (version>>4);
    }

    unsigned char Reader::GetVersion()
    {
        return m_version;
    }
}
