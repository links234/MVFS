#ifndef MVFSNODE_HPP
#define MVFSNODE_HPP

#include <unordered_map>
#include <string>

namespace MVFS
{
    class Reader;

    namespace V1
    {
        class Reader;
    }
}

namespace MVFS
{
    class Node
    {
    public:
        ~Node();

        enum Type{DIR,FILE};

        std::unordered_map<std::string,Node*>& GetDirectories();
        std::unordered_map<std::string,Node*>& GetFiles();
        Node* Get(std::string name);

        Type GetType() const;
        bool IsDirectory() const;
        bool IsFile() const;

        static Node* GetSentinel();

    private:
        Node(Reader *reader);

        void SetParent(Node *parent);

        std::unordered_map<std::string,Node*> m_directories, m_files;
        Type m_type;
        int m_fileOffset;

        Reader *m_reader;
        Node *m_parent;

        static Node s_sentinel;

        friend class MVFS::Reader;
        friend class MVFS::V1::Reader;
    };
}

#endif
