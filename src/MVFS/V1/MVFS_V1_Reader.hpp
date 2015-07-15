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
            virtual ~Reader();

        protected:
            Reader(FileReaderInterface *pFileReaderItf);

            friend class MVFS::Reader;
        };
    }
}

#endif
