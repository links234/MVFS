#include "MVFS.hpp"

#ifdef LINUX_PLATFORM
    #include <stdlib.h>
#endif

using namespace std;

namespace MVFS
{

    void MakeDir(string pathToDir)
    {
        cout<<"DIR: "<<pathToDir<<endl;
#ifdef LINUX_PLATFORM
        system( (string("mkdir -p ")+pathToDir).c_str() );
#endif
    }

    void UnpackFile(Node *node, string pathToFile)
    {
        cout<<"File: "<<pathToFile<<"  size = "<<node->GetFileSize()<<"   offset = "<<node->GetFileOffset()<<endl;
    }

    void UnpackDir(Node *node, string pathToDir)
    {
        MakeDir(pathToDir);
        for(unordered_map<string,Node*>::iterator it=node->GetDirectories().begin();it!=node->GetDirectories().end();++it)
        {
            string dirName=pathToDir+"/"+it->first;
            UnpackDir(it->second,dirName);
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

        UnpackDir(pReader->GetRoot(),pathToDir);

        delete pFileReaderItf;
        delete pReader;
    }
}
