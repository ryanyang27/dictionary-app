#ifndef NODE_CLASS
#define NODE_CLASS
#include <string>
#include <vector>

class Node {
    public:
        Node(char letter, unsigned int depth);
        Node(char letter, unsigned int depth, Node *parent);
        ~Node();
        std::string insert(std::string word);
        int count(std::string prefix);
        std::string erase(std::string word);
        std::string print(std::string word);
        void spellcheck(std::string word);
        Node* navigateToLeaf(std::string word);
        void clear();
        char getLetter();
        unsigned int occupiedKeys;
    private:
        Node *children[27];
        Node *parent; 
        char letter;
        unsigned int depth;
        bool endOfWord;
};
#endif
