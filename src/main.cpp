#include "MVFS.hpp"

using namespace std;

int main()
{
    vector<char> myKey;
    myKey.push_back(255);
    myKey.push_back(255);
    myKey.push_back(127);
    myKey.push_back(31);
    myKey.push_back(127);
    myKey.push_back(31);
    myKey.push_back(7);

    MVFS::V1::Pack("./local/test_data2","",myKey);

    MVFS::V1::Unpack("./local/test_data2.mvfs","./local/unpack_test_data2",myKey);
    return 0;
}
