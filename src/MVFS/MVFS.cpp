#include "MVFS.hpp"

#ifdef LINUX_PLATFORM
    #include <sys/types.h>
    #include <sys/stat.h>
    #include <unistd.h>
#endif

using namespace std;

namespace MVFS
{

    void MakeDir(string pathToDir)
    {
#ifdef LINUX_PLATFORM
        struct stat st = {0};

        if (stat("/some/directory", &st) == -1) {
            mkdir("/some/directory", 0700);
        }
#endif
    }

    void UnpackFile(Node *node, string pathToFile)
    {
        cout<<"File: "<<pathToFile<<"  size = "<<node->GetFileSize()<<"   offset = "<<node->GetFileOffset()<<endl;
    }

    void UnpackRec(Node *node, string pathToDir)
    {
        for(unordered_map<string,Node*>::iterator it=node->GetDirectories().begin();it!=node->GetDirectories().end();++it)
        {
            MakeDir(pathToDir);
            string dirName=pathToDir+"/"+it->first;
            UnpackRec(it->second,dirName);
        }
        for(unordered_map<string,Node*>::iterator it=node->GetFiles().begin();it!=node->GetFiles().end();++it)
        {
            string fileName=pathToDir+"/"+it->first;
            UnpackFile(it->second,fileName);
        }
    }

    void Unpack(string pathToArchive, string pathToDir, vector<char> key)
    {
        if(pathToDir=="")
        {
            //TODO
        }

        FileReaderInterface *pFileReaderItf = FileReaderCstdio::Open(pathToArchive.c_str());
        MVFS::Reader *pReader = MVFS::Reader::Open(pFileReaderItf,key);

        UnpackRec(pReader->GetRoot(),pathToDir);

        delete pFileReaderItf;
        delete pReader;
    }
}
