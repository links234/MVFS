#include "MVFS_V1.hpp"

using namespace std;

namespace MVFS
{
    namespace V1
    {
        vector<char> xorKey;
        ofstream archiveOutput;

        const unsigned char MKDIR=1;
        const unsigned char OPENDIR=2;
        const unsigned char BACK=3;
        const unsigned char NEWFILE=4;
        const unsigned char OPENLASTMKDIR=5;
        const unsigned char THIS_VERSION=1;

        void PackWriteFile(string pathToFile)
        {
            ifstream file(pathToFile.c_str(), ios::binary | ios::ate);
            int fileSize = file.tellg();
            file.close();

            cout<<pathToFile<<"   size = "<<fileSize<<" bytes"<<endl;

            char *buffer=new char[fileSize];
            file.open(pathToFile.c_str(),ios::binary);
            file.read(buffer,fileSize);
            file.close();

            if(xorKey.size())
            {
                int keyIndex=0;
                for(int i=0;i<fileSize;++i)
                {
                    buffer[i]^=xorKey[keyIndex];

                    ++keyIndex;
                    if(keyIndex>=xorKey.size())
                    {
                        keyIndex=0;
                    }
                }
            }

            archiveOutput<<fileSize;
            archiveOutput.write(buffer,fileSize);
        }

        void PackRec(string pathToDir)
        {
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
                if(name==".")
                {
                    continue;
                }
                if(name=="..")
                {
                    continue;
                }
                if(name[name.size()-1]=='~')
                {
                    continue;
                }

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
        }

        void Pack (string pathToDir, string pathToArchive, vector<char> key)
        {
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
        }

        ifstream archiveInput;

        void Unpack(string pathToArchive, string pathToDir, vector<char> key)
        {
            if(pathToArchive=="")
            {
                //TODO
            }
        }
    }
}
