#pragma once
#include "SHA1.h"
#include <string>
#include <iostream>



#define SIZE 10
#define LOGINLENGTH 10

typedef char Login[LOGINLENGTH];

class Chat
{
public:

    Chat();
    ~Chat();

    void add(Login log, uint* fr_count);
    uint* find(Login log);
    void del(Login log);
    void resize();

    void reg(char _login[LOGINLENGTH], char _pass[], int pass_length);
    bool login(char _login[LOGINLENGTH], char _pass[], int pass_length);

private:

    enum enPairStatus
    {
        free, // свободен
        engaged, //занят
        deleted //удален
    };

    struct AuthData
    {
        AuthData() : login(""), pass_sha1_hash(0), status(enPairStatus::free)
        {}


        ~AuthData()
        {
            delete[] pass_sha1_hash;
        }

        AuthData(char _login[LOGINLENGTH], uint* sh1)
        {
            strcpy_s(login, _login);
            pass_sha1_hash = new uint[SHA1HASHLENGTHUINTS];
            memcpy(pass_sha1_hash, sh1, SHA1HASHLENGTHBYTES);
        }



        AuthData& operator = (const AuthData& other)
        {
            strcpy_s(login, other.login);

            if (pass_sha1_hash != nullptr)
                delete[] pass_sha1_hash;

            pass_sha1_hash = new uint[SHA1HASHLENGTHUINTS];
            memcpy(pass_sha1_hash, other.pass_sha1_hash, SHA1HASHLENGTHBYTES);

            return *this;
        }


        Login login;
        uint* pass_sha1_hash;
        enPairStatus status;
    };

    int hash_func(Login log, int offset);

    AuthData* data;
    int data_count;

    int mem_size;

};

