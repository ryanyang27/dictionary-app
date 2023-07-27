
#include <iostream>
#include <fstream>
#include "Trie.hpp"

using namespace std;

int main() {
    Trie myTrie;
    ifstream fin("corpus.txt");
    string cmd;
    string addWord;
    while (cin >> cmd) {
        if (cmd == "load") {
            while (fin >> addWord) {
                myTrie.insertCorpus(addWord);
            }
            cout << "success" << endl;
        } else if (cmd == "i") {
            string word;
            cin >> word;
            myTrie.insert(word);
        } else if (cmd == "c") {
            string prefix;
            cin >> prefix;
            myTrie.count(prefix);
        } else if (cmd == "e") {
            string word;
            cin >> word;
            myTrie.erase(word);
        } else if (cmd == "p") {
            myTrie.print("");
        } else if (cmd == "spellcheck") {
            string word;
            cin >> word;
            myTrie.spellcheck(word);
        } else if (cmd == "empty") {
            myTrie.empty();
        } else if (cmd == "clear") {
            myTrie.clear();
        } else if (cmd == "size") {
            myTrie.sizeOfTree();
        } else if (cmd == "exit") {
            myTrie.~Trie();
        }
    }
} 