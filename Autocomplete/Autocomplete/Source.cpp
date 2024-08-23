#include <iostream>
#include <thread>
#include <chrono>
//#include <Windows.h>
#include "Trie.h"

/*void simulateEnterKey()
{
    INPUT input;
    input.type = INPUT_KEYBOARD;
    input.ki.wScan = 0;
    input.ki.time = 0;
    input.ki.dwExtraInfo = 0;

    // Нажатие клавиши Enter
    input.ki.wVk = VK_RETURN;
    input.ki.dwFlags = 0;
    SendInput(1, &input, sizeof(INPUT));

    // Отпускание клавиши Enter
    input.ki.dwFlags = KEYEVENTF_KEYUP;
    SendInput(1, &input, sizeof(INPUT));
}

void simulateKeyPresses()
{
    while (true)
    {
        simulateEnterKey();
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    }
}*/

int main()
{
    Trie trie;
    trie.loadFromFile("engwords.txt");

    // std::thread simThread(simulateKeyPresses); // 

    execute(trie);

    // simThread.detach(); // Отсоединение потока, чтобы он работал независимо

    return 0;
}
