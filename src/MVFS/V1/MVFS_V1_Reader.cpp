#include "MVFS_V1_Reader.hpp"

#include "MVFS_V1_Constants.hpp"

namespace MVFS
{
    namespace V1
    {
        Reader::Reader(FileReaderInterface *pFileReaderItf)
            : MVFS::Reader(pFileReaderItf)
        {
        }

        Reader::~Reader()
        {
        }
    }
}
