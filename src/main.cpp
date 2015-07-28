#include <vector>
#include <string>

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

#include "MVFS.hpp"

using namespace std;

const int OPTYPE_PACK=0;
const int OPTYPE_UNPACK=1;

int opType=OPTYPE_PACK;

string from, to;
int versionHint=MVFS::LATEST_VERSION;
vector<char> key;

int main(int argc, char* argv[])
{
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
        else
        {
            cerr<<"Invalid argument: \""<<arg<<"\""<<endl;
            return -1;
        }
    }

    if(opType == OPTYPE_PACK)
    {
        struct stat st;
        if(stat(from.c_str(),&st) == 0)
        {
            if( ((st.st_mode) & S_IFMT) != S_IFDIR)
            {
                cerr<<"Directory \""<<from<<"\" does not exists!"<<endl;
                return -1;
            }
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
