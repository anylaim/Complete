#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <unordered_map>
#include <unordered_set>


#define ALPHABET_SIZE 26

class Trie
{
private:
    struct TrieNode
    {
        struct TrieNode* children[ALPHABET_SIZE];
        bool isEndOfWord;

        TrieNode() : isEndOfWord(false)
        {
            for (int i = 0; i < ALPHABET_SIZE; i++)
                children[i] = nullptr;
        }
    };

    TrieNode* root;

    void suggestHelper(TrieNode* node, const std::string& currentPrefix, std::vector<std::string>& suggestions);


public:
    Trie();

    ~Trie();

    void deleteTrie(TrieNode* node);

    void insert(const std::string& word);

    std::vector<std::string> suggest(const std::string& prefix);

    void loadFromFile(const std::string& filename);

};

void clearConsole();

void display(Trie& trie, const std::string& prefix);

void execute(Trie& trie);