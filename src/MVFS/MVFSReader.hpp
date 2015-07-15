#ifndef MVFSREADER_HPP
#define MVFSREADER_HPP

#include "FileReaderInterface.hpp"

namespace MVFS
{
    class Reader
    {
    public:
        virtual ~Reader();

        static Reader* Open(FileReaderInterface *pReaderItf);

        unsigned char GetVersion();

    protected:
        Reader(FileReaderInterface *pReaderItf);

        static unsigned char ReadVersion(FileReaderInterface *pReaderItf);

        FileReaderInterface *m_pReaderItf;

        unsigned char m_version;
    };
}

#endif
