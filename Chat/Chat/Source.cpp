#include <iostream>
#include <locale>
#include "Chat.h"


void run_tests()
{
    Chat chat;

    // Тест 1: Регистрация пользователя
    char login1[LOGINLENGTH] = "user1";
    char password1[] = "password1";
    int password1_length = strlen(password1);

    chat.reg(login1, password1, password1_length);
    uint* found_hash1 = chat.find(login1);

    if (found_hash1 != nullptr)
    {
        std::cout << "Test 1 (User registration) passed." << std::endl;
    }
    else
    {
        std::cout << "Test 1 (User registration) failed." << std::endl;
    }

    // Тест 2: Вход в систему с правильными данными
    if (chat.login(login1, password1, password1_length))
    {
        std::cout << "Test 2 (Login with correct password) passed." << std::endl;
    }
    else
    {
        std::cout << "Test 2 (Login with correct password) failed." << std::endl;
    }

    // Тест 3: Вход в систему с неверным паролем
    char wrong_password[] = "wrongpass";
    int wrong_password_length = strlen(wrong_password);

    if (!chat.login(login1, wrong_password, wrong_password_length))
    {
        std::cout << "Test 3 (Login with incorrect password) passed." << std::endl;
    }
    else
    {
        std::cout << "Test 3 (Login with incorrect password) failed." << std::endl;
    }

    // Тест 4: Удаление пользователя
    chat.del(login1);
    uint* found_hash2 = chat.find(login1);

    if (found_hash2 == nullptr)
    {
        std::cout << "Test 4 (User deletion) passed." << std::endl;
    }
    else
    {
        std::cout << "Test 4 (User deletion) failed." << std::endl;
    }

    // Тест 5: Проверка заполнения хеш-таблицы и её расширение
    for (int i = 0; i < 10; ++i)
    {
        char login[LOGINLENGTH];
        sprintf_s(login, "user%d", i);
        char password[] = "123456";
        int pass_length = strlen(password);
        chat.reg(login, password, pass_length);
    }

    bool all_users_found = true;
    for (int i = 0; i < 10; ++i)
    {
        char login[LOGINLENGTH];
        sprintf_s(login, "user%d", i);
        uint* hash = chat.find(login);

        if (hash == nullptr)
        {
            all_users_found = false;
            std::cout << "Test 5 (Table filling) failed for " << login << std::endl;
        }
    }

    if (all_users_found)
    {
        std::cout << "Test 5 (Table filling and resizing) passed." << std::endl;
    }
    else
    {
        std::cout << "Test 5 (Table filling and resizing) failed." << std::endl;
    }

}

int main()
{
    run_tests();

	return 0;
}