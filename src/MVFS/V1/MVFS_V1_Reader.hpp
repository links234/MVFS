#ifndef MVFS_V1_READER_HPP
#define MVFS_V1_READER_HPP

#include "MVFSReader.hpp"

namespace MVFS
{
    namespace V1
    {
        class Reader : public MVFS::Reader
        {
        public:

        protected:
            Reader(FileReaderInterface *pFileReaderItf);
            virtual ~Reader();

            friend class MVFS::Reader;
        };
    }
}

#endif
