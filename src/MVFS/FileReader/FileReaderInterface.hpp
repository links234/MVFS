#ifndef FILEREADERINTERFACE_HPP
#define FILEREADERINTERFACE_HPP

namespace MVFS
{
    class FileReaderInterface
    {
    public:
        virtual int Size() = 0;
        virtual void Reset() = 0;

        virtual void Read(char *pBuffer, int size) = 0;
        virtual void ReadFrom(int offset, char *pBuffer, int size) = 0;

    private:
        FileReaderInterface();
        virtual ~FileReaderInterface();
    };
}

#endif
