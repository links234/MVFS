#include <vector>
#include <string>

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <dirent.h>
#include <errno.h>

#include "MVFS.hpp"

using namespace std;

const int OPTYPE_PACK=0;
const int OPTYPE_UNPACK=1;

int opType=OPTYPE_PACK;

string from, to, rawKey;
int versionHint=MVFS::LATEST_VERSION;
vector<char> key;

inline void PrintHelp()
{
    cout<<"List of arguments: "<<endl;
    cout<<"\t--verbose or -v print more information about what is happening"<<endl;
    cout<<"\t--version=X or -vX sets the preferred file version to X"<<endl;
    cout<<"\t--unpack or -u"<<endl;
    cout<<"\t--pack or -p (this is set by default)"<<endl;
    cout<<"\t--from <path> sets the path to the input file/directory"<<endl;
    cout<<"\t--to <path> sets the path to the output file/directory"<<endl;
    cout<<"\t--key \"{values-separated-by-comma}\" sets the key for encryption/decryption"<<endl;
    cout<<"\t--help show this table";
}

int main(int argc, char* argv[])
{
    if(argc==2)
    {
        if(string(argv[1])=="--help")
        {
            PrintHelp();
            return 0;
        }
    }

    for(int i=1;i<argc;++i)
    {
        string arg=string(argv[i]);
        if(arg=="--verbose" || arg=="-v")
        {
            MVFS::Global::verbose=true;
        }
        else if(arg=="--unpack" || arg=="-u")
        {
            opType = OPTYPE_UNPACK;
        }
        else if(arg=="--pack" || arg=="-p")
        {
            opType = OPTYPE_PACK;
        }
        else if(arg=="--version=1" || arg=="-v1")
        {
            versionHint=1;
        }
        else if(arg=="--from")
        {
            ++i;
            if(i<argc)
            {
                from=string(argv[i]);
            }
            else
            {
                cerr<<"Argument --from not followed by a parameter"<<endl;
            }
        }
        else if(arg=="--to")
        {
            ++i;
            if(i<argc)
            {
                to=string(argv[i]);
            }
            else
            {
                cerr<<"Argument --to not followed by a parameter"<<endl;
                return -1;
            }
        }
        else if(arg=="--key" || arg=="-k")
        {
            ++i;
            if(i<argc)
            {
                rawKey = string(argv[i]);
            }
            else
            {
                cerr<<"Argument "<<argv[i-1]<<" not followd by a parameter"<<endl;
                return -1;
            }
        }
        else
        {
            cerr<<"Invalid argument: \""<<arg<<"\""<<endl;
            return -1;
        }
    }

    if(rawKey!="")
    {
        int index=0;
        if(rawKey[index]=='{')
        {
            ++index;
        }
        else
        {
            cerr<<"Invalid key param \""<<rawKey<<"\""<<endl;
            return -1;
        }
        while(true)
        {
            char value=0;
            while('0'<=rawKey[index] && rawKey[index]<='9')
            {
                value*=10;
                value+=rawKey[index]-'0';
                ++index;
            }
            key.push_back(value);
            if(rawKey[index]==',')
            {
                ++index;
            }
            else if(rawKey[index]=='}')
            {
                break;
            }
            else
            {
                cerr<<"Invalid key param \""<<rawKey<<"\""<<endl;
                return -1;
            }
        }
    }

    if(opType == OPTYPE_PACK)
    {
        DIR *dp;
        struct dirent *dirp;
        if((dp  = opendir(from.c_str())) == NULL)
        {
            cerr << "Error(" << errno << ") opening directory \"" << from << "\"" << endl;
            return -1;
        }

        if(versionHint==1)
        {
            MVFS::V1::Pack(from,to,key);
        }
        else
        {
            cerr<<"Invalid version argument ("<<versionHint<<")"<<endl;
            return -1;
        }
    }
    else if(opType == OPTYPE_UNPACK)
    {
        struct stat st;
        if( stat(from.c_str(), &st) != 0 )
        {
            cerr<<"File \""<<from<<"\" does not exists!"<<endl;
            return -1;
        }

        MVFS::Unpack(from,to,key);
    }

    return 0;
}
