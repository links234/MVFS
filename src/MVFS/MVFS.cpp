#include "MVFS.hpp"

#include <fstream>

#ifdef LINUX_PLATFORM
    #include <stdlib.h>
#endif

#include "MVFSGlobal.hpp"

using namespace std;

namespace MVFS
{
    void MakeDir(string pathToDir)
    {
#ifdef LINUX_PLATFORM
        system( (string("mkdir -p ")+pathToDir).c_str() );
#endif
    }

    void UnpackFile(Node *node, string pathToFile)
    {
        if(Global::verbose)
        {
            cout<<"Unpacking file: \""<<pathToFile<<"\" with size = "<<node->GetFileSize()<<" bytes"<<endl;
        }

        FileReaderInterface *file=node->Open();
        int size=file->Size();

        char *buffer=new char[size];
        file->Read(buffer,size);
        delete file;

        ofstream fileOutput;
        fileOutput.open(pathToFile.c_str(),ios::binary);
        fileOutput.write(buffer,size);
        fileOutput.close();

        delete[] buffer;
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
            int index=pathToArchive.size()-1;
            for(;pathToArchive[index]!='.' && index>0;--index);
            if(index==0)
            {
                pathToDir=pathToArchive+"_unpacked";
            }
            else
            {
                for(int i=0;i<index;++i)
                {
                    pathToDir+=pathToArchive[i];
                }
            }
        }

        if(Global::verbose)
        {
            cout<<"Unpacking from \""<<pathToArchive<<"\" to \""<<pathToDir<<"\""<<endl;
        }

        FileReaderInterface *pFileReaderItf = FileReaderCstdio::Open(pathToArchive.c_str());
        MVFS::Reader *pReader = MVFS::Reader::Open(pFileReaderItf,key);

        UnpackDir(pReader->GetRoot(),pathToDir);

        delete pFileReaderItf;
        delete pReader;
    }
}
