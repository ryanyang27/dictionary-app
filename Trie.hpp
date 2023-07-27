#ifndef TRIE
#define TRIE
#include "Node.hpp"

class Trie {
    public:
        Trie();
        ~Trie();
        void insertCorpus(std::string word);
        void insert(std::string word);
        void count(std::string prefix);
        void erase(std::string word);
        void print(std::string word);
        void spellcheck(std::string word);
        void empty();
        void clear();
        void sizeOfTree();
    private:
        bool filterWord(std::string word);
        Node* navigateToLeaf(std::string word);
        Node* root;
        unsigned int size;
};

#endif