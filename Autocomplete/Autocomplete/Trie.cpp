#include "Trie.h"

std::string str;

void Trie::suggestHelper(TrieNode* node, const std::string& currentPrefix, std::vector<std::string>& suggestions)
{
    if (node->isEndOfWord)
    {
        suggestions.push_back(currentPrefix);
    }
    for (int i = 0; i < ALPHABET_SIZE; i++)
    {
        if (node->children[i])
        {
            suggestHelper(node->children[i], currentPrefix + static_cast<char>('a' + i), suggestions);
        }
    }
}

Trie::Trie()
    {
        root = new TrieNode();
    }

Trie::~Trie()
    {
        deleteTrie(root);
    }

void Trie::deleteTrie(TrieNode* node)
{
    for (int i = 0; i < ALPHABET_SIZE; i++)
    {
        if (node->children[i])
        {
            deleteTrie(node->children[i]);
        }
    }
    delete node;
}

void Trie::insert(const std::string& word)
{
    TrieNode* currentNode = root;
    for (char ch : word)
    {
        int index = ch - 'a';
        if (currentNode->children[index] == nullptr)
        {
            currentNode->children[index] = new TrieNode();
        }
        currentNode = currentNode->children[index];
    }
    currentNode->isEndOfWord = true;
}

std::vector<std::string> Trie::suggest(const std::string& prefix)
{
    TrieNode* currentNode = root;
    for (char ch : prefix)
    {
        int index = ch - 'a';
        if (currentNode->children[index] == nullptr)
        {
            return {};
        }
        currentNode = currentNode->children[index];
    }

    std::vector<std::string> suggestions;
    suggestHelper(currentNode, prefix, suggestions);
    return suggestions;
}

void Trie::loadFromFile(const std::string& filename)
{
    std::ifstream file(filename);
    if (!file.is_open())
    {
        return;
    }

    std::string word;
    while (std::getline(file, word))
    {
        insert(word);
    }

    file.close();
}

void clearConsole()
{
#if defined(_WIN32) || defined(_WIN64)
    system("cls");
#elif defined(__linux__) || defined(__APPLE__)
    system("clear");
#else
    std::cout << "\033[2J\033[1;1H";
#endif
}

std::string findLastWord(const std::string& str1)
{
    size_t end = str1.find_last_not_of(' ');
    if (end == std::string::npos)
    {
        return "";
    }

    size_t lastSpace = str1.rfind(' ', end);

    return str1.substr(lastSpace + 1, end - lastSpace);
}

void display(Trie& trie, const std::string& prefix)
{
    clearConsole();

    std::vector<std::string> suggestions = trie.suggest(prefix);

    if (suggestions.empty())
    {
        std::cout << str;

    }
    else
    {
        for (const std::string& suggestion : suggestions)
        {
            //clearConsole();
            std::cout << suggestion << std::endl;
            /*std::string input;
            std::getline(std::cin, input);
            if (input == " ")
            {
                break;
            }*/

        }
        std::cout << str;
    }
}

void execute(Trie& trie)
{
    std::string prefix;

    while (true)
    {
        std::string input;
        std::getline(std::cin, input);

        str += input;

        if (input.empty())
        {
            break; // continue; для продолжения работы программы после ввода пустой строки
        }

        prefix += input;
        display(trie, findLastWord(prefix));
    }
}