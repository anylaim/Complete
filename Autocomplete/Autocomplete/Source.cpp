#include <iostream>
#include "Trie.h"



int main()
{
    Trie trie;
    trie.loadFromFile("engwords.txt");

    execute(trie);

    return 0;
}
