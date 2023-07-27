#include <iostream>
#include "Node.hpp"

//Constructor
Node::Node(char letter, unsigned int depth) {
    this->letter = letter;
    this->parent = 0;
    this->depth = depth;
    this->occupiedKeys = 0;
    this->endOfWord = false;
    for (int i{0}; i < 27; i++) {
        children[i] = new Node('*', depth+1, this);
    }
};

// Constructor
Node::Node(char letter, unsigned int depth, Node *parent) {
    this->letter = letter;
    this->parent = parent;
    this->depth = depth;
    this->occupiedKeys = 0;
    this->endOfWord = false;
    if (letter != '*') {
        for (int i{0}; i < 27; i++) {
            children[i] = new Node('*', depth+1, this);
        }
    };
}

// Destructor
Node::~Node() {
    if (letter != '*') {
        for (int i{0}; i < 27; i++) {
            delete children[i];
            children[i] = nullptr;
        }
    };
}

//Add data to page
std::string Node::insert(std::string word) {
    if (word.empty()) {
        if (this->endOfWord) {
            return "failure";
        } else {
            endOfWord = true;
            delete children[26];
            children[26] = new Node(' ', depth+1, this);
            occupiedKeys++;
            return "success";
        }
    } else {
        char nextLetter = word[0];
        word.erase(word.begin());
        int nextIndex = nextLetter - 65;
        if (children[nextIndex]->getLetter() != nextLetter) {
            delete children[nextIndex];
            children[nextIndex] = new Node(nextLetter, depth+1, this);
            occupiedKeys++;
        }
        return children[nextIndex]->insert(word);
    }
};

//Get data from certain address
int Node::count(std::string prefix) {
    if (letter == '*') {
        return 0;
    }

    if (prefix.empty()) {
        int count{0};
        if (endOfWord) {
            count++;
        }
        for (int i{0}; i < 26; i++) {
            count += children[i]->count("");
        }
        return count;
    } else {
        char nextLetter = prefix[0];
        prefix.erase(prefix.begin());
        int nextIndex = nextLetter - 65;
        return children[nextIndex]->count(prefix);
    }
};

//Get ID of Page
std::string Node::erase(std::string word) {
    char deletedLetter = word[word.size()-1];
    word.pop_back();
    int deletedIndex;
    if (deletedLetter == ' ') {
        deletedIndex = 26;
        this->endOfWord = false;
    } else {
        deletedIndex = deletedLetter - 65;
    }
    if (children[deletedIndex]->occupiedKeys == 0) {
        delete children[deletedIndex];
        children[deletedIndex] = new Node('*', depth+1, this);
        occupiedKeys--;
        if (word.empty()) {
            if (this->depth == 0) {
                return "success";
            } else {

                return "failure";
            }
        } else {
            return parent->erase(word);
        }
    } else {
        return "success";
    }
};  

//
std::string Node::print(std::string word) {
    std::string prints;
    std::string fullWord;
    if (letter != '\0') {
        fullWord = word+letter;
    }
    if (this->letter == '*') {
        return "";
    }
    if (this->endOfWord) {
        prints.append(fullWord);
        prints.append(" ");
    }
    for (int i{0}; i < 26; i++) {
        prints.append(children[i]->print(fullWord));
    }
    return prints;
};

//
void Node::spellcheck(std::string word) {
    char nextLetter = word[depth];
    int nextIndex = nextLetter-65;
    if (word.length() == depth) {
        if (this->endOfWord) {
            std::cout << "correct" << std::endl;
        } else {
            word.erase(word.begin()+depth-1, word.end());
            std::string result = this->print(word);
            result.erase(result.end()-1);
            std::cout << result << std::endl;
        }
    } else {  
        if (children[nextIndex]->getLetter() == '*') {
            if (depth == 0) {
                std::cout << std::endl;
                return;
            }
            word.erase(word.begin()+depth-1, word.end());
            std::string result = this->print(word);
            result.erase(result.end()-1);
            std::cout << result << std::endl;
        } else {
            children[nextIndex]->spellcheck(word);
        }
    }
};

//
void Node::clear() {
    for (int i{0}; i < 27; i++) {
        delete children[i];
        children[i] = new Node('*', depth+1, this);
    }
    occupiedKeys = 0;
};

//
Node* Node::navigateToLeaf(std::string word) {
    if (word.empty()) {
        if (this->endOfWord) {
            return this;
        } else {
            return 0;
        }
    } else {
        char nextLetter = word[0];
        word.erase(word.begin());
        int nextIndex = nextLetter-65;
        if (children[nextIndex]->getLetter() == '*') {
            return children[nextIndex];
        } else {
            return children[nextIndex]->navigateToLeaf(word);
        }
    }
};

char Node::getLetter() {
    return letter;
}