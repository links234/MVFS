#ifndef MVFS_V1_READER_HPP
#define MVFS_V1_READER_HPP

#include <vector>

#include "MVFSReader.hpp"

namespace MVFS
{
    namespace V1
    {
        class Reader : public MVFS::Reader
        {
        public:
            virtual ~Reader();

        protected:
            Reader(FileReaderInterface *pFileReaderItf, std::vector<char> key);

            friend class MVFS::Reader;
        };
    }
}

#endif
