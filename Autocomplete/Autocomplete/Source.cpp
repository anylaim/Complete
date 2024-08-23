#include <iostream>
#include <thread>
#include <chrono>
#include "Trie.h"



int main()
{
    Trie trie;
    trie.loadFromFile("engwords.txt");

    execute(trie);

    return 0;
}
