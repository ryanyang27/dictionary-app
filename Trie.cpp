#include <iostream>
#include "Trie.hpp"

// Constructor
Trie::Trie() {
    root = new Node('\0', 0);
    size = 0;
}

// Destructor
Trie::~Trie() {
    delete root;
    root = nullptr;
}

//Add data to page
void Trie::insertCorpus(std::string word) {
    if (this->filterWord(word)) {
        std::string result = root->insert(word);
        if (result == "success") {
            size++;
        }
    }
}

//Add data to page
void Trie::insert(std::string word) {
    if (this->filterWord(word)) {
        std::string result = root->insert(word);
        std::cout << result << std::endl;
        if (result == "success") {
            size++;
        }
    } else {
        std::cout << "illegal argument" << std::endl;
    }
};

//Get data from certain address
void Trie::count(std::string prefix) {
    if (this->filterWord(prefix)) {
        int result = root->count(prefix);
        if (result != 0) {
            std::cout << "count is " << result << std::endl;
        } else {
            std::cout << "not found" << std::endl;
        }
    } else {
        std::cout << "illegal argument" << std::endl;
    }
};

//Get ID of Page
void Trie::erase(std::string word) {
    if (this->filterWord(word)) {
        if (this->size) {
            Node * leaf = root->navigateToLeaf(word);
            if (leaf) {
                if (leaf->getLetter() != '*') {
                    word.append(" ");
                    std::string result = leaf->erase(word);
                    std::cout << result << std::endl;
                    if (result == "success") {
                        size--;
                    }
                } else {
                    std::cout << "failure" << std::endl;
                }
            } else {
                std::cout << "failure" << std::endl;
            }
        } else {
            std::cout << "failure" << std::endl;
        }   
    } else {
        std::cout << "illegal argument" << std::endl;
    }
};

//
void Trie::print(std::string word) {
    if (size) { 
        std::string result = root->print(word);
        result.erase(result.end()-1);
        std::cout << result << std::endl;
    }
};

//
void Trie::spellcheck(std::string word) {
    root->spellcheck(word);
};

//
void Trie::empty() {
    if (size) {
        std::cout << "empty 0" << std::endl;
    } else {
        std::cout << "empty 1" << std::endl;
    }
};

//
void Trie::clear() {
    root->clear();
    size = 0;
    std::cout << "success" << std::endl;
};

//
void Trie::sizeOfTree() {
    std::cout << "number of words is " << size << std::endl;
};

//
bool Trie::filterWord(std::string word) {
    for (unsigned int i{0}; i < word.length(); i++) {
        int asciiNum = word[i];
        if (asciiNum < 65 || asciiNum > 90) {
            return false;
        }
    }
    return true;
}

//
Node* Trie::navigateToLeaf(std::string word) {
    return root->navigateToLeaf(word);
};