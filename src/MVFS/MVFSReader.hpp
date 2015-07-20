#ifndef MVFSREADER_HPP
#define MVFSREADER_HPP

#include <vector>

#include "FileReaderInterface.hpp"
#include "MVFSNode.hpp"

namespace MVFS
{
    class Reader
    {
    public:
        virtual ~Reader();

        static Reader* Open(FileReaderInterface *pFileReaderItf, std::vector<char> key);

        unsigned char GetVersion();

        Node* GetRoot();

    protected:
        Reader(FileReaderInterface *pReaderItf, std::vector<char> key);

        static unsigned char ReadVersion(FileReaderInterface *pFileReaderItf);

        FileReaderInterface *m_pFileReaderItf;
        Node *m_pRoot;
        unsigned char m_version;
        std::vector<char> m_key;
    };
}

#endif
