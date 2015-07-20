#include "MVFSNode.hpp"

using namespace std;

namespace MVFS
{
    Node Node::s_sentinel(NULL);

    Node::Node(Reader *reader)
        : m_type(Node::Type::DIR), m_fileOffset(0), m_reader(reader)
    {
    }

    Node::~Node()
    {
        for(unordered_map<string,Node*>::iterator it=m_directories.begin();it!=m_directories.end();++it)
        {
            delete it->second;
        }
        for(unordered_map<string,Node*>::iterator it=m_files.begin();it!=m_files.end();++it)
        {
            delete it->second;
        }
    }

    unordered_map<string,Node*>& Node::GetDirectories()
    {
        return m_directories;
    }

    unordered_map<string,Node*>& Node::GetFiles()
    {
        return m_files;
    }

    Node* Node::Get(std::string name)
    {
        unordered_map<string,Node*>::iterator it=m_directories.find(name);
        if(it!=m_directories.end())
        {
            return it->second;
        }
        it=m_files.find(name);
        if(it!=m_files.end())
        {
            return it->second;
        }
        return &s_sentinel;
    }

    Node::Type Node::GetType() const
    {
        return m_type;
    }

    bool Node::IsDirectory() const
    {
        return m_type == Node::Type::DIR;
    }

    bool Node::IsFile() const
    {
        return m_type == Node::Type::FILE;
    }

    Node* Node::GetSentinel()
    {
        return &s_sentinel;
    }

    void Node::SetParent(Node *parent)
    {
        m_parent=parent;
    }
}
