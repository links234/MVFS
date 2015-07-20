#include "MVFS_V1_Reader.hpp"

#include "MVFS_V1_Constants.hpp"


/*
if(pathToArchive=="")
{
    pathToArchive=pathToDir+".mvfs";
}
archiveOutput.open(pathToArchive.c_str(),ios::binary);

xorKey=key;
unsigned char xorBit=0;
if(xorKey.size()>0)
{
    xorBit=1;
}
unsigned char version = (THIS_VERSION<<4)|xorBit;

archiveOutput<<version;

PackRec(pathToDir);

archiveOutput.close();


#if defined(LINUX_PLATFORM)
DIR *dp;
struct dirent *dirp;
if((dp  = opendir(pathToDir.c_str())) == NULL)
{
    cout << "Error(" << errno << ") opening " << pathToDir << endl;
    return;
}

while ((dirp = readdir(dp)) != NULL)
{
    string name=string(dirp->d_name);

    if(dirp->d_type==DT_REG)
    {
        archiveOutput<<NEWFILE;
        PackWriteFile(pathToDir+"/"+name);
    }
    else if(dirp->d_type==DT_DIR)
    {
        archiveOutput<<MKDIR;
        archiveOutput.write((const char*)name.c_str(),name.size()+1);
        archiveOutput<<OPENLASTMKDIR;
        PackRec(pathToDir+"/"+name);
        archiveOutput<<BACK;
    }
}
closedir(dp);
#endif
const unsigned char MKDIR=1;
const unsigned char OPENDIR=2;
const unsigned char BACK=3;
const unsigned char NEWFILE=4;
const unsigned char OPENLASTMKDIR=5;
const unsigned char THIS_VERSION=1;

*/
namespace MVFS
{
    namespace V1
    {
        Reader::Reader(FileReaderInterface *pFileReaderItf, std::vector<char> key)
            : MVFS::Reader(pFileReaderItf, key)
        {
            m_pFileReaderItf->Read((char*)&m_version,1);

            Node *cursor = m_pRoot = new Node(this);
            Node *lastMkDir = NULL;

            while(m_pFileReaderItf->GetOffset()<m_pFileReaderItf->Size())
            {
                unsigned char op=0;
                m_pFileReaderItf->Read((char*)&op,1);

                switch(op)
                {
                    case MKDIR:
                    break;
                    case OPENDIR:
                    break;
                    case BACK:
                    break;
                    case NEWFILE:
                    break;
                    case OPENLASTMKDIR:
                    break;
                    default:
                        cout<<"ERROR! Invalid operation!"<<endl;
                    break;
                }
            }
        }

        Reader::~Reader()
        {
        }
    }
}
