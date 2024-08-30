#include "Chat.h"

Chat::Chat()
{
    data_count = 0;
    mem_size = 8;
    data = new AuthData[mem_size];
}


Chat::~Chat()
{
    delete[] data;
}


int Chat::hash_func(Login log, int offset)
{
    const double A = 0.618033;
    unsigned int hash = 0;

    for (int i = 0; i < strlen(log); i++)
    {
        hash = (hash * 31) + log[i];
    }

    double fractional_part = hash * A - int(hash * A);
    unsigned int index = int(mem_size * fractional_part);

    return (index + offset * offset) % mem_size;
}



void Chat::reg(char _login[LOGINLENGTH], char _pass[], int pass_length)
{
    if (data_count * 4 >= mem_size * 3)
    {
        resize();
    }

    uint* hash = sha1(_pass, pass_length);

    add(_login, hash);
}




bool Chat::login(char _login[LOGINLENGTH], char _pass[], int pass_length)
{
    uint* stored_hash = find(_login);

    if (stored_hash == nullptr)
    {
        return false;
    }

    uint* input_hash = sha1(_pass, pass_length);

    bool is_correct = !memcmp(stored_hash, input_hash, SHA1HASHLENGTHBYTES);

    delete[] input_hash;

    return is_correct;
}




void Chat::add(Login log, uint* hash)
{
    if (data_count * 4 >= mem_size * 3)
    {
        resize();
    }

    int index = -1, i = 0;
    for (; i < mem_size; i++)
    {
        index = hash_func(log, i);
        if (data[index].status == enPairStatus::free || data[index].status == enPairStatus::deleted)
        {
            break;
        }
    }

    if (i >= mem_size)
    {
        resize();
        add(log, hash);
    }
    else
    {
        data[index] = AuthData(log, hash);
        data[index].status = enPairStatus::engaged;
        data_count++;
    }
}




uint* Chat::find(Login log)
{
    for (int i = 0; i < mem_size; i++)
    {
        int index = hash_func(log, i);
        if (data[index].status == enPairStatus::engaged && strcmp(data[index].login, log) == 0)
        {
            return data[index].pass_sha1_hash;
        }
        if (data[index].status == enPairStatus::free)
        {
            break;
        }
    }
    return nullptr;
}


void Chat::del(Login log)
{
    for (int i = 0; i < mem_size; i++)
    {
        int index = hash_func(log, i);
        if (data[index].status == enPairStatus::engaged && strcmp(data[index].login, log) == 0)
        {
            data[index].status = enPairStatus::deleted;
            delete[] data[index].pass_sha1_hash;
            data[index].pass_sha1_hash = nullptr;
            data_count--;
            return;
        }
    }
}


void Chat::resize()
{
    int oldSize = mem_size;
    AuthData* oldArray = data;

    mem_size *= 2;
    data = new AuthData[mem_size];
    data_count = 0;

    for (int i = 0; i < mem_size; i++)
    {
        data[i].status = enPairStatus::free;
    }

    for (int i = 0; i < oldSize; i++)
    {
        if (oldArray[i].status == enPairStatus::engaged)
        {
            add(oldArray[i].login, oldArray[i].pass_sha1_hash);
        }
    }

    delete[] oldArray;
}
